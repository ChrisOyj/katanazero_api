#include "stdafx.h"
#include "CCollider.h"

#include "CObj.h"
#include "CCamera.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_iID(g_iNextID++) // 콜라이더가 새로 생성될 때마다 ID 값을 하나씩 늘려서 다 다르게 넣어줌
	, m_pOwner(nullptr)
	, m_vOffSetPos{}
	, m_vFinalPos{}
	, m_vScale{}
	, m_vDir{1.f, 0.f}
	, m_iCol(0)
	, m_bCircle(false)
{
}

CCollider::CCollider(const CCollider & _origin) // ID값 다르게 해주기 위해 복사 생성자 직접 구현
	: m_pOwner(nullptr)
	, m_vOffSetPos(_origin.m_vOffSetPos)
	, m_vScale(_origin.m_vScale)
	, m_vDir(_origin.m_vDir)
	, m_iID(g_iNextID++)
	, m_bCircle(_origin.m_bCircle)
{
}

CCollider::~CCollider()
{
}

void CCollider::Initialize()
{
	Vec2 vObjectPos = m_pOwner->Get_Pos();
	m_vFinalPos = vObjectPos + m_vOffSetPos;

	float fAngle = acos(m_vDir.x) * (180.f / PI); // 각도 구하기

	if (0 > m_vDir.y)
	{
		fAngle *= -1.f;
	}

	int LTX = (int)(m_vFinalPos.x - m_vScale.x / 2.f);
	int LTY = (int)(m_vFinalPos.y - m_vScale.y / 2.f);
	int RBX = (int)(m_vFinalPos.x + m_vScale.x / 2.f);
	int RBY = (int)(m_vFinalPos.y + m_vScale.y / 2.f);

	m_LTPoint = rotatept(m_vFinalPos, Point(LTX, LTY), fAngle);
	m_LBPoint = rotatept(m_vFinalPos, Point(LTX, RBY), fAngle);
	m_RTPoint = rotatept(m_vFinalPos, Point(RBX, LTY), fAngle);
	m_RBPoint = rotatept(m_vFinalPos, Point(RBX, RBY), fAngle);
}

void CCollider::Final_Update()
{
	//Object의 위치를 따라 가기
	Vec2 vObjectPos = m_pOwner->Get_Pos();
	m_vFinalPos = vObjectPos + m_vOffSetPos;


	assert(0 <= m_iCol);
}

void CCollider::Render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	SelectGDI pen(_dc, ePen);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vRenderPos = CCamera::Get_Instance()->Get_RenderPos(m_vFinalPos);

	if (m_bCircle)
	{
		Ellipse(_dc, (int)(vRenderPos.x - m_vScale.x / 2.f)
			, (int)(vRenderPos.y - m_vScale.y / 2.f)
			, (int)(vRenderPos.x + m_vScale.x / 2.f)
			, (int)(vRenderPos.y + m_vScale.y / 2.f));
	}
	else
	{
		Rectangle(_dc, (int)(vRenderPos.x - m_vScale.x / 2.f)
			, (int)(vRenderPos.y - m_vScale.y / 2.f)
			, (int)(vRenderPos.x + m_vScale.x / 2.f)
			, (int)(vRenderPos.y + m_vScale.y / 2.f));
	}

	
}

void CCollider::dir_Render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	SelectGDI pen(_dc, ePen);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);

	

	POINT LTPoint = CCamera::Get_Instance()->Get_RenderPos(m_LTPoint);
	POINT LBPoint = CCamera::Get_Instance()->Get_RenderPos(m_LBPoint);
	POINT RBPoint = CCamera::Get_Instance()->Get_RenderPos(m_RBPoint);
	POINT RTPoint = CCamera::Get_Instance()->Get_RenderPos(m_RTPoint);

	POINT destinationPoints[] = {
		LTPoint, LBPoint, RBPoint, RTPoint };

	Polygon(_dc, destinationPoints, 4);
}

void CCollider::OnCollision(CCollider * _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider * _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}

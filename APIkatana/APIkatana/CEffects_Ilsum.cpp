#include "stdafx.h"
#include "CEffects_Ilsum.h"

#include "CTimeMgr.h"
#include "CAlive.h"

CEffects_Ilsum::CEffects_Ilsum()
{
}

CEffects_Ilsum::~CEffects_Ilsum()
{
}

void CEffects_Ilsum::OnCollisionEnter(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();

	switch (pOtherObj->Get_ObjType())
	{
	case GROUP_TYPE::PLAYER_HITBOX:
	case GROUP_TYPE::MONSTER_HITBOX:
		dynamic_cast<CAlive*>(pOtherObj->Get_Owner())->LaserHit();
		pOtherObj->SetCollision(false);
		break;


	case GROUP_TYPE::PLAYER:
	case GROUP_TYPE::MONSTER:
		if (STATE_TYPE::HIT == dynamic_cast<CAlive*>(pOtherObj)->Get_State() || STATE_TYPE::DEATH == dynamic_cast<CAlive*>(pOtherObj)->Get_State())
			dynamic_cast<CAlive*>(pOtherObj)->LaserHit();

		break;
	}
}

void CEffects_Ilsum::Initialize()
{
	m_vPos; // 이동한 위치
	m_pOwner->Get_Pos(); // 이전 위치

	float fDis = sqrt((m_vPos.x - m_pOwner->Get_Pos().x) * (m_vPos.x - m_pOwner->Get_Pos().x) + (m_vPos.y - m_pOwner->Get_Pos().y) * (m_vPos.y - m_pOwner->Get_Pos().y));

	SetScale(Vec2(fDis, 25.f));

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

	m_tInfo.RGB[0] = 255;
	m_tInfo.RGB[1] = 200;
	m_tInfo.RGB[2] = 0;

	m_tInfo.iAlpha = 255;


	CreateCollider();
	Get_Collider()->SetScale(m_vScale);
	Get_Collider()->SetOffSetPos(Vec2(m_vScale.x * -0.5f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜

	m_fSpeed = 200.f;
}

void CEffects_Ilsum::Update()
{
	m_fTime += fDT;

	Vec2 vScale = Get_Scale();
	vScale.y -= m_fSpeed * fDT;
	SetScale(vScale);

	if (2.f >= vScale.y)
	{
		DeleteObject(this);
	}
}

void CEffects_Ilsum::Render(HDC _dc)
{
	Vec2 vPos = Get_Pos();
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	Vec2 vScale = Get_Scale();

	int LTX = (int)(vPos.x - vScale.x);
	int LTY = (int)(vPos.y - vScale.y * 0.5f);
	int RBX = (int)(vPos.x);
	int RBY = (int)(vPos.y + vScale.y * 0.5f);

	Point LTpoint = rotate(vPos, Point(LTX, LTY), m_fTheta);
	Point LBpoint = rotate(vPos, Point(LTX, RBY), m_fTheta);
	Point RTpoint = rotate(vPos, Point(RBX, LTY), m_fTheta);
	Point RBpoint = rotate(vPos, Point(RBX, RBY), m_fTheta);
	//Point cenPoint = rotate(vPos, Point(RBX, (INT)vPos.y), m_fTheta);

	Graphics g(_dc);

	Point destinationPoints[4] = {
		LTpoint, LBpoint, RBpoint, RTpoint };

	GraphicsPath path;
	path.AddLines(destinationPoints, 4);

	g.FillPath(&SolidBrush(Color(m_tInfo.iAlpha, m_tInfo.RGB[0], m_tInfo.RGB[1], m_tInfo.RGB[2])), &path);



	LTX = (int)(vPos.x - vScale.x);
	LTY = (int)(vPos.y - vScale.y * 0.5f) + 2;
	RBX = (int)(vPos.x);
	RBY = (int)(vPos.y + vScale.y * 0.5f) - 2;

	LTpoint = rotate(vPos, Point(LTX, LTY), m_fTheta);
	LBpoint = rotate(vPos, Point(LTX, RBY), m_fTheta);
	RTpoint = rotate(vPos, Point(RBX, LTY), m_fTheta);
	RBpoint = rotate(vPos, Point(RBX, RBY), m_fTheta);

	Point destinationPoints2[] = {
		LTpoint, LBpoint, RBpoint, RTpoint };

	GraphicsPath path2;
	path2.AddLines(destinationPoints2, 4);
	g.FillPath(&SolidBrush(Color(m_tInfo.iAlpha, 255, 255, 255)), &path2);


	/*GraphicsPath path;
	path.AddLines(destinationPoints, 4);

	PathGradientBrush pthGrBrush(&path);

	pthGrBrush.SetCenterPoint(cenPoint);
	pthGrBrush.SetCenterColor(Color(200, 255, 255, 255));

	Color colors[] = { Color(m_tInfo.iAlpha, m_tInfo.RGB[0], m_tInfo.RGB[1], m_tInfo.RGB[2])  };
	int count = 1;
	pthGrBrush.SetSurroundColors(colors, &count);

	g.FillPath(&pthGrBrush, &path);*/

	
}

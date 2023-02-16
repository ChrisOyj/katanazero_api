#include "stdafx.h"
#include "CSelector.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CSelector::CSelector()
	: m_fXSpeed(0.f)
	, m_fMaxXSpeed(220.f)
	, m_fFriction(12000.f)
	, m_fAccel(0.f)
	, m_fMaxAccel(800.f)
	, m_bSelected(false)
	, m_iAlpha(30)
	, m_fAcc(0.f)
{
	SetPos(Vec2(320.f, 227.f));
	SetScale(Vec2(290.f, 20.f));
}

CSelector::~CSelector()
{
}

void CSelector::Update()
{
	Vec2 vPos = Get_Pos();

	if (KEY(W, TAP))
	{
		if (227.f < vPos.y)
		{
			SetDir(Vec2(0.f, -1.f));
			m_fXSpeed = 700.f;
		}
	}

	if (KEY(S, TAP))
	{
		if (277.f > vPos.y)
		{
			SetDir(Vec2(0.f, 1.f));
			m_fXSpeed = 700.f;
		}
	}

	if (KEY(SPACE, TAP))
	{
		m_bSelected = true;
	}

	if (m_bSelected)
	{
		m_fAcc += RealfDT;
		m_fTime += RealfDT;
		if (0.03f < m_fTime)
		{
			m_iAlpha = 30;
			m_fTime = 0.f;
		}
		else
		{
			m_iAlpha = 0;
		}

		if (0.2f < m_fAcc)
		{
			m_bSelected = false;
			m_iAlpha = 30;

		}
	}


	if (227.f > vPos.y)
	{
		vPos.y = 227.f;
		m_fXSpeed = 0.f;
	}
	if (277.f < vPos.y)
	{
		vPos.y = 277.f;
		m_fXSpeed = 0.f;

	}

	SetPos(vPos);

	physics_Update();

}

void CSelector::Render(HDC _dc)
{
	Vec2 vPos = Get_Pos();
	Vec2 vScale = Get_Scale();

	//검은 네모
	int LTX = (int)(vPos.x - vScale.x / 2.f);
	int LTY = (int)(vPos.y - vScale.y / 2.f);
	int RBX = (int)(vPos.x + vScale.x / 2.f);
	int RBY = (int)(vPos.y + vScale.y / 2.f);

	Point LTpoint = { LTX, LTY };
	Point LBpoint = { LTX, RBY };
	Point RTpoint = { RBX, LTY };
	Point RBpoint = { RBX, RBY };

	Graphics g(_dc);

	////////////////////////
	Point destinationPoints[] = {
		LTpoint, LBpoint, RBpoint, RTpoint };

	// Use the array of points to construct a path.
	GraphicsPath path;
	path.AddLines(destinationPoints, 4);

	//g.FillPath(&pthGrBrush, &path);
	g.FillPath(&SolidBrush(Color(m_iAlpha, 255, 255, 255)), &path);
}

void CSelector::physics_Update()
{
	Vec2 vPos = Get_Pos();
	Vec2 vDir = Get_Dir();

	vPos.y += m_fXSpeed * Get_Dir().y * fDT;

		if (0 < m_fXSpeed) // 속도가 존재하면
			m_fXSpeed -= m_fFriction * fDT; // 속도는 마찰만큼 감소
		else
			m_fXSpeed = 0;

	if (m_fXSpeed < m_fMaxXSpeed)
		m_fXSpeed += (m_fAccel) * 6 * fDT;

	SetPos(vPos);
}

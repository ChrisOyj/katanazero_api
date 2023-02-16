#include "stdafx.h"
#include "CEffects_SlashHit.h"

#include "CTimeMgr.h"

CEffects_SlashHit::CEffects_SlashHit()
{
}

CEffects_SlashHit::~CEffects_SlashHit()
{
}

void CEffects_SlashHit::Initialize()
{
	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

	m_vPos.x += -500.f * Get_Dir().x;
	m_vPos.y += -500.f * Get_Dir().y;

	int i = random(0, 1);
	if (i == 0)
		m_tInfo.iColor = 50;
	else
		m_tInfo.iColor = 200;

	SetScale(Vec2(700.f, 8.f));

	m_fSpeed = 8500.f;
}

void CEffects_SlashHit::Update()
{
	m_vPos.x += m_fSpeed * RealfDT * Get_Dir().x;
	m_vPos.y += m_fSpeed * RealfDT * Get_Dir().y;

	m_fTime += RealfDT;

	if (0.07f < m_fTime && m_fAcc == 0.f)
	{
		if (m_tInfo.iColor == 50)
			m_tInfo.iColor = 200;
		else
			m_tInfo.iColor = 50;

		m_fAcc += 1.f;
	}

	if (3.f <= m_fTime)
	{
		DeleteObject(this);
	}
}

void CEffects_SlashHit::Render(HDC _dc)
{
	Vec2 vPos = Get_Pos();
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	Vec2 vScale = Get_Scale();

	int LTX = (int)(vPos.x - vScale.x / 2.f);
	int LTY = (int)(vPos.y - vScale.y / 2.f);
	int RBX = (int)(vPos.x + vScale.x / 2.f);
	int RBY = (int)(vPos.y + vScale.y / 2.f);

	Point LTpoint = rotate(vPos, Point(LTX, LTY), m_fTheta);
	Point LBpoint = rotate(vPos, Point(LTX, RBY), m_fTheta);
	Point RTpoint = rotate(vPos, Point(RBX, LTY), m_fTheta);
	Point RBpoint = rotate(vPos, Point(RBX, RBY), m_fTheta);

	Graphics g(_dc);

	////////////////////////
	Point destinationPoints[] = {
		LTpoint, LBpoint, RBpoint, RTpoint };

	GraphicsPath path;
	path.AddLines(destinationPoints, 4);

	PathGradientBrush pthGrBrush(&path);

	pthGrBrush.SetCenterColor(Color(255, 30 + m_tInfo.iColor, 285 - m_tInfo.iColor, 255));

	Color colors[] = { Color(30, 30 + m_tInfo.iColor, 285 - m_tInfo.iColor, 255) };
	int count = 1;
	pthGrBrush.SetSurroundColors(colors, &count);

	g.FillPath(&pthGrBrush, &path);
}

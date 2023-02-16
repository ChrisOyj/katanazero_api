#include "stdafx.h"
#include "CEffects_PurpleScreen.h"

#include "CTimeMgr.h"

CEffects_PurpleScreen::CEffects_PurpleScreen()
{
}

CEffects_PurpleScreen::~CEffects_PurpleScreen()
{
}

void CEffects_PurpleScreen::Initialize()
{
	m_tInfo.fFadeSpeed = 200.f;
	m_tInfo.iAlpha = 0;
	m_tInfo.iColor = 50;
	m_tInfo.bColorPlus = true;
	m_fTimeLimit = 3.f;
}

void CEffects_PurpleScreen::Update()
{
	if (5 < m_tInfo.iAlpha)
	m_tInfo.iAlpha -= int(m_tInfo.fFadeSpeed * RealfDT);

	m_fTime += RealfDT;

	if (m_tInfo.bDelete)
	{

		if (m_tInfo.bColorPlus)
		{
			m_tInfo.iAlpha = 250;
			m_tInfo.bColorPlus = false;
		}

		if (10 > m_tInfo.iAlpha)
		{
			m_tInfo.iAlpha = 0;
			m_tInfo.bDelete = false;
			DeleteObject(this);
		}

		return;
	}
	else if (m_fTimeLimit < m_fTime)
	{
		m_fTime = 0.f;
		m_fTimeLimit -= 0.3f;
		m_tInfo.iAlpha = m_tInfo.iColor;
		m_tInfo.iColor += 10;

		if (m_tInfo.iColor > 200)
			m_tInfo.iColor = 200;

		if (m_fTimeLimit < 0.3f)
			m_fTimeLimit = 0.3f;
	}

}

void CEffects_PurpleScreen::Render(HDC _dc)
{
	Vec2 vPos = CCamera::Get_Instance()->Get_RealPos(Vec2(0.f, 0.f));
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);

	Graphics g(_dc);


	g.FillRectangle(&SolidBrush(Color(m_tInfo.iAlpha, 240, 50, 220)), (int)vPos.x, (int)vPos.y, (int)WINCX, (int)WINCY);
}


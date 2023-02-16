#include "stdafx.h"
#include "CEffects_DarkScreen.h"

#include "CTimeMgr.h"

CEffects_DarkScreen::CEffects_DarkScreen()
{
}

CEffects_DarkScreen::~CEffects_DarkScreen()
{
}

void CEffects_DarkScreen::Initialize()
{
	m_tInfo.fFadeSpeed = 1500.f;
	m_tInfo.iAlpha = 0;
}

void CEffects_DarkScreen::Update()
{
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 1.f) // 속도 일반 상태
		m_tInfo.bDelete = true;

	if (m_tInfo.bDelete)
	{
		if (40 < m_tInfo.iAlpha)
			m_tInfo.iAlpha -= int(m_tInfo.fFadeSpeed * RealfDT);
		else
		{
			m_tInfo.iAlpha = 0;
			m_tInfo.bDelete = false;
			DeleteObject(this);
		}

		return;
	}

	if (200 > m_tInfo.iAlpha)
	{
		m_tInfo.iAlpha += int(m_tInfo.fFadeSpeed * RealfDT);
	}
}

void CEffects_DarkScreen::Render(HDC _dc)
{

	Graphics g(_dc);


	g.FillRectangle(&SolidBrush(Color(m_tInfo.iAlpha, 0, 0, 0)), 0, 0, (int)WINCX, (int)WINCY);
}

#include "stdafx.h"
#include "CEffects_Dragon.h"

#include "CTimeMgr.h"
#include "CCamera.h"

CEffects_Dragon::CEffects_Dragon()
{
}

CEffects_Dragon::~CEffects_Dragon()
{
}

void CEffects_Dragon::Initialize()
{
	m_tInfo.fFadeSpeed = 500.f;
	m_tInfo.iAlpha = 100;
	m_fTimeLimit = 3.f;
	m_fTime = 0.f;
	m_tInfo.bDelete = false;
}

void CEffects_Dragon::Update()
{
	if (m_tInfo.iAlpha < 255 && !m_tInfo.bDelete)
		m_tInfo.iAlpha += (int)(m_tInfo.fFadeSpeed * RealfDT);


	if (m_tInfo.iAlpha >= 255)
	{
		m_tInfo.bDelete = true;
		m_tInfo.iAlpha = 255;
	}

	if (m_tInfo.bDelete)
	{
		m_fTime += RealfDT;

		if (m_fTimeLimit < m_fTime)
			m_tInfo.iAlpha -= (int)(m_tInfo.fFadeSpeed * RealfDT);

		if (m_tInfo.iAlpha < 20)
			DeleteObject(this);

	}
		
}

void CEffects_Dragon::Render(HDC _dc)
{
	Vec2 vPos = CCamera::Get_Instance()->Get_RenderPos(m_vPos);

	vPos.y -= 60.f;
	vPos.x -= 50.f;

	Graphics g(_dc);
	TCHAR szBuff[64];
	int iRand = random(0, 5);
	float fRatio = (float)m_tInfo.iAlpha / 255.f;

	int iRectAlpha = m_tInfo.iAlpha - 100;
	if (iRectAlpha < 0)
		iRectAlpha = 0;

	g.FillRectangle(&SolidBrush(Color(iRectAlpha, 0, 0, 0)), (int)vPos.x, (int)vPos.y, 100, 30);




	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("Impact"));
	HFONT hDefaultFont = (HFONT)SelectObject(_dc, hFont);

	SetTextColor(_dc, RGB(int(250.f * fRatio), int(250.f * fRatio), int(250.f * fRatio)));
	swprintf_s(szBuff, L"[BOSS] DRAGON");
	TextOut(_dc, (int)vPos.x + 4, (int)vPos.y + 8, szBuff, lstrlen(szBuff));

	SetTextColor(_dc, RGB(int(250.f * fRatio), int(50.f * fRatio), int(50.f * fRatio)));
	TextOut(_dc, (int)vPos.x + 3, (int)vPos.y + 8, szBuff, lstrlen(szBuff));
	SelectObject(_dc, hDefaultFont);
	DeleteObject(hFont);


}


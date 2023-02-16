#include "stdafx.h"
#include "CEffects_DeadUI.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"

CEffects_DeadUI::CEffects_DeadUI()
{
}

CEffects_DeadUI::~CEffects_DeadUI()
{
}

void CEffects_DeadUI::Initialize()
{
	m_vPos = Vec2((float)WINCX * 0.5f, (float)WINCY * 0.5f);
	m_vScale = Vec2(160.f, 100.f);
	m_tInfo.fFadeSpeed = 200.f;
	m_tInfo.iAlpha = 50;
	m_fTime = 0.f;
}

void CEffects_DeadUI::Update()
{
}

void CEffects_DeadUI::Render(HDC _dc)
{

	Graphics g(_dc);
	TCHAR szBuff[64];
	int iRand = random(0, 5);
	int iAlpha = m_tInfo.iAlpha;



	HFONT hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	HFONT hDefaultFont = (HFONT)SelectObject(_dc, hFont);

	//네모 5개
	for (int i = 0; i < 5; ++i)
	{
		g.FillRectangle(&SolidBrush(Color(iAlpha, 0, 0, 0))
			, (int)(m_vPos.x - m_vScale.x * 0.5f) + i * 4
			, (int)(m_vPos.y - m_vScale.y * 0.5f) + i * 4
			, (int)m_vScale.x - i * 8
			, (int)m_vScale.y - i * 8
		);
	}

	
	SetTextColor(_dc, RGB(250, 50, 240));


	swprintf_s(szBuff, L"아니...");
	TextOut(_dc, (int)m_vPos.x - 9, (int)m_vPos.y - 25, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"통하지 않을 거야.");
	TextOut(_dc, (int)m_vPos.x - 44, (int)m_vPos.y - 10, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"(R키로 재시작)");
	TextOut(_dc, (int)m_vPos.x - 39, (int)m_vPos.y + 20, szBuff, lstrlen(szBuff));


	if (iRand == 1)
		SetTextColor(_dc, RGB(0, 100, 150));
	else if (iRand == 2)
		SetTextColor(_dc, RGB(0, 200, 200));
	else
		SetTextColor(_dc, RGB(50, 255, 255));

	swprintf_s(szBuff, L"아니...");
	TextOut(_dc, (int)m_vPos.x - 10, (int)m_vPos.y - 25, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"통하지 않을 거야.");
	TextOut(_dc, (int)m_vPos.x - 45, (int)m_vPos.y - 10, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"(R키로 재시작)");
	TextOut(_dc, (int)m_vPos.x - 40, (int)m_vPos.y + 20, szBuff, lstrlen(szBuff));

	SelectObject(_dc, hDefaultFont);
	DeleteObject(hFont);


}


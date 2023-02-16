#include "stdafx.h"
#include "CEffects_Clear.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CEditor.h"

CEffects_Clear::CEffects_Clear()
{
}

CEffects_Clear::~CEffects_Clear()
{
}

void CEffects_Clear::Initialize()
{
	//m_vPos = Vec2((float)WINCX * 0.5f, (float)WINCY * 0.5f);
	m_vScale = Vec2(160.f, 100.f);
	m_tInfo.fFadeSpeed = 200.f;
	m_tInfo.iAlpha = 50;
	m_fTime = 0.f;

	float fLastRecord = CEditor::Get_Instance()->LoadTimeRecord(5);
	float fCurRecord = (float)g_iMinute * 60.f + (float)g_iSec + g_fTime;
	if (fCurRecord < fLastRecord)
	{
		CEditor::Get_Instance()->SaveTimeRecord(5);
		m_bNewRecord = true;
	}
}

void CEffects_Clear::Update()
{
}

void CEffects_Clear::Render(HDC _dc)
{

	Graphics g(_dc);
	TCHAR szBuff[64];
	int iRand = 5;
	int iAlpha = m_tInfo.iAlpha;
	Vec2 vPos = CCamera::Get_Instance()->Get_RenderPos(m_vPos);


	HFONT hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	HFONT hDefaultFont = (HFONT)SelectObject(_dc, hFont);

	//네모 5개
	/*for (int i = 0; i < 5; ++i)
	{
		g.FillRectangle(&SolidBrush(Color(iAlpha, 0, 0, 0))
			, (int)(vPos.x - m_vScale.x * 0.5f) + i * 4
			, (int)(vPos.y - m_vScale.y * 0.5f) + i * 4
			, (int)m_vScale.x - i * 8
			, (int)m_vScale.y - i * 8
		);
	}*/


	SetTextColor(_dc, RGB(250, 50, 240));


	swprintf_s(szBuff, L"CLEAR");
	TextOut(_dc, (int)vPos.x - 19, (int)vPos.y - 25, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"모두 수고하셨습니당 ㅎ");
	TextOut(_dc, (int)vPos.x - 60, (int)vPos.y - 10, szBuff, lstrlen(szBuff));

	int iTime = int(g_fTime * 100.f);
	swprintf_s(szBuff, L"최종 기록 [%.2d:%2d.%2d]", g_iMinute, g_iSec, iTime);
	TextOut(_dc, (int)vPos.x - 57, (int)vPos.y + 20, szBuff, lstrlen(szBuff));


	if (iRand == 1)
		SetTextColor(_dc, RGB(0, 100, 150));
	else if (iRand == 2)
		SetTextColor(_dc, RGB(0, 200, 200));
	else
		SetTextColor(_dc, RGB(50, 255, 255));

	swprintf_s(szBuff, L"CLEAR");
	TextOut(_dc, (int)vPos.x - 20, (int)vPos.y - 25, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"모두 수고하셨습니당 ㅎ");
	TextOut(_dc, (int)vPos.x - 61, (int)vPos.y - 10, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"최종 기록 [%.2d:%2d.%2d]", g_iMinute, g_iSec, iTime);
	TextOut(_dc, (int)vPos.x - 58, (int)vPos.y + 20, szBuff, lstrlen(szBuff));

	if (m_bNewRecord)
	{
		swprintf_s(szBuff, L"!! 신기록 갱신 !!");
		TextOut(_dc, (int)vPos.x - 50, (int)vPos.y + 40, szBuff, lstrlen(szBuff));
	}
	


	SelectObject(_dc, hDefaultFont);
	DeleteObject(hFont);


}


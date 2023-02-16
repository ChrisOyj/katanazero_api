#include "stdafx.h"
#include "CEffects_PlayMusic.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"

CEffects_PlayMusic::CEffects_PlayMusic()
{
}

CEffects_PlayMusic::~CEffects_PlayMusic()
{
}

void CEffects_PlayMusic::Initialize()
{
	m_vPos = Vec2(-150.f, (float)WINCY - 60.f);
	m_vTargetPos = Vec2(25.f, (float)WINCY - 60.f);
	m_vScale = Vec2(130.f, 45.f);
	m_tInfo.fFadeSpeed = 200.f;
	m_tInfo.iAlpha = 150;
	m_fTimeLimit = 5.f;
	m_fTime = 0.f;
}

void CEffects_PlayMusic::Update()
{
	if (m_vPos.x < m_vTargetPos.x - 3.f)
	{
		m_fSpeed = (m_vTargetPos.x - m_vPos.x) * 0.05f;
		m_vPos.x += m_fSpeed;
	}
	else
	{
		m_tInfo.bDelete = true;
	}


	if (m_tInfo.bDelete)
	{
		m_fTime += RealfDT;
		if (m_fTimeLimit < m_fTime)
			m_tInfo.iAlpha -= (int)(m_tInfo.fFadeSpeed * RealfDT);

		if (m_tInfo.iAlpha < 5)
			DeleteObject(this);
	}

}

void CEffects_PlayMusic::Render(HDC _dc)
{
	Graphics g(_dc);
	TCHAR szBuff[64];
	int iRand = random(0, 5);
	float fRatio = (float)m_tInfo.iAlpha / 150.f;

	

	HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	HFONT hDefaultFont = (HFONT)SelectObject(_dc, hFont);
	
	//가로 그림자
	g.FillRectangle(&SolidBrush(Color(m_tInfo.iAlpha, 150, 0, 150))
		, (int)m_vPos.x + 4
		, (int)(m_vPos.y + m_vScale.y)
		, (int)m_vScale.x
		, 2);
	//세로 그림자
	g.FillRectangle(&SolidBrush(Color(m_tInfo.iAlpha, 150, 0, 150))
		, (int)(m_vPos.x + m_vScale.x)
		, (int)(m_vPos.y) +4
		, 2
		, (int)m_vScale.y);
	g.FillRectangle(&SolidBrush(Color(m_tInfo.iAlpha, 50, 0, 120)), (int)m_vPos.x, (int)m_vPos.y, (int)m_vScale.x, (int)m_vScale.y);
	g.FillRectangle(&SolidBrush(Color(m_tInfo.iAlpha+105, 240, 50, 220)), (int)m_vPos.x+5, (int)m_vPos.y+25, (int)(m_vScale.x * 0.6f), 1);
	swprintf_s(szBuff, L"재생 중인 곡 ♬");

	SetTextColor(_dc, RGB(int(230.f * fRatio), int(50.f * fRatio), int(255.f * fRatio)));
	TextOut(_dc, (int)m_vPos.x + 4, (int)m_vPos.y+3, szBuff, lstrlen(szBuff));

	SetTextColor(_dc, RGB(int(90.f * fRatio), int(255.f * fRatio), int(255.f * fRatio)));

	if (iRand == 1)
		SetTextColor(_dc, RGB(20, 20, 20));
	TextOut(_dc, (int)m_vPos.x + 5, (int)m_vPos.y+3, szBuff, lstrlen(szBuff));
	SelectObject(_dc, hDefaultFont);
	DeleteObject(hFont);




	SetTextColor(_dc, RGB(int(70.f * fRatio), int(255.f * fRatio), int(255.f * fRatio)));

	hFont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	hDefaultFont = (HFONT)SelectObject(_dc, hFont);

	if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::START)
		swprintf_s(szBuff, L"코딩할 때 듣기 좋은 음악");
	else
		swprintf_s(szBuff, L"시연회날 듣기 좋은 음악");
	TextOut(_dc, (int)m_vPos.x + 4, (int)m_vPos.y + 30, szBuff, lstrlen(szBuff));
	SelectObject(_dc, hDefaultFont);
	DeleteObject(hFont);


}


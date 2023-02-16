#include "stdafx.h"
#include "CMenu.h"

#include "CKeyMgr.h"

#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CSoundMgr.h"

#include "CScene.h"

int		g_iSound = 50;
int		g_iVibSpeed = 100;

CMenu::CMenu()
	: m_iSelect(0)
	, m_fColor(255.f)
	, m_iPhase(0)
{
}

CMenu::~CMenu()
{
}

void CMenu::Initialize()
{
}

void CMenu::Update()
{
	if (KEY(ESC, TAP))
		DeleteObject(this);

	

	switch (m_iPhase)
	{
	case 0:
		Update_Default();

		break;

	case 1:
		Update_Option();

		break;

	}

	

	
}

void CMenu::Render(HDC _dc)
{
	//=================== 화면 효과 =============================

	Vec2 vPos = CCamera::Get_Instance()->Get_RealPos(Vec2(0.f, 0.f));
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);

	Graphics g(_dc);

	int iRand = random(50, 100);
	int iCount = 10;
	int iAlpha = 150;

	if (m_iPhase == 1)
		iAlpha = 230;


	g.FillRectangle(&SolidBrush(Color(iAlpha, 60, 10, 255)), (int)vPos.x, (int)vPos.y, (int)WINCX, (int)WINCY);

	int iRandY = random(0, 400);
	int iRandY2 = random(1, 4);
	vPos.y += (float)iRandY;
	g.FillRectangle(&SolidBrush(Color(60, 0, 255 - iRand, 150 + iRand)), (int)vPos.x, (int)vPos.y, (int)WINCX, iRandY2);
	vPos.y -= (float)iRandY;


	iRandY2 = random(10, (int)WINCY - 10);


	//흰 줄
	for (int i = 0; i < iCount; ++i)
	{
		iRandY = random(3, 20);
		int iRandX = random(0, (int)WINCX - 10);
		iAlpha = random(50, 190);

		g.FillRectangle(&SolidBrush(Color(iAlpha, 255, 255, 255)), (int)vPos.x + iRandX, (int)vPos.y + iRandY2, iRandY, 1);
	}

	//==========================================================

	if (m_iPhase == 0)
	{
		Render_Default(_dc);
	}
	else
		Render_Option(_dc);

}

void CMenu::Update_Default()
{
	if (KEY(W, TAP) && m_iSelect > 0)
	{
		m_iSelect--;
		CSoundMgr::Get_Instance()->PlaySound(L"Menu_Select.wav");
	}

	if (KEY(S, TAP) && m_iSelect < 3)
	{
		m_iSelect++;
		CSoundMgr::Get_Instance()->PlaySound(L"Menu_Select.wav");
	}

	if (KEY(SPACE, TAP))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Menu_Choice.wav");


		switch (m_iSelect)
		{
		case 0:
			DeleteObject(this);
			CTimeMgr::Get_Instance()->SetTimeSpeed(1.f);
			break;

		case 1:
			break;

		case 2:
			m_iSelect = 0;
			m_iPhase = 1;
			break;

			
		case 3:
			//CSceneMgr::Get_Instance()->Get_CurScene()->DeleteEventAll();
			CTimeMgr::Get_Instance()->SetTimeSpeed(1.f);
			ChangeScene(SCENE_TYPE::MAINMENU);
			break;
		}
	}

	if (m_bColorPlus)
	{
		m_fColor += (1000.f * RealfDT);
		if (m_fColor >= 255)
		{
			m_fColor = 255;
			m_bColorPlus = false;
		}
	}
	else
	{
		m_fColor -= (1000.f * RealfDT);
		if (m_fColor <= 0)
		{
			m_fColor = 0;
			m_bColorPlus = true;
		}
	}
}

void CMenu::Update_Option()
{
	if (KEY(W, TAP) && m_iSelect > 0)
	{
		m_iSelect--;
		CSoundMgr::Get_Instance()->PlaySound(L"Menu_Select.wav");
	}

	if (KEY(S, TAP) && m_iSelect < 6)
	{
		m_iSelect++;
		CSoundMgr::Get_Instance()->PlaySound(L"Menu_Select.wav");
	}

	if (KEY(SPACE, TAP))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Menu_Choice.wav");

		switch (m_iSelect)
		{
		case 0:
			//볼륨
			break;

		case 1:
			//진동세기
			break;

		case 2:
			//시네마틱모드
			g_bCinema = !g_bCinema;
			break;

		case 3:
			//레이져
			g_bLaser = !g_bLaser;
			break;

		case 4:
			//고스트
			g_bGhost = !g_bGhost;
			break;

		case 5:
			//고스트
			g_bSuper = !g_bSuper;
			break;


		case 6:
			m_iPhase = 0;
			m_iSelect = 0;
			break;
		}
	}

	if (KEY(UP, HOLD))
	{
		switch (m_iSelect)
		{
		case 0:
			//볼륨
			if (g_iSound < 100)
			{
				g_iSound++;
				g_fSound = (float)g_iSound * 0.01f;
				CSoundMgr::Get_Instance()->SetChannelVolume(BGM, g_fSound);
			}

			break;

		case 1:
			//진동세기
			if (g_iVibSpeed < 100)
			{
				g_iVibSpeed++;
				float fSpeed = (float)g_iVibSpeed * 0.01f * 2000.f;
				CCamera::Get_Instance()->SetVibSpeed(fSpeed);
			}
			break;

		default:
			break;
		}
	}

	if (KEY(DOWN, HOLD))
	{
		switch (m_iSelect)
		{
		case 0:
			//볼륨
			if (g_iSound > 0)
			{
				g_iSound--;
				g_fSound = (float)g_iSound * 0.01f;
				CSoundMgr::Get_Instance()->SetChannelVolume(BGM, g_fSound);
			}

			break;

		case 1:
			//진동세기
			if (g_iVibSpeed > 0)
			{
				g_iVibSpeed--;
				float fSpeed = (float)g_iVibSpeed * 0.01f * 2000.f;
				CCamera::Get_Instance()->SetVibSpeed(fSpeed);
			}
			break;

		default:
			break;
		}
	}


}

void CMenu::Render_Default(HDC _dc)
{
	//================텍스트=======================
	Vec2 vPos = CCamera::Get_Instance()->Get_RealPos(Vec2(30, 10));
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	TCHAR szBuff[64];
	int iRand = random(0, 5);

	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
	HFONT hDefaultFont = (HFONT)SelectObject(_dc, hFont);

	//텍스트 색상 변환
	SetTextColor(_dc, RGB(50, 250, 250));
	if (m_iSelect == 0)
	{
		SetTextColor(_dc, RGB(255, (int)m_fColor, 255));
		Render_Select(_dc, vPos);
	}

	swprintf_s(szBuff, L"이어하기");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));


	SetTextColor(_dc, RGB(50, 250, 250));
	if (m_iSelect == 1)
	{
		SetTextColor(_dc, RGB(255, (int)m_fColor, 255));
		Render_Select(_dc, vPos);
	}

	swprintf_s(szBuff, L"재시작");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));


	SetTextColor(_dc, RGB(50, 250, 250));
	if (m_iSelect == 2)
	{
		SetTextColor(_dc, RGB(255, (int)m_fColor, 255));
		Render_Select(_dc, vPos);
	}

	swprintf_s(szBuff, L"설정");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));


	SetTextColor(_dc, RGB(50, 250, 250));
	if (m_iSelect == 3)
	{
		SetTextColor(_dc, RGB(255, (int)m_fColor, 255));
		Render_Select(_dc, vPos);
	}

	swprintf_s(szBuff, L"메인 메뉴");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));


	//===========================================
	SelectObject(_dc, hDefaultFont);
	DeleteObject(hFont);
}

void CMenu::Render_Option(HDC _dc)
{
	//================텍스트=======================
	Vec2 vPos = CCamera::Get_Instance()->Get_RealPos(Vec2(10, 10));
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	TCHAR szBuff[64];
	int iRand = random(0, 5);

	HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
	HFONT hDefaultFont = (HFONT)SelectObject(_dc, hFont);

	//텍스트 색상 변환
	SetTextColor(_dc, RGB(255, 255, 255));

	if (m_iSelect == 0)
	{
		SetTextColor(_dc, RGB(0, 0, 255));
		Render_Select2(_dc, vPos);
	}

	swprintf_s(szBuff, L"음악 볼륨");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L":       %d%%", g_iSound);
	TextOut(_dc, (int)vPos.x + 150, (int)(vPos.y), szBuff, lstrlen(szBuff));


	SetTextColor(_dc, RGB(255, 255, 255));
	if (m_iSelect == 1)
	{
		SetTextColor(_dc, RGB(0, 0, 255));
		Render_Select2(_dc, vPos);
	}

	swprintf_s(szBuff, L"화면 떨림");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L":       %d%%", g_iVibSpeed);
	TextOut(_dc, (int)vPos.x + 150, (int)(vPos.y), szBuff, lstrlen(szBuff));


	SetTextColor(_dc, RGB(255, 255, 255));
	if (m_iSelect == 2)
	{
		SetTextColor(_dc, RGB(0, 0, 255));
		Render_Select2(_dc, vPos);
	}

	swprintf_s(szBuff, L"시네마틱 모드");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));

	if (g_bCinema)
		swprintf_s(szBuff, L":       ON");
	else
		swprintf_s(szBuff, L":       OFF");
	TextOut(_dc, (int)vPos.x + 150, (int)(vPos.y), szBuff, lstrlen(szBuff));

	SetTextColor(_dc, RGB(255, 255, 255));
	if (m_iSelect == 3)
	{
		SetTextColor(_dc, RGB(0, 0, 255));
		Render_Select2(_dc, vPos);
	}

	swprintf_s(szBuff, L"레이져 블레이드");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));

	if (g_bLaser)
		swprintf_s(szBuff, L":       ON");
	else
		swprintf_s(szBuff, L":       OFF");
	TextOut(_dc, (int)vPos.x + 150, (int)(vPos.y), szBuff, lstrlen(szBuff));

	SetTextColor(_dc, RGB(255, 255, 255));
	if (m_iSelect == 4)
	{
		SetTextColor(_dc, RGB(0, 0, 255));
		Render_Select2(_dc, vPos);
	}

	swprintf_s(szBuff, L"고스트 모드");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));

	if (g_bGhost)
		swprintf_s(szBuff, L":       ON");
	else
		swprintf_s(szBuff, L":       OFF");
	TextOut(_dc, (int)vPos.x + 150, (int)(vPos.y), szBuff, lstrlen(szBuff));

	SetTextColor(_dc, RGB(255, 255, 255));
	if (m_iSelect == 5)
	{
		SetTextColor(_dc, RGB(0, 0, 255));
		Render_Select2(_dc, vPos);
	}

	swprintf_s(szBuff, L"무적");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));

	if (g_bSuper)
		swprintf_s(szBuff, L":       ON");
	else
		swprintf_s(szBuff, L":       OFF");
	TextOut(_dc, (int)vPos.x + 150, (int)(vPos.y), szBuff, lstrlen(szBuff));

	SetTextColor(_dc, RGB(255, 255, 255));
	if (m_iSelect == 6)
	{
		SetTextColor(_dc, RGB(0, 0, 255));
		Render_Select2(_dc, vPos);
	}

	swprintf_s(szBuff, L"뒤로");
	TextOut(_dc, (int)vPos.x, (int)(vPos.y += 40.f), szBuff, lstrlen(szBuff));


	//===========================================
	SelectObject(_dc, hDefaultFont);
	DeleteObject(hFont);
}

void CMenu::Render_Select(HDC _dc, Vec2 _vPos)
{
	Graphics g(_dc);
	Vec2 vPos = _vPos;
	vPos.y += 40.f;
	vPos.y -= 7.f;

	g.FillRectangle(&SolidBrush(Color(50, 255, 255, 255)), 0, (int)vPos.y, (int)WINCX, 30);

	//흰 줄
	for (int i = 0; i < 100; ++i)
	{
		int iRandY = random(0, 30);
		int iRandX = random(0, (int)WINCX - 10);
		int iRandCX = random(3, 13);
		int iAlpha = random(50, 255);

		g.DrawLine(&Pen(Color(iAlpha, 255, 255, 255)), Point(iRandX, (INT)vPos.y + iRandY), Point(iRandX + iRandCX, (INT)vPos.y + iRandY));

		//g.FillRectangle(&SolidBrush(Color(iAlpha, 255, 255, 255)), (int)vPos.x + iRandX, (int)vPos.y + iRandY2, iRandY, 1);
	}

}

void CMenu::Render_Select2(HDC _dc, Vec2 _vPos)
{
	Graphics g(_dc);
	Vec2 vPos = _vPos;
	vPos.y += 40.f;
	vPos.y -= 7.f;

	g.FillRectangle(&SolidBrush(Color(255, 255, 255, 255)), 0, (int)vPos.y, (int)WINCX, 30);

}

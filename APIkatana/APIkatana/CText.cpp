#include "stdafx.h"
#include "CText.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CMainGame.h"
#include "CSoundMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CEffects_Rain.h"
#include "CAbstractFactory.h"


CText::CText()
	: m_iSelected(0)
	, m_fAlpha(0.7f)
	, m_bUP(true)
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Font_New", L"texture\\font\\Font_New.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Font_New", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Font_Game", L"texture\\font\\Font_Game.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Font_Game", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Font_Option", L"texture\\font\\Font_Option.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Font_Option", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Font_Exit", L"texture\\font\\Font_Exit.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Font_Exit", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
		1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	SetRatio(0.7f);
}

CText::~CText()
{
}

void CText::Initialize()
{
}

void CText::Update()
{
	if (m_iSelected == 10)
	{
		m_fTime += RealfDT;

		if (0.6f < m_fTime)
		{
			ChangeScene(SCENE_TYPE::START);
		}
		return;
	}

	if (m_iSelected == 20)
	{
		m_fTime += RealfDT;

		if (0.6f < m_fTime)
		{
			ChangeScene(SCENE_TYPE::TOOL);
		}
		return;
	}

	if (m_iSelected == 30)
	{
		DestroyWindow(g_hwnd);
		return;
	}

	CreateRain();



	if (KEY(W, TAP))
	{
		if (0 < m_iSelected)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"MainMenu_Select.wav");
			--m_iSelected;

		}
	}
	if (KEY(S, TAP))
	{
		if (2 > m_iSelected)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"MainMenu_Select.wav");
			++m_iSelected;

		}
	}
	if (KEY(SPACE, TAP))
		Select();




	if (1.f <= m_fAlpha)
		m_bUP = false;
	else if (0.7f >= m_fAlpha)
		m_bUP = true;

	if (m_bUP)
		m_fAlpha += 1.0f * RealfDT;
	else
		m_fAlpha -= 1.0f * RealfDT;

}

void CText::Render(HDC _dc)
{
	SetPos(Vec2(295.f, 227.f));
	Vec2 vPos = Get_Pos();

	if (0 == m_iSelected)
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, m_fAlpha, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.7f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}

	Get_Animator()->Play(L"Font_New", false);
	Get_Animator()->Render(_dc);

	vPos.x += 57.f;
	SetPos(vPos);
	Get_Animator()->Play(L"Font_Game", false);
	Get_Animator()->Render(_dc);


	if (1 == m_iSelected)
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, m_fAlpha, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.7f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}

	vPos.x -= 25.f;
	vPos.y += 25.f;
	SetPos(vPos);
	Get_Animator()->Play(L"Font_Option", false);
	Get_Animator()->Render(_dc);

	if (2 == m_iSelected)
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, m_fAlpha, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.7f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}

	vPos.y += 25.f;
	SetPos(vPos);
	Get_Animator()->Play(L"Font_Exit", false);
	Get_Animator()->Render(_dc);
}

void CText::Select()
{
	CSoundMgr::Get_Instance()->PlaySound(L"MainMenu_Choice.wav");

	switch (m_iSelected)
	{
	case 0:
		m_iSelected = 10;
		break;

	case 1:
		m_iSelected = 20;

		break;

	case 2:
		m_iSelected = 30;

		break;
	}

	CSceneMgr::Get_Instance()->SceneChange(false);

}

void CText::CreateRain()
{
	int iRandX = random(20, 600);

	Vec2 vPos{ (float)iRandX, 0.f };

	CObj* pRain = CAbstractFactory<CEffects_Rain>::Create();
	pRain->SetPos(vPos);
	CreateObject(pRain, GROUP_TYPE::UI);
}

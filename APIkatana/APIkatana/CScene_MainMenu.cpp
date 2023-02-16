#include "stdafx.h"
#include "CScene_MainMenu.h"

#include "CKeyMgr.h"
#include "CCamera.h"
#include "CSoundMgr.h"

#include "CObj.h"
#include "CMainMenu.h"
#include "CText.h"
#include "CSelector.h"
#include "CEffects_DarkScreen.h"


CScene_MainMenu::CScene_MainMenu()
{
}

CScene_MainMenu::~CScene_MainMenu()
{
}

void CScene_MainMenu::Update()
{
	CScene::Update();
}

void CScene_MainMenu::Enter(bool _replay)
{
	g_fTime = 0.f;
	g_iMinute = 0;
	g_iSec = 0;

	CObj* pObj = new CMainMenu;

	pObj->SetPos(Vec2((float)WINCX * 0.5f, (float)WINCY * 0.5f));

	AddObject(pObj, GROUP_TYPE::UI);

	pObj = new CSelector;
	AddObject(pObj, GROUP_TYPE::UI);

	pObj = new CText;
	AddObject(pObj, GROUP_TYPE::UI);


	pObj = new CEffects_DarkScreen;
	dynamic_cast<CEffects*>(pObj)->Set_Alpha(255);
	dynamic_cast<CEffects*>(pObj)->Set_FadeSpeed(300.f);
	dynamic_cast<CEffects*>(pObj)->Set_Delete();
	AddObject(pObj, GROUP_TYPE::UI);

	CCamera::Get_Instance()->SetLookAt(Vec2((float)WINCX * 0.5f, (float)WINCY * 0.5f));

	CSoundMgr::Get_Instance()->StopSound(BGM);

	CSoundMgr::Get_Instance()->PlayBGM(L"Music_MainMenu.wav", g_fSound);
}

void CScene_MainMenu::Exit()
{
	CSoundMgr::Get_Instance()->StopSound(BGM);
	//DeleteEventAll();

	DeleteAll();
}

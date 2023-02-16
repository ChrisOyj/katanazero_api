#include "stdafx.h"
#include "CScene_Stage3.h"

#include "CObj.h"
#include "CPlayer.h"

#include "CCursor.h"
#include "CUI_hud.h"

#include "CSceneChange.h"

#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CCollisionMgr.h"
#include "CLineMgr.h"
#include "CTexture.h"
#include "CSoundMgr.h"
#include "CEditor.h"
#include "CPortal.h"
#include "CPortal_Stage3.h"
#include "CGhost.h"

#include "CCamera.h"

#include "CAbstractFactory.h"

CScene_Stage3::CScene_Stage3()
{
}

CScene_Stage3::~CScene_Stage3()
{
}

void CScene_Stage3::Enter(bool _replay)
{
	if (!_replay)
	{
		CSceneMgr::Get_Instance()->SceneChange(true);
		CLineMgr::Get_Instance()->Initialize();
	}

	//커서
	CObj* pObj = new CCursor;
	AddObject(pObj, GROUP_TYPE::CURSOR);

	//오브젝트 로드
	CEditor::Get_Instance()->Set_Stage(3);

	//UI
	pObj = CAbstractFactory<CUI_hud>::Create();
	pObj->SetOwner(Get_Player());
	dynamic_cast<CUI_hud*>(pObj)->SetCurTime();
	AddObject(pObj, GROUP_TYPE::UI);

	CLineMgr::Get_Instance()->Set_Player(Get_Player());

	//Portal
	pObj = CAbstractFactory<CPortal_Stage3>::Create(630.f, 210.f, GROUP_TYPE::MONSTER);
	AddObject(pObj, GROUP_TYPE::MONSTER);

	//Ghost
	pObj = CAbstractFactory<CGhost>::Create();
	AddObject(pObj, GROUP_TYPE::UI);

	// Camera Look 지정
	CCamera::Get_Instance()->SetLookAt(Vec2(WINCX / 2.f, WINCY / 2.f));
	CCamera::Get_Instance()->SetTarget(Get_Player());
}

void CScene_Stage3::Exit()
{
	DeleteEventAll();
	CLineMgr::Get_Instance()->Release();
	//CCollisionMgr::Get_Instance()->Reset(); // 그룹 충돌 체크 해놓은거 다 리셋
}

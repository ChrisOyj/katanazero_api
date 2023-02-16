#include "stdafx.h"
#include "CScene_Boss.h"

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

#include "CCamera.h"

#include "CAbstractFactory.h"
#include "CBoss.h"

CScene_Boss::CScene_Boss()
	: m_iDragonCount(3)
{
}

CScene_Boss::~CScene_Boss()
{
}

void CScene_Boss::Enter(bool _replay)
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
	CEditor::Get_Instance()->Set_Stage(4);

	//UI
	pObj = CAbstractFactory<CUI_hud>::Create();
	pObj->SetOwner(Get_Player());
	dynamic_cast<CUI_hud*>(pObj)->SetCurTime();
	AddObject(pObj, GROUP_TYPE::UI);

	CLineMgr::Get_Instance()->Set_Player(Get_Player());

	//BOSS
	pObj = CAbstractFactory<CBoss>::Create(Vec2(500.f, 280.f), GROUP_TYPE::MONSTER);
	pObj->SetOwner(Get_Player());
	pObj->SetDir(Vec2(-1.f, 0.f));
	pObj->SetRenderDir(Vec2(-1.f, 0.f));
	dynamic_cast<CAlive*>(pObj)->SetOriginY(280.f);
	if (!_replay)
	{
		dynamic_cast<CAlive*>(pObj)->Animation();
			
	}
	AddObject(pObj, GROUP_TYPE::MONSTER);


	//if (!_replay)
	//{
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LAND);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::CEILING);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SUBWEAPON);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MANSION);

	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_HITBOX, GROUP_TYPE::CEILING);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::LAND);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WALL);

	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MONSTER_HITBOX);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MONSTER_ATTACK);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MANSION);

	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::PLAYER_HITBOX);
	//	//CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::CEILING);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::WALL);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::LAND);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::SUBATTACK);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_SIGHT, GROUP_TYPE::PLAYER_HITBOX);

	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::MONSTER_HITBOX);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::WALL);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::CEILING);
	//	CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::LAND);
	//}


	// Camera Look 지정
	CCamera::Get_Instance()->SetLookAt(Vec2(WINCX / 2.f + 50.f, WINCY / 2.f));
	CCamera::Get_Instance()->SetTarget(pObj);
}

void CScene_Boss::Exit()
{
	DeleteEventAll();
	CLineMgr::Get_Instance()->Release();
	//CCollisionMgr::Get_Instance()->Reset(); // 그룹 충돌 체크 해놓은거 다 리셋
}

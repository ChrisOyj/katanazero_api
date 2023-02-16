#include "stdafx.h"
#include "CScene_Start.h"

#include "CObj.h"
#include "CPlayer.h"

#include "CCursor.h"
#include "CUI_hud.h"
#include "CPortal.h"
#include "CFall.h"

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

#include "CGhost.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter(bool _replay)
{
	if (!_replay)
	{
		CSceneMgr::Get_Instance()->SceneChange(true);
		CLineMgr::Get_Instance()->Initialize();
	}

	//Ä¿¼­
	CObj* pObj = new CCursor;
	AddObject(pObj, GROUP_TYPE::CURSOR);

	//¿ÀºêÁ§Æ® ·Îµå
	CEditor::Get_Instance()->Set_Stage(1);
	if (!_replay)
		dynamic_cast<CPlayer*>(Get_Player())->SetPlayMusic();

	//UI
	pObj = CAbstractFactory<CUI_hud>::Create();
	pObj->SetOwner(Get_Player());
	dynamic_cast<CUI_hud*>(pObj)->SetCurTime();
	AddObject(pObj, GROUP_TYPE::UI);

	CLineMgr::Get_Instance()->Set_Player(Get_Player());

	//Portal
	pObj = CAbstractFactory<CPortal>::Create(2290.f, 90.f, GROUP_TYPE::MONSTER);
	AddObject(pObj, GROUP_TYPE::MONSTER);

	//Fall
	pObj = CAbstractFactory<CFall>::Create(1950.f, 500.f, GROUP_TYPE::MANSION);
	AddObject(pObj, GROUP_TYPE::MANSION);

	//Ghost
	pObj = CAbstractFactory<CGhost>::Create();
	AddObject(pObj, GROUP_TYPE::UI);

	


	//Ãæµ¹ Ã¼Å©

	//Player ±×·ì°ú monster ±×·ìÀÇ ®G
	/*if (!_replay)
	{
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LAND);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::CEILING);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SUBWEAPON);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MANSION);

		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_HITBOX, GROUP_TYPE::CEILING);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::LAND);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WALL);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MANSION);

		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MONSTER_HITBOX);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MONSTER_ATTACK);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MANSION);

		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::PLAYER_HITBOX);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::WALL);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::LAND);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MONSTER_SIGHT, GROUP_TYPE::PLAYER_HITBOX);

		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::LASER, GROUP_TYPE::PLAYER);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::LASER, GROUP_TYPE::MONSTER);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::LASER_ATTACK, GROUP_TYPE::PLAYER_HITBOX);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::LASER_ATTACK, GROUP_TYPE::PLAYER);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::LASER_ATTACK, GROUP_TYPE::MONSTER_HITBOX);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::LASER_ATTACK, GROUP_TYPE::MONSTER);

		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::MONSTER_HITBOX);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::WALL);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::CEILING);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::LAND);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::MONSTER_ATTACK);

		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::PLAYER_HITBOX);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::WALL);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::CEILING);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::LAND);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::SLASH);

		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SMOKE, GROUP_TYPE::SMOKE);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SMOKE, GROUP_TYPE::PLAYER_HITBOX);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SMOKE, GROUP_TYPE::SLASH);
		CCollisionMgr::Get_Instance()->CheckGroup(GROUP_TYPE::SMOKE, GROUP_TYPE::MONSTER_HITBOX);
	}*/

	// Camera Look ÁöÁ¤
	CCamera::Get_Instance()->SetLookAt(Vec2(WINCX * 0.5f, WINCY * 0.5f));
	CCamera::Get_Instance()->SetTarget(Get_Player());
}

void CScene_Start::Exit()
{
	DeleteEventAll();
	//DeleteAll();
	CLineMgr::Get_Instance()->Release();
	//CCollisionMgr::Get_Instance()->Reset(); // ±×·ì Ãæµ¹ Ã¼Å© ÇØ³õÀº°Å ´Ù ¸®¼Â
}

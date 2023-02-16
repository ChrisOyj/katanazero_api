#include "stdafx.h"
#include "CPortal_Stage3.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CAbstractFactory.h"
#include "CScene.h"

#include "CMonster_Grant.h"
#include "CMonster_Gangster.h"
#include "CEffects_Go.h"

CPortal_Stage3::CPortal_Stage3()
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_MansionDoor", L"texture\\Effects\\Effects_MansionDoor.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	m_vScale.x = pTex->Width();
	m_vScale.y = pTex->Height();
	Get_Animator()->CreateAnimation(L"Effects_MansionDoor", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);
}

CPortal_Stage3::~CPortal_Stage3()
{
}

void CPortal_Stage3::Initialize()
{
	CPortal::Initialize();
}

void CPortal_Stage3::Update()
{

	if (!m_bClear && CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::MONSTER_SIGHT).empty())
	{
		if (m_bOpen)
		{
			m_bClear = true;
			Vec2 vPos = m_vPos;
			vPos.x -= 30.f;
			vPos.y -= 20.f;
			CAbstractFactory<CEffects_Go>::Create_Effects(vPos, GROUP_TYPE::UI);
			CSoundMgr::Get_Instance()->PlaySound(L"Clear.wav");

		}
		else
		{
			CSoundMgr::Get_Instance()->PlaySound(L"DoorOpen.wav");
			SetImage();
			m_bOpen = true;
			CAbstractFactory<CMonster_Gangster>::Create_Monster(CSceneMgr::Get_Instance()->Get_CurScene()->Get_Player(), m_vPos, Vec2(1.f, 0.f));
			CObj* pMonster = CAbstractFactory<CMonster_Grant>::Create(m_vPos, GROUP_TYPE::MONSTER);
			pMonster->SetOwner(CSceneMgr::Get_Instance()->Get_CurScene()->Get_Player());
			dynamic_cast<CAlive*>(pMonster)->SetOriginY(m_vPos.y);
			dynamic_cast<CAlive*>(pMonster)->Run();
			CreateObject(pMonster, GROUP_TYPE::MONSTER);
		}


	}

	if (m_bChange)
	{
		m_fTime += RealfDT;
		if (0.6f < m_fTime)
		{
			m_fTime = 0.f;
			m_bChange = false;
			UINT curScene = (UINT)CSceneMgr::Get_Instance()->Get_CurSceneType();
			curScene++;
			ChangeScene(SCENE_TYPE(curScene));
		}
	}
}

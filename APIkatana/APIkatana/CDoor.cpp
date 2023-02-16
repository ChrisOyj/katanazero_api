#include "stdafx.h"
#include "CDoor.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CAbstractFactory.h"
#include "CScene.h"

#include "CMonster_Grant.h"
#include "CMonster_Gangster.h"
#include "CEffects_Go.h"

CDoor::CDoor()
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

CDoor::~CDoor()
{
}

void CDoor::OnCollisionEnter(CCollider * pOther)
{
	m_bOpen = true;
	CSoundMgr::Get_Instance()->PlaySound(L"DoorOpen.wav");
	m_pAnimator->Play(L"Effects_MansionDoor", false);
}

void CDoor::Initialize()
{
	CreateCollider();

	m_pCollider->SetScale(Vec2(10.f, 100.f));

	m_vPos = Vec2(945.f, 326.f);
}



void CDoor::Update()
{
	if (m_bOpen)
	{
		m_fTime += fDT;

		if (1.5f < m_fTime)
		{
			if (m_bCreate)
				DeleteObject(this);

			m_fTime = 0.f;
			m_bOpen = false;
			CSoundMgr::Get_Instance()->PlaySound(L"DoorClose.wav");
			m_pAnimator->Play(L"NOTHING", false);
		}
	}
	else if (m_pOwner->Get_Pos().y > 450.f)
	{
		m_bOpen = true;
		m_bCreate = true;
		CSoundMgr::Get_Instance()->PlaySound(L"DoorOpen.wav");
		m_pAnimator->Play(L"Effects_MansionDoor", false);
		CObj* pMonster = CAbstractFactory<CMonster_Grant>::Create(m_vPos, GROUP_TYPE::MONSTER);
		pMonster->SetOwner(CSceneMgr::Get_Instance()->Get_CurScene()->Get_Player());
		dynamic_cast<CAlive*>(pMonster)->SetOriginY(m_vPos.y);
		dynamic_cast<CAlive*>(pMonster)->Run();
		CreateObject(pMonster, GROUP_TYPE::MONSTER);
	}
}

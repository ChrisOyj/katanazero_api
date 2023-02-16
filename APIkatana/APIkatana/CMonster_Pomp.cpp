#include "stdafx.h"
#include "CMonster_Pomp.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CAbstractFactory.h"
#include "CEffects_PompSlash.h"

CMonster_Pomp::CMonster_Pomp()
{
	//애니메이터
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Pomp_Idle", L"texture\\Monster\\Monster_Pomp_Idle.png");
	iCount = 8;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"STANCE", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Pomp_Walk", L"texture\\Monster\\Monster_Pomp_Walk_10.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"WALK", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Pomp_Run", L"texture\\Monster\\Monster_Pomp_Run_10.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Pomp_Attack", L"texture\\Monster\\Monster_Pomp_Attack.png");
	iCount = 6;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ATTACK", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Pomp_Hit", L"texture\\Monster\\Monster_Pomp_Hit.png");
	iCount = 2;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"HIT", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Pomp_Death", L"texture\\Monster\\Monster_Pomp_Death_15.png");
	iCount = 15;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DEATH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Pomp_Parring", L"texture\\Monster\\Monster_Pomp_Parring_22.png");
	iCount = 22;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"PARRING", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	// =============== 오프셋 조정 ==================
	CAnimation* pAnim = Get_Animator()->FindAnimation(L"PARRING");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -1.f);

}

CMonster_Pomp::~CMonster_Pomp()
{
}


void CMonster_Pomp::Initialize()
{
	CMonster::Initialize();

	m_eMobType = MOB_TYPE::POMP;

	m_tPhysics.fOffsetY = 22.f;
	m_pCollider->SetScale(Vec2(50.f, 5.f));
	Get_Collider()->SetOffSetPos(Vec2(0.f, m_tPhysics.fOffsetY)); //오프셋 만져주면 충돌체 위치 바뀜
	Default();
	m_bAir = true;
}


void CMonster_Pomp::Update_Attack()
{
	if (dynamic_cast<CPlayer*>(m_pOwner)->IsSmoke())
	{
		Default();
		SetMark(MARK_TYPE::QUESTION);
		return;
	}

	STATE_TYPE eState = STATE_TYPE::END;

	if (m_pOwner)
		eState = dynamic_cast<CAlive*>(m_pOwner)->Get_State();

	if (eState == STATE_TYPE::DEATH || eState == STATE_TYPE::HIT)
	{
		Default();
		m_pOwner = nullptr;
	}

	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (m_fTime > 0.1f && 0 == m_iAttackCount)
	{
		CAbstractFactory<CEffects_PompSlash>::Create_Effects(this, m_vPos, m_vDir, GROUP_TYPE::MONSTER_ATTACK);
		m_iAttackCount++;
	}

	if (TimeLimit <= m_fTime)
	{
		Run();
		m_iAttackCount = 0;
	}
}
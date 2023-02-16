#include "stdafx.h"
#include "CMonster_Grant.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CAbstractFactory.h"
#include "CEffects_GrantSlash.h"



CMonster_Grant::CMonster_Grant()
{
	//애니메이터
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Grant_Stance", L"texture\\Monster\\Monster_Grant_Stance.png");
	iCount = 8;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"STANCE", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Grant_Walk", L"texture\\Monster\\Monster_Grant_Walk_10.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"WALK", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Grant_Run", L"texture\\Monster\\Monster_Grant_Run_10.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Grant_Attack", L"texture\\Monster\\Monster_Grant_Attack.png");
	iCount = 8;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ATTACK", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Grant_Hit", L"texture\\Monster\\Monster_Grant_Hit.png");
	iCount = 2;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"HIT", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Grant_Death", L"texture\\Monster\\Monster_Grant_Death_15.png");
	iCount = 15;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DEATH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	// =============== 오프셋 조정 ==================
	CAnimation* pAnim = Get_Animator()->FindAnimation(L"DEATH");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -1.f);

	pAnim = Get_Animator()->FindAnimation(L"ATTACK");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -4.f);

	pAnim = Get_Animator()->FindAnimation(L"RUN");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -1.f);

	
}

CMonster_Grant::~CMonster_Grant()
{
}

void CMonster_Grant::Initialize()
{
	CMonster::Initialize();

	m_eMobType = MOB_TYPE::GRANT;

	m_tPhysics.fOffsetY = 19.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, m_tPhysics.fOffsetY)); //오프셋 만져주면 충돌체 위치 바뀜
	Default();
	m_bAir = true;
}

//void CMonster_Grant::OnCollisionEnter(CCollider * _pOther)
//{
//	CMonster::OnCollisionEnter(_pOther);
//
//	CObj* pOtherObj = _pOther->Get_Obj();
//
//	if (pOtherObj->Get_ObjType() == GROUP_TYPE::PLAYER)
//	{
//		if (STATE_TYPE::RUN == m_eState)
//			Attack();
//
//	}
//}

void CMonster_Grant::Update_Attack()
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

	if (TimeLimit / 2.f <= m_fTime && 0 == m_iAttackCount)
	{
		CAbstractFactory<CEffects_GrantSlash>::Create_Effects(this, m_vPos, m_vDir, GROUP_TYPE::MONSTER_ATTACK);
		m_iAttackCount++;
	}

	if (TimeLimit <= m_fTime)
	{
		Run();
		m_iAttackCount = 0;
	}
}
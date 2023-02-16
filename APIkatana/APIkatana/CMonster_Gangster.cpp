#include "stdafx.h"
#include "CMonster_Gangster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMark.h"

CMonster_Gangster::CMonster_Gangster()
{
	//애니메이터
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Gangster_Stance_8", L"texture\\Monster\\Monster_Gangster_Stance_8.png");
	iCount = 8;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"STANCE", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Gangster_Walk_8", L"texture\\Monster\\Monster_Gangster_Walk_8.png");
	iCount = 8;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"WALK", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Gangster_Run_10", L"texture\\Monster\\Monster_Gangster_Run_10.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Gangster_Aim", L"texture\\Monster\\Monster_Gangster_Aim.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ATTACK", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Gangster_Hit", L"texture\\Monster\\Monster_Gangster_Hit.png");
	iCount = 2;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"HIT", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Gangster_Death_14", L"texture\\Monster\\Monster_Gangster_Death_14.png");
	iCount = 14;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DEATH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);
	

	// =============== 오프셋 조정 ==================
	CAnimation* pAnim = Get_Animator()->FindAnimation(L"DEATH");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 8.f);

	pAnim = Get_Animator()->FindAnimation(L"WALK");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 4.f);

	pAnim = Get_Animator()->FindAnimation(L"RUN");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 4.f);

	pAnim = Get_Animator()->FindAnimation(L"ATTACK");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -1.f);

}

CMonster_Gangster::~CMonster_Gangster()
{
}

void CMonster_Gangster::Initialize()
{
	CMonster::Initialize();

	m_eMobType = MOB_TYPE::GANGSTER;

	m_pSight->SetColSize(Vec2(700.f, 500.f));

	m_tPhysics.fOffsetY = 26.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, m_tPhysics.fOffsetY)); //오프셋 만져주면 충돌체 위치 바뀜
	Default();
	m_bAir = true;
}


void CMonster_Gangster::Default()
{
	CMonster::Default();

	if (m_pArm)
	{
		DeleteObject(m_pArm);
		m_pArm = nullptr;
	}
}

void CMonster_Gangster::Attack()
{
	CMonster::Attack();
	SetMark(MARK_TYPE::EXCLAIM2);

	if (!m_pArm)
		CreateArm();
}

void CMonster_Gangster::Run()
{
	CMonster::Run();

	if (m_pArm)
	{
		DeleteObject(m_pArm);
		m_pArm = nullptr;
	}
}

//void CMonster_Gangster::Run()
//{
//	Get_Animator()->Play(L"ATTACK", false);
//	m_eState =(STATE_TYPE::ATTACK);
//	m_tPhysics.fAccel = 0.f;
//	m_fTime = 0.f;
//	m_iAttackCount = 0;
//
//	SetMark(MARK_TYPE::EXCLAIM2);
//	
//	
//}

void CMonster_Gangster::Hit(Vec2 _vDir)
{
	CMonster::Hit(_vDir);

	if (m_pArm)
	{
		DeleteObject(m_pArm);
		m_pArm = nullptr;
	}
}

void CMonster_Gangster::LaserHit()
{
	CMonster::LaserHit();

	if (m_pArm)
	{
		DeleteObject(m_pArm);
		m_pArm = nullptr;
	}

}

void CMonster_Gangster::Update_Attack()
{
	if (dynamic_cast<CPlayer*>(m_pOwner)->IsSmoke())
	{
		Default();
		SetMark(MARK_TYPE::QUESTION);
		return;
	}

	Vec2 vPlayerPos = Get_Owner()->Get_Pos();
	if (vPlayerPos.x < Get_Pos().x)
	{
		SetRenderDir(Vec2(-1.f, 0.f));
	}
	else
	{
		SetRenderDir(Vec2(1.f, 0.f));
	}
}

void CMonster_Gangster::CreateArm()
{
	m_pArm = new CMark;
	m_pArm->SetOwner(this);
	m_pArm->SetMarkType(MARK_TYPE::ARM);
	m_pArm->SetObjType(GROUP_TYPE::MONSTER);
	m_pArm->Initialize();
	CreateObject(m_pArm, GROUP_TYPE::MONSTER);
}


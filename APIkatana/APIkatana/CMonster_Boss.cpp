#include "stdafx.h"
#include "CMonster_Boss.h"

#include "CAnimator.h"
#include "CAbstractFactory.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CHitBox.h"
#include "CSight.h"
#include "CAnimation.h"

CMonster_Boss::CMonster_Boss()
{
	//애니메이터
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Casual_Idle", L"texture\\Monster\\Dragon_Casual_Idle.png");
	iCount = 13;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_CasualtoBattle", L"texture\\Monster\\Dragon_CasualtoBattle.png");
	iCount = 5;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"CasualtoBattle", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Stance", L"texture\\Monster\\Dragon_Stance.png");
	iCount = 12;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"STANCE", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Dash", L"texture\\Monster\\Dragon_Dash.png");
	iCount = 7;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DASH", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Death", L"texture\\Monster\\Dragon_Death.png");
	iCount = 6;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DEATH", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Fall", L"texture\\Monster\\Dragon_Fall.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"FALL", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Flip", L"texture\\Monster\\Dragon_Flip.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ROLL", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Hit", L"texture\\Monster\\Dragon_Hit.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"HIT", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Landing", L"texture\\Monster\\Dragon_Landing.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SIT", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Recover", L"texture\\Monster\\Dragon_Recover.png");
	iCount = 9;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RECOVER", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Run", L"texture\\Monster\\Dragon_Run.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Set", L"texture\\Monster\\Dragon_Set.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SET", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Skill", L"texture\\Monster\\Dragon_Skill.png");
	iCount = 2;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SKILL", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.03f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Attack", L"texture\\Monster\\Dragon_Attack.png");
	iCount = 7;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ATTACK", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	// =============== 오프셋 조정 ==================
	/*CAnimation* pAnim = Get_Animator()->FindAnimation(L"DIEMOVIE");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -4.f);

	pAnim = Get_Animator()->FindAnimation(L"WALK");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -4.f);*/
}

CMonster_Boss::~CMonster_Boss()
{
}

void CMonster_Boss::Initialize()
{
	CAlive::Initialize();

	Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜

	//m_pHitBox = CAbstractFactory<CHitBox>::Create(this, GROUP_TYPE::MONSTER_HITBOX);
	//CreateObject(m_pHitBox, GROUP_TYPE::MONSTER_HITBOX);

	////시야 충돌체
	//m_pSight = CAbstractFactory<CSight>::Create(this, GROUP_TYPE::MONSTER_SIGHT);
	//m_pSight->SetColSize(Vec2(300.f, 300.f));
	//dynamic_cast<CSight*>(m_pSight)->Set_Offset(0.f);
	//CreateObject(m_pSight, GROUP_TYPE::MONSTER_SIGHT);
}

void CMonster_Boss::Update()
{
	m_pAnimator->Play(L"DIEMOVIE", true);
	m_pAnimator->Update();
}

void CMonster_Boss::Render(HDC _dc)
{
	m_pAnimator->Render(_dc, Color(190, 230, 230), Color(255, 255, 255));
	CObj::Component_Render(_dc);
}

void CMonster_Boss::Update_Attack()
{
}

#include "stdafx.h"
#include "CBoss.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CLineMgr.h"
#include "CSoundMgr.h"

#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CEffects_Dust.h"
#include "CEffects_LandingDust.h"
#include "CDragon_Slash.h"
#include "CEffects_JumpDust.h"
#include "CEffects_Blood.h"
#include "CEffects_DarkScreen.h"
#include "CEffects_PlayMusic.h"
#include "CEffects_Charge.h"

#include "CLand.h"
#include "CWall.h"
#include "CHitBox.h"
#include "CAfterImage.h"
#include "CLaserImage.h"
#include "CSubWeapon.h"

#include "CSub_Knife.h"
#include "CSub_Bottle.h"
#include "CSub_Smoke.h"

#include "CAbstractFactory.h"
#include "CEffects_Dragon.h"

#include "CScene_Boss.h"
#include "CPlayer.h"

#include "CBG_Boss.h"

CBoss::CBoss()
	: m_bAfter(false)
	, m_baftercolorplus(true)
	, m_fAfterCount(0.f)
	, m_fAfterDuration(4.f)
	, m_fAfterColor{ 1.f, 0.f, 0.f }
	, m_iDashCount(0)
	, m_fDashTime(0.f)
	, m_fAfterSpeed(0.01f)
	, m_fSlowMaxTime(6.f)
	, m_fSlowTime(m_fSlowMaxTime)
	, m_fMaxCool(1.f)
	, m_fSkillCool(0.f)
{

#pragma region 플레이어 캐릭터 텍스쳐 추가 / 조정

	CreateAnimator();
	CTexture* pTex = nullptr;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Casual_Idle", L"texture\\Monster\\Dragon_Casual_Idle.png");
	UINT iCount = 13;
	float fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Dragon_Casual_Idle", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_CasualtoBattle", L"texture\\Monster\\Dragon_CasualtoBattle.png");
	iCount = 5;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Dragon_CasualtoBattle", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.11f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Stance", L"texture\\Monster\\Dragon_Stance.png");
	iCount = 12;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"STANCE", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.09f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Run", L"texture\\Monster\\Dragon_Run.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Dash", L"texture\\Monster\\Dragon_Dash.png");
	iCount = 7;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DASH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Recover", L"texture\\Monster\\Dragon_Recover.png");
	iCount = 9;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RECOVER", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Landing", L"texture\\Monster\\Dragon_Landing.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SET", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Attack", L"texture\\Monster\\Dragon_Attack.png");
	iCount = 7;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ATTACK", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Hang", L"texture\\Monster\\Dragon_Hang.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"HANG", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Flip", L"texture\\Monster\\Dragon_Flip.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ROLL", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Hit", L"texture\\Monster\\Dragon_Hit.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"HIT", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Set", L"texture\\Monster\\Dragon_Set.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SIT", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Death", L"texture\\Monster\\Dragon_Death.png");
	iCount = 6;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DEATH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Skill", L"texture\\Monster\\Dragon_Skill.png");
	iCount = 2;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SKILL", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.02f, iCount);

	// ==================점프====================

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Fall", L"texture\\Monster\\Dragon_Fall.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"FALL", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	CAnimation* pAnim = Get_Animator()->FindAnimation(L"DEATH");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 5.f);

	pAnim = Get_Animator()->FindAnimation(L"Dragon_Casual_Idle");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -3.f);

	/*CAnimation* pAnim = Get_Animator()->FindAnimation(L"DASH");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 3.f);

	pAnim = Get_Animator()->FindAnimation(L"DEATH");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 7.f);

	pAnim = Get_Animator()->FindAnimation(L"RUN");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 2.f);

	pAnim = Get_Animator()->FindAnimation(L"SIT");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 2.f);

	pAnim = Get_Animator()->FindAnimation(L"CROUCH");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -1.f);

	pAnim = Get_Animator()->FindAnimation(L"FALL");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -6.f);

	pAnim = Get_Animator()->FindAnimation(L"JUMP");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -4.f);

	pAnim = Get_Animator()->FindAnimation(L"PLAYSONG");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -2.f);*/
#pragma endregion 플레이어 캐릭터 텍스쳐 추가 / 조정


	Get_Animator()->Play(L"FALL", true);
}

CBoss::~CBoss()
{
}

void CBoss::SetColorMatrix(bool _b)
{
	if (!_b)
	{
		*m_colorMatrix = {
		   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		m_fAfterSpeed = 0.01f;
		m_bAfter = false;


	}
	else
	{
		/**m_colorMatrix = {
		   0.5f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.8f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   0.0f, 0.3f, 0.6f, 0.0f, 1.0f };*/

		*m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,   0.7f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f,  0.7f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.0f, 0.0f, 0.0f, 1.0f };

		/**m_colorMatrix = {
		   0.1f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.8f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.8f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   0.0f, 0.5f, 0.9f, 0.0f, 1.0f };*/
		m_fAfterSpeed = 0.05f;
		m_bAfter = true;


	}

}


#pragma region 이니셜라이즈와 업데이트
void CBoss::Initialize()
{
	CAlive::Initialize();

	m_eMobType = MOB_TYPE::BOSS;

	//몸 충돌체
	CObj* pHitBox = CAbstractFactory<CHitBox>::Create();
	pHitBox->SetObjType(GROUP_TYPE::MONSTER_HITBOX);
	pHitBox->SetOwner(this);
	CreateObject(pHitBox, GROUP_TYPE::MONSTER_HITBOX);
	m_pHitBox = pHitBox;
	m_tPhysics.fOffsetY = 18.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, m_tPhysics.fOffsetY)); //오프셋 만져주면 충돌체 위치 바뀜
	SetColorMatrix(false);

	Default();
	m_tPhysics.fOriginY = 200.f;
	m_tPhysics.fAcc = 0.f;
	m_bAir = false;


}

void CBoss::Update()
{
	if (m_bLaser)
		*m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	else if (STATE_TYPE::DEATH != m_eState && STATE_TYPE::HIT != m_eState)
	*m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	if (STATE_TYPE::DEATH != m_eState && CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		*m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,   0.7f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f,  0.7f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.0f, 0.0f, 0.0f, 1.0f };
	}


	m_fMaxCool = (float)dynamic_cast<CScene_Boss*>(CSceneMgr::Get_Instance()->Get_CurScene())->Get_DragonCount() * 2.f + 0.5f;

	if (m_fSkillCool > 0.f)
		m_fSkillCool -= RealfDT;
	else
		m_fSkillCool = 0.f;

	//================ 공중에 있을 때 처리 =======================
	if (m_bAir)
	{
		if (STATE_TYPE::DEFAULT == m_eState || STATE_TYPE::RUN == m_eState
			|| STATE_TYPE::SIT == m_eState || STATE_TYPE::SET == m_eState || STATE_TYPE::CROUCH == m_eState)
		{
			m_eState = (STATE_TYPE::AIR);
			m_fTime = 0.3f;
		}
	}
	//=========================================================


	//================ 대쉬 중엔 히트박스 무효화 =======================
	if (STATE_TYPE::DASH == m_eState || STATE_TYPE::AIRDASH == m_eState || STATE_TYPE::DEATH == m_eState)
	{
		if (m_pHitBox->Get_Collision())
			m_pHitBox->SetCollision(false);
	}
	else if (!m_pHitBox->Get_Collision())
		m_pHitBox->SetCollision(true);

	//===========================================================

	//======================= 잔상효과 꺼짐 관련 =========================
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 1.f) // 속도 일반 상태
	{
		if (STATE_TYPE::DASH != m_eState && STATE_TYPE::AIRDASH != m_eState && STATE_TYPE::ATTACK != m_eState
			&& STATE_TYPE::SKILL != m_eState)
			m_bAfter = false;

	}
	//====================================================================

	//if (m_bAfter)
	m_fAfterCount += fDT;

	if (m_fAfterCount >= m_fAfterSpeed)
	{
		m_fAfterCount = 0;
		CreateAfterImage();
	}

	CAlive::Update();
}
void CBoss::Render(HDC _dc)
{
	CObj::Render(_dc);

}
#pragma endregion 이니셜라이즈와 업데이트


#pragma region 충돌처리 관련
void CBoss::OnCollision(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();

	switch (pOtherObj->Get_ObjType())
	{
	case GROUP_TYPE::LAND:
		if (m_tPhysics.bFalling)
		{
			m_bLand = true;
		}

		break;

	case GROUP_TYPE::WALL:

		if (m_eState != STATE_TYPE::ATTACK && m_bAir && dynamic_cast<CWall*>(pOtherObj)->IsClimbTrue() && 0 < m_tPhysics.fXSpeed
			&& STATE_TYPE::DEATH != m_eState && STATE_TYPE::HIT != m_eState) // 
		{
			if (dynamic_cast<CWall*>(pOtherObj)->IsWallLeft())
			{
				if (0 > m_vDir.x)
					Hang();
			}
			else
			{
				if (0 < m_vDir.x)
					Hang();
			}

		}

		break;
	default:
		break;

	}
}

void CBoss::OnCollisionEnter(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();

	switch (pOtherObj->Get_ObjType())
	{
	case GROUP_TYPE::LAND:
		if (!m_tPhysics.bFalling)
			return;

		if (m_bAir && 0 > m_tPhysics.fMaxYSpeed && STATE_TYPE::DEATH != m_eState && STATE_TYPE::DASH != m_eState)
		{
			m_bAir = false;
			Set();
			m_tPhysics.fXSpeed = 0.f;
		}

		break;

	case GROUP_TYPE::WALL:
		if (m_eState == STATE_TYPE::HIT || m_eState == STATE_TYPE::DEATH)
		{
			SetDirX(Get_Dir().x * -1.f);
			SetRenderDir(Get_RenderDir() * -1.f);
			m_tPhysics.fXSpeed *= 0.5f;
			return;
		}

		else if (m_eState == STATE_TYPE::AIR && dynamic_cast<CWall*>(pOtherObj)->IsClimbTrue())
		{
			if (m_bAir)
			{
				Hang();
			}
		}

		break;



	case GROUP_TYPE::SUBWEAPON:
	{
		if (m_eState != STATE_TYPE::HIT && m_eState != STATE_TYPE::DEATH)
		{
			ThrowSub(dynamic_cast<CSubWeapon*>(pOtherObj)->Get_SubType());
			DeleteObject(pOtherObj);
		}
		
	}
	break;

	default:
		break;

	}
}

void CBoss::OnCollisionExit(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();

	switch (pOtherObj->Get_ObjType())
	{
	case GROUP_TYPE::LAND:
		if (!m_tPhysics.bFalling)
			return;

		m_bLand = false;
		m_tPhysics.fOriginY = m_vPos.y;


		break;

	case GROUP_TYPE::WALL:
		if (STATE_TYPE::HANG == m_eState)
		{
			m_eState = (STATE_TYPE::AIR);
		}

		break;

	default:
		break;

	}
}

#pragma endregion 충돌처리 관련

#pragma region 캐릭터의 현재 상태별 키 업데이트
void CBoss::Update_Default()
{
	Get_Animator()->Play(L"STANCE", true);

	if (dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::HIT || dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::DEATH)
	{
		return;
	}

	//보스 패턴 우선순위
	//1. 스킬 쿨타임이 돌았을 경우 스킬 사용
	if (m_fSkillCool == 0.f)
	{
		Sit();
		return;
	}

	//2. 플레이어와 나의 거리를 판별
	float fDis = fabs(m_pOwner->Get_Pos().x - m_vPos.x);

	//2-1. 거리가 가깝다 : 공격 or 구르기
	if (fDis < 100.f)
	{
		int iRand = random(0, 15);
		if (iRand <= 11)
			Attack();
		else if (iRand == 13)
			Dash();
		else
			Dash(true);
	}


	//2-2. 거리가 멀다 : 내 위치를 판별 (플레이어보다 벽이랑 더 가까운지)
	else
	{
		float fLeftX = m_vPos.x - 110.f;
		float fRightX = 625.f - m_vPos.x;

		// 내가 아예 벽쪽인 경우 -> 점프 후 벽타기


		//2-2-1. 플레이어가 더 가까운 경우 : 플레이어 쪽으로 구르기
		if (fDis < fLeftX && fDis < fRightX)
		{
			Dash(true);
		}
		//2-2-2. 벽이 더 가까운 경우 : 벽타기
		else if (fLeftX < 40.f || fRightX < 40.f)
		{
			Jump();
		}
		//2-2-3. 플레이어는 멀고 벽타기에도 벽도 멀다 : 벽쪽으로 구르기
		else
		{
			Dash();
		}
	}


	ThrowSubWeapon();
}

void CBoss::Update_Dash()
{
	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	m_fTime += fDT;
	m_fDashTime += fDT;

	if (0.02f <= m_fDashTime)
	{
		CAbstractFactory<CEffects_Dust>::Create_Effects(this, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);
		//CreateDust();
		m_fDashTime = 0.f;
	}
	if (TimeLimit <= m_fTime)
	{
		Default();
	}

	ThrowSubWeapon();

}

void CBoss::Update_Air()
{
	if (m_fSkillCool == 0.f)
	{
		Skill();
		return;
	}

	if (m_iAttackCount == 1)
	{
		Attack();
		return;
	}

	// 땅에 닿으면 처리
	if (!m_bAir)
	{
		Set();
		m_tPhysics.fXSpeed = 0.f;
		return;
	}

	Get_Animator()->Play(L"FALL", true);

	m_tPhysics.fXSpeed = m_tPhysics.fMaxXSpeed;

	ThrowSubWeapon();

}

void CBoss::Update_Animation()
{
	Get_Animator()->Play(L"Dragon_Casual_Idle", true);
	m_fTime += RealfDT;
	
	dynamic_cast<CAlive*>(m_pOwner)->SetState(STATE_TYPE::DEFAULT);

	if (0.5f < m_fTime && m_fAcc == 0.f)
	{
		m_fAcc += RealfDT;
		CCamera::Get_Instance()->SetZoom();
		CObj* pObj = CAbstractFactory<CEffects_Dragon>::Create(m_vPos, GROUP_TYPE::UI);
		CreateObject(pObj, GROUP_TYPE::UI);
		dynamic_cast<CBackGround*>(CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::DEFAULT).front())->SetDark();

		//DeleteObject(CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::DEFAULT).front());

	}

	if (m_fAcc != 0.f)
	{
		m_fAcc += RealfDT;
		if (m_fAcc > 3.f)
		{
			Run();
			
		}
	}

}

void CBoss::Update_Skill()
{
	m_tPhysics.fXSpeed = 100.f;

	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit <= m_fTime)
	{
		if (m_fAcc != 0.f)
		{
			m_bAir = true;
			m_eState = STATE_TYPE::AIR;
			return;
		}
		Get_Animator()->Play(L"ATTACK", true);
		m_fAcc += fDT;
		m_fTime = 0.f;
	}
}

void CBoss::Update_Run()
{
	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit <= m_fTime && m_fAcc == 0.f)
	{
		CCamera::Get_Instance()->SetZoom();
		CCamera::Get_Instance()->SetTarget(m_pOwner);
		m_fAcc += fDT;
		m_pAnimator->Play(L"STANCE", true);
		dynamic_cast<CBackGround*>(CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::DEFAULT).front())->SetNormal();

		//CreateObject(CAbstractFactory<CBG_Boss>::Create(), GROUP_TYPE::DEFAULT);
	}

	if (m_fAcc != 0.f)
	{
		m_fAcc += fDT;
		if (dynamic_cast<CAlive*>(CSceneMgr::Get_Instance()->Get_CurScene()->Get_Player())->Get_State() == STATE_TYPE::DEFAULT )
		{
			Default();

		}
	}
}

void CBoss::Update_Attack()
{
	m_fTime += fDT;

	if (0.24f <= m_fTime)
	{
		if (m_bAir)
		{
			m_tPhysics.fXSpeed *= 0.7f;
		}
		m_iDashCount = 0;
		m_fTime = 0.f;
		m_eState = (STATE_TYPE::DEFAULT);
	}
}

void CBoss::Update_Hang()
{
	m_fAcc += fDT;
	if (0.3f <= m_fAcc)
	{
		m_fAcc = 0.f;
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Hold.wav");

	}

	float fDir = Get_RenderDir().x;
	m_bAfter = false;

	m_fDashTime += fDT;

	if (0.03f < m_fDashTime && !m_bHold)
	{
		CreateDust(fDir * 7.f);
		m_fDashTime = 0.f;
	}

	if (m_tPhysics.bFalling && m_fTime == 0.f)
	{
		m_bHold = true;
	}

	if (m_bHold)
	{
		AirDash();
	}

	ThrowSubWeapon();

}

void CBoss::Update_Airdash()
{
	m_fTime += fDT;
	m_tPhysics.fAcc -= 3.f*fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit <= m_fTime)
	{
		Attack();
	}
}

void CBoss::Update_Hit()
{
	m_fDashTime += fDT;

	if (0.01f < m_fDashTime)
	{
		CreateBlood(false);
		m_fDashTime = 0.f;
	}
}

void CBoss::Update_Death()
{
	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit / 1.5f >= m_fTime && m_fAcc == 0.f)
	{
		m_fDashTime += fDT;
		if (0.05f < m_fDashTime)
		{
			CreateBlood(true);
			m_fDashTime = 0.f;
		}
	}

	int iDragonCount = dynamic_cast<CScene_Boss*>(CSceneMgr::Get_Instance()->Get_CurScene())->Get_DragonCount();
	
	if (iDragonCount != 0)
	{
		m_fAcc += RealfDT;

		if (m_fAcc > 1.f)
		{
			if (m_fTime >= 1.f)
				CSoundMgr::Get_Instance()->PlaySound(L"Charge.wav");

			if (m_fTime > 0.016f && m_fAcc < 1.5f)
			{
				CObj* pElectric = new CEffects_Charge;
				pElectric->SetPos(m_vPos);
				pElectric->Initialize();
				CreateObject(pElectric, GROUP_TYPE::EFFECTS);
				m_fTime = 0.f;
			}
		}

		if (m_fAcc > 2.f)
		{
			CSceneMgr::Get_Instance()->DragonReplay();
		}
	}
	else if (m_fAcc == 0.f)
	{
		m_fAcc += 1.f;
		dynamic_cast<CPlayer*>(m_pOwner)->SetPlayMusic(true);
	}
}

void CBoss::Update_Set()
{
	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit <= m_fTime)
	{
		Default();
	}
}

void CBoss::Update_Sit()
{
	m_fAcc += fDT;

	if (m_fTime < 0.3f && m_fAcc > 0.016f)
	{
		CObj* pElectric = new CEffects_Charge;
		pElectric->SetPos(m_vPos);
		pElectric->Initialize();
		CreateObject(pElectric, GROUP_TYPE::EFFECTS);
		m_fAcc = 0.f;
	}
	

	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit + 0.5f <= m_fTime)
	{
		Skill();
	}

	ThrowSubWeapon();
}

#pragma endregion 캐릭터의 현재 상태별 키 업데이트

#pragma region 캐릭터 모션
void CBoss::Default()
{
	Get_Animator()->Play(L"STANCE", true);
	m_tPhysics.fAccel = 0.f;
	m_tPhysics.fYSpeed = 0.f;
	m_fTime = 0.f;

	m_eState = (STATE_TYPE::DEFAULT);
	m_iAttackCount = 0;
	m_iDashCount = 0;
}

void CBoss::Attack()
{
	int iRand = random(0, 2);

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		switch (iRand)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySound(L"Slow_Katana.wav");

			break;

		default:
			CSoundMgr::Get_Instance()->PlaySound(L"Slow_Katana_2.wav");

			break;

		}
	}
	else
	{
		switch (iRand)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Katana.wav");

			break;

		case 1:
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Katana2.wav");

			break;

		case 2:
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Katana3.wav");

			break;

		}
	}

	Get_Animator()->Play(L"ATTACK", true);

	//기본 상태 변경
	m_bAfter = true;
	m_bHold = false;
	m_iDashCount = 0;
	m_fTime = 0.f;

	//마우스 방향으로 진행, 슬래쉬 생성
	Vec2 vDir;
	Vec2 mousePos = m_pOwner->Get_Pos();
	vDir = mousePos - m_vPos;
	vDir.Normalize();
	CreateSlash(vDir);
	m_vDir = vDir;

	if (!m_bAir)
		CAbstractFactory<CEffects_JumpDust>::Create_Effects(this, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);

	//출력 방향
	if (0 <= vDir.x)
		SetRenderDir(Vec2(1.f, 0.f));
	else
		SetRenderDir(Vec2(-1.f, 0.f));

	float fTemp = m_tPhysics.fYSpeed;

	// 캐릭터의 진행 힘
	m_vPos.y -= 10.f;

	m_tPhysics.fXSpeed = 300.f;
	m_tPhysics.fYSpeed = 36.f * fabs(vDir.y);

	// 캐릭터의 y축 힘이 줄어드는 조건
	// 1. 공격 횟수가 2번째일 때

	if (0 != m_iAttackCount || 12.f > m_tPhysics.fYSpeed)
	{
		m_tPhysics.fYSpeed = 8.f;
	}

	// 2. 땅에서 땅쪽으로 공격할 때

	if (!m_bAir && vDir.y > -0.2f)
	{
		{
			m_tPhysics.fYSpeed = 8.f;
			m_tPhysics.fXSpeed = 320.f * fabs(vDir.x);
		}


		m_tPhysics.fAcc = 0.f;
		m_tPhysics.fOriginY = m_vPos.y;
		m_bAir = true;
	}

	// 3. (예외상황)공중에서 아래로 공격할 때
	else if (0.7f < vDir.y)
	{
		m_tPhysics.fYSpeed = fTemp;
		m_bAir = true;
	}
	else
	{
		m_tPhysics.fAcc = 0.f;
		m_tPhysics.fOriginY = m_vPos.y;
		m_bAir = true;
	}


	m_eState = (STATE_TYPE::ATTACK);
	++m_iAttackCount;

}

void CBoss::Jump()
{
	if (!m_bAir)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Jump.wav");

		m_iDashCount = 0;
		CAbstractFactory<CEffects_JumpDust>::Create_Effects(nullptr, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);
		m_fTime = 0.f;
		m_eState = (STATE_TYPE::AIR);
		m_tPhysics.fYSpeed = 24.f;
		m_tPhysics.fOriginY = m_vPos.y;
		m_tPhysics.fAcc = 0.f;
		m_tPhysics.fXSpeed = m_tPhysics.fMaxXSpeed;
		m_bAir = true;

		if (m_vPos.x < m_pOwner->Get_Pos().x)
		{
			m_vDir = Vec2(-1.f, 0.f);
		}
		else
		{
			m_vDir = Vec2(1.f, 0.f);
		}
		m_vRenderDir = m_vDir;
	}
}

void CBoss::Dash(bool _bPlayer)
{
	if (!m_bAir)
	{
		if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
			CSoundMgr::Get_Instance()->PlaySound(L"Slow_Dash.wav");
		else
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Dash.wav");

		Get_Animator()->Play(L"DASH", false);
		Get_Animator()->Get_CurAnim()->SetFrame(0);
		CAbstractFactory<CEffects_Dust>::Create_Effects(this, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);
		m_iAttackCount = 0;
		m_iDashCount = 0;
		m_fDashTime = 0.f;
		m_fTime = 0.f;
		m_eState = (STATE_TYPE::DASH);
		m_tPhysics.fXSpeed = m_tPhysics.fMaxXSpeed * 2.5f;
		m_tPhysics.fAccel = 0.f;
		m_bAfter = true; // 잔상효과

		if (_bPlayer)
		{
			if (m_vPos.x < m_pOwner->Get_Pos().x)
			{
				m_vDir = Vec2(1.f, 0.f);
			}
			else
			{
				m_vDir = Vec2(-1.f, 0.f);
			}
			m_vRenderDir = m_vDir;

		}
		else
		{
			if (m_vPos.x < m_pOwner->Get_Pos().x)
			{
				m_vDir = Vec2(-1.f, 0.f);
			}
			else
			{
				m_vDir = Vec2(1.f, 0.f);
			}
			m_vRenderDir = m_vDir;
		}

	}
}

void CBoss::Hang()
{
	Get_Animator()->Play(L"HANG", false);
	Get_Animator()->Get_CurAnim()->SetFrame(0);
	SetRenderDir(m_vDir);
	m_eState = (STATE_TYPE::HANG);

	if (STATE_TYPE::AIRDASH == m_eState)
	{
		m_tPhysics.fXSpeed = 0.f;
		m_tPhysics.fYSpeed = 0.f;
	}

	m_tPhysics.fAccel = 0.f;
	m_tPhysics.fOriginY = m_vPos.y;

	if (!m_tPhysics.bFalling)
	{
		if (2.f < m_tPhysics.fAcc)
			m_tPhysics.fYSpeed = m_tPhysics.fXSpeed*0.1f;
		else
			m_tPhysics.fYSpeed = m_tPhysics.fXSpeed*0.13f;

	}

	m_tPhysics.fAcc = 0.f;
	m_tPhysics.fXSpeed = 0.f;
	m_fDashTime = 0.f;
	m_fTime = 0.f;

}

void CBoss::AirDash()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Player_Dash.wav");

	Vec2 vDir = { m_vRenderDir.x * -1.f, 0.f };

	Get_Animator()->Play(L"ROLL", true);
	Get_Animator()->Get_CurAnim()->SetFrame(0);

	SetDir(vDir);
	SetRenderDir(Get_Dir());

	m_bHold = false;
	m_fTime = 0.f;
	m_iAttackCount = 0;
	m_bAfter = true; // 잔상효과

	m_tPhysics.fXSpeed = m_tPhysics.fMaxXSpeed * 1.5f;
	JUMP(25.f);
	m_eState = (STATE_TYPE::AIRDASH);

}

void CBoss::Death()
{
	Get_Animator()->Play(L"DEATH", false);
	m_eState = (STATE_TYPE::DEATH);
	m_tPhysics.fYSpeed = 0.f;
	m_fDashTime = 0.f;
	m_pHitBox->SetCollision(false);
	m_fTime = 0.f;
	m_fAcc = 0.f;

}

void CBoss::Sit()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Charge.wav");

	Get_Animator()->Play(L"SIT", false);
	Get_Animator()->Get_CurAnim()->SetFrame(0);
	m_eState = (STATE_TYPE::SIT);
	m_iAttackCount = 0;
	m_fTime = 0.f;

	Vec2 vDir;
	Vec2 mousePos = m_pOwner->Get_Pos();
	vDir = mousePos - m_vPos;
	vDir.Normalize();
	m_vDir = vDir;

	//출력 방향
	if (0 <= vDir.x)
		SetRenderDir(Vec2(1.f, 0.f));
	else
		SetRenderDir(Vec2(-1.f, 0.f));
}

void CBoss::Set()
{
	Get_Animator()->Play(L"SET", false);
	Get_Animator()->Get_CurAnim()->SetFrame(0);
	m_eState = (STATE_TYPE::SET);
	m_fTime = 0.f;
	m_iAttackCount = 0;
	m_iDashCount = 0;
	m_tPhysics.fAccel = 0.f;
	m_tPhysics.fYSpeed = 0.f;
	m_tPhysics.fAcc = 0.f;
	m_vDir = m_vRenderDir;
	CAbstractFactory<CEffects_LandingDust>::Create_Effects(this, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);
}

void CBoss::ThrowSubWeapon()
{
	vector<CObj*> arrSub = CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::SUBATTACK);
	if (!arrSub.empty())
	{
		CObj* pSub = arrSub.front();
		if (pSub->Get_Pos().x < m_vPos.x + 130.f && pSub->Get_Pos().x > m_vPos.x - 130.f)
		{
			Attack();
		}
	}
}

void CBoss::ThrowSub(SUB_TYPE eType)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Player_Throw.wav");

	Vec2 vDir;
	Vec2 mousePos = m_pOwner->Get_Pos();
	vDir.x = mousePos.x - Get_Pos().x;
	vDir.y = mousePos.y - Get_Pos().y;
	vDir.Normalize();

	Vec2 vPos = m_vPos;
	vPos.x += 20.f * vDir.x;
	vPos.y += 20.f * vDir.y;


	CSub* pSub = nullptr;

	switch (eType)
	{
	case SUB_TYPE::KNIFE:
		pSub = new CSub_Knife;
		break;

	case SUB_TYPE::BOTTLE:
		pSub = new CSub_Bottle;
		break;

	case SUB_TYPE::SMOKE:
		pSub = new CSub_Smoke;
		break;
	}

	pSub->SetOwner(this);
	pSub->SetDir(vDir);
	pSub->Initialize();
	pSub->SetPos(vPos);
	pSub->SetObjType(GROUP_TYPE::MOBSUBATTACK);
	CreateObject(pSub, GROUP_TYPE::MOBSUBATTACK);
}

void CBoss::Skill()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Dragon_Skill.wav");

	//m_bAfter = true; // 잔상효과

	m_fTime = 0.f;
	m_fSkillCool = m_fMaxCool;

	m_eState = STATE_TYPE::SKILL;

	Vec2 vDir;
	Vec2 mousePos = m_pOwner->Get_Pos();
	vDir = mousePos - m_vPos;
	vDir.Normalize();
	m_vDir = vDir;
	CreateSlash(m_vDir);

	Get_Animator()->Play(L"ATTACK", false);
	Vec2 vPos;
	if (0 <= vDir.x)
		vPos = Vec2(550.f, mousePos.y);
	else
		vPos = Vec2(150.f, mousePos.y);
	SkillEffects(vPos);
	Get_Animator()->Play(L"SKILL", false);

	//출력 방향
	if (0 <= vDir.x)
	{
		SetRenderDir(Vec2(1.f, 0.f));
		m_vPos.x = 600.f;
	}
	else
	{
		SetRenderDir(Vec2(-1.f, 0.f));
		m_vPos.x = 100.f;
	}

	//m_bAir = true;
	m_vPos.y = m_pOwner->Get_Pos().y-1.f;
	JUMP(0);

	

	CCamera::Get_Instance()->SetVibrate();

}
void CBoss::Parring(CObj* pOther)
{
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Slow_Parring.wav");
	}
	else
	{
		int iRand = random(0, 1);
		if (iRand == 0)
			CSoundMgr::Get_Instance()->PlaySound(L"Parring.wav");
		else
			CSoundMgr::Get_Instance()->PlaySound(L"Parring_2.wav");
	}

	m_tPhysics.fXSpeed = 200.f;

	if (pOther->Get_Pos().x < m_vPos.x)
		m_vDir = Vec2(1.f, 0.f);
	else
		m_vDir = Vec2(-1.f, 0.f);

	//m_vPos.y -= 10.f;
	JUMP(20.f);
	m_bAir = true;

	m_iAttackCount = 2;
}

void CBoss::Run()
{
	//m_pAnimator->Play(L"Dragon_CasualtoBattle", false);
	m_eState = STATE_TYPE::RUN;
	m_fTime = 0.f;
	m_fAcc = 0.f;
	dynamic_cast<CPlayer*>(CSceneMgr::Get_Instance()->Get_CurScene()->Get_Player())->SetPlayMusic();

}

void CBoss::Hit(Vec2 _vDir)
{
	CAlive::Hit(_vDir);
	m_vPos.y -= 10.f;
	m_tPhysics.fOriginY = m_vPos.y;

	m_bAfter = false;

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		dynamic_cast<CPlayer*>(m_pOwner)->TimeSlow(false);
	}
	CSoundMgr::Get_Instance()->PlaySound(L"Dragon_Die.wav");

	dynamic_cast<CScene_Boss*>(CSceneMgr::Get_Instance()->Get_CurScene())->Set_DragonCount();

	if (dynamic_cast<CScene_Boss*>(CSceneMgr::Get_Instance()->Get_CurScene())->Get_DragonCount() == 0)
	{
		dynamic_cast<CBackGround*>(CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::DEFAULT).front())->SetWhite();
		CCamera::Get_Instance()->SetTarget(m_pOwner);
		CCamera::Get_Instance()->SetZoom();
		dynamic_cast<CPlayer*>(m_pOwner)->TimeSlow(false);
		CTimeMgr::Get_Instance()->SetTimeSpeed(0.1f);
		CSoundMgr::Get_Instance()->StopSound(BGM);
	}
		


}

void CBoss::LaserHit()
{

	CAlive::LaserHit();

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		dynamic_cast<CPlayer*>(m_pOwner)->TimeSlow(false);
	}

	dynamic_cast<CScene_Boss*>(CSceneMgr::Get_Instance()->Get_CurScene())->Set_DragonCount();

	m_bLaser = true;

}


#pragma endregion 캐릭터 모션

#pragma region 이펙트 관련


void CBoss::CreateAfterImage()
{
	if (m_bAfter)
	{
		if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW) // 속도 느린 상태면
		{
			m_fAfterColor[0] = 1.f;
			m_fAfterColor[1] = 0.2f;
			m_fAfterColor[2] = 0.2f;
			m_fAfterDuration = 2.f;

		}
		else
		{
			float fTemp = (float)random(0, 3);
			m_fAfterDuration = 3.f;

			m_fAfterColor[0] = 1.f;
			m_fAfterColor[1] = fTemp * 0.1f;
			m_fAfterColor[2] = fTemp * 0.1f;
		}

		CAfterImage* pImage = new CAfterImage;

		pImage->SetAnim(*Get_Animator()->Get_CurAnim());
		pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
		pImage->SetDir(Get_Dir());
		pImage->Set_RGB(m_fAfterColor);

		pImage->SetAlphaCount(m_fAfterDuration); // 낮게 설정할 수록 잔상이 오래 남음

		pImage->SetPos(Get_Pos());
		CreateObject(pImage, GROUP_TYPE::LASER_ATTACK);


	}
	else if (m_eState == STATE_TYPE::RUN || m_eState == STATE_TYPE::AIR)
	{
		/*m_fAfterColor[0] = 0.1f;
		m_fAfterColor[1] = 0.6f;
		m_fAfterColor[2] = 1.0f;*/
		m_fAfterColor[0] = 0.1f;
		m_fAfterColor[1] = 0.1f;
		m_fAfterColor[2] = 0.1f;
		m_fAfterDuration = 8.f;


		CAfterImage* pImage = new CAfterImage;

		pImage->SetAnim(*Get_Animator()->Get_CurAnim());
		pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
		pImage->SetDir(m_vRenderDir);
		pImage->Set_RGB(m_fAfterColor);

		pImage->SetAlphaCount(m_fAfterDuration); // 낮게 설정할 수록 잔상이 오래 남음

		pImage->SetPos(Get_Pos());
		CreateObject(pImage, GROUP_TYPE::LASER_ATTACK);
	}




}

void CBoss::SkillEffects(Vec2 vNextPos)
{
	Vec2 vDir = vNextPos - m_vPos;
	vDir.Normalize();

	float fTerm = 20.f;
	Vec2 vPos = m_vPos;

	m_fAfterDuration = 0.9f;

	while(vPos.x + 10 < vNextPos.x || vPos.x - 10 > vNextPos.x)
	{
		float fTemp = (float)random(0, 3);
		m_fAfterColor[0] = 1.f;
		m_fAfterColor[1] = fTemp * 0.1f;
		m_fAfterColor[2] = fTemp * 0.2f;

		CAfterImage* pImage = new CAfterImage;
		pImage->SetAnim(*Get_Animator()->Get_CurAnim());
		pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
		pImage->SetDir(Get_Dir());
		pImage->Set_RGB(m_fAfterColor);

		pImage->SetAlphaCount(m_fAfterDuration); // 낮게 설정할 수록 잔상이 오래 남음
		m_fAfterDuration -= 0.01f;
		vPos.x += vDir.x * fTerm;
		vPos.y += vDir.y* fTerm;

		pImage->SetPos(vPos);
		CreateObject(pImage, GROUP_TYPE::LASER_ATTACK);
	}
}

void CBoss::CreateDust(float _f)
{
	Vec2 vDir;
	int iRand = random(1, 10);
	float fy = (float)iRand * -0.1f;

	Vec2 vEffectsPos = Get_Pos();
	vEffectsPos.x += float(iRand) * Get_RenderDir().x + _f;

	vDir.x = Get_RenderDir().x * -1.f;
	vDir.y = fy;

	vDir.Normalize();

	CAbstractFactory<CEffects_Dust>::Create_Effects(this, vEffectsPos, vDir, GROUP_TYPE::EFFECTS);
}

void CBoss::CreateDust3()
{
	int iRand = random(1, 2);
	Vec2 vEffectsPos = Get_Pos();

	for (int i = 0; i < 3; ++i)
	{
		float fy = (float)random(-7, 1);

		vEffectsPos.x += float(iRand)*(float)i*2.f * Get_RenderDir().x;

		CAbstractFactory<CEffects_Dust>::Create_Effects(this, vEffectsPos, m_vRenderDir, GROUP_TYPE::EFFECTS);

	}
}


void CBoss::CreateSlash(Vec2 _vDir)
{
	CAbstractFactory<CDragon_Slash>::Create_Effects(this, m_vPos, _vDir, GROUP_TYPE::MONSTER_ATTACK);
}
#pragma endregion 이펙트 관련

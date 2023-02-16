#include "stdafx.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CLineMgr.h"
#include "CSoundMgr.h"
#include "CEditor.h"

#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CEffects_Dust.h"
#include "CEffects_LandingDust.h"
#include "CEffects_Slash.h"
#include "CEffects_JumpDust.h"
#include "CEffects_Blood.h"
#include "CEffects_DarkScreen.h"
#include "CEffects_PlayMusic.h"
#include "CEffects_Breath.h"
#include "CEffects_Sub.h"

#include "CLand.h"
#include "CWall.h"
#include "CHitBox.h"
#include "CAfterImage.h"
#include "CLaserImage.h"
#include "CSubWeapon.h"

#include "CSub_Knife.h"
#include "CSub_Bottle.h"
#include "CSub_Smoke.h"
#include "CSub_Beer.h"

#include "CAbstractFactory.h"
#include "CEffects_DeadUI.h"
#include "CEffects_Clear.h"
#include "CEffects_Ilsum.h"
#include "CScene.h"

#include "CBG_Outside.h"
#include "CEffects_Moon.h"
#include "CBoss.h"



CPlayer::CPlayer()
	: m_bAfter(false)
	, m_baftercolorplus(true)
	, m_fAfterCount(0.f)
	, m_fAfterDuration(4.f)
	, m_fAfterColor{1.f, 0.f, 0.f}
	, m_iDashCount(0)
	, m_fDashTime(0.f)
	, m_fAfterSpeed(0.01f)
	, m_bSubWeapon(false)
	, m_eSubType(SUB_TYPE::END)
	, m_fSlowMaxTime(6.f)
	, m_fSlowTime(m_fSlowMaxTime)
	, m_bPlayMusic(false)
{
	
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player_Katana.wav");


#pragma region 플레이어 캐릭터 텍스쳐 추가 / 조정

	CreateAnimator();
	CTexture* pTex = nullptr;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Stance", L"texture\\Player\\Player_Idle_11.png");
	UINT iCount = 11;
	float fSize = pTex->Width() / (float)iCount ;
	Get_Animator()->CreateAnimation(L"STANCE", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.09f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Run", L"texture\\Player\\Player_Run_10.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Dash", L"texture\\Player\\Player_Dash_7.png");
	iCount = 7;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DASH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Sit", L"texture\\Player\\Player_IdletoRun.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SIT", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Stop", L"texture\\Player\\Player_RuntoIdle.png");
	iCount = 5;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"STOP", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Attack", L"texture\\Player\\Player_Attack_7.png");
	iCount = 7;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ATTACK", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Hang", L"texture\\Player\\Player_Hang_1.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"HANG", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Roll", L"texture\\Player\\Player_Flip_11.png");
	iCount = 11;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"ROLL", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Hit", L"texture\\Player\\Player_Hit_6.png");
	iCount = 6;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"HIT", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Crouch", L"texture\\Player\\Player_Crouch.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"CROUCH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Death", L"texture\\Player\\Player_Death_6.png");
	iCount = 6;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DEATH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Playsong", L"texture\\Player\\Player_Playsong_31.png");
	iCount = 31;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"PLAYSONG", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.1f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Dance", L"texture\\Player\\Player_Dance.png");
	iCount = 12;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DANCE", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	// ==================점프====================
	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Jump", L"texture\\Player\\Player_Jump.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"JUMP", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Player_Fall", L"texture\\Player\\Player_Fall.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"FALL", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);


	CAnimation* pAnim = Get_Animator()->FindAnimation(L"DASH");
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
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -2.f);

	pAnim = Get_Animator()->FindAnimation(L"DANCE");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -4.f);

#pragma endregion 플레이어 캐릭터 텍스쳐 추가 / 조정
	

	Get_Animator()->Play(L"FALL", true);
}

CPlayer::~CPlayer()
{
}

void CPlayer::SetColorMatrix(bool _b)
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
		   0.7f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   0.1f, 0.5f, 0.7f, 0.0f, 1.0f };

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
void CPlayer::Initialize()
{
	CAlive::Initialize();

	//몸 충돌체
	CObj* pHitBox = CAbstractFactory<CHitBox>::Create();
	pHitBox->SetObjType(GROUP_TYPE::PLAYER_HITBOX);
	pHitBox->SetOwner(this);
	CreateObject(pHitBox, GROUP_TYPE::PLAYER_HITBOX);
	m_pHitBox = pHitBox;
	m_tPhysics.fOffsetY = 18.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, m_tPhysics.fOffsetY)); //오프셋 만져주면 충돌체 위치 바뀜
	SetColorMatrix(false);

	Default();
	m_tPhysics.fOriginY = 200.f;
	m_tPhysics.fAcc = 0.f;
	m_bAir = true;


}

void CPlayer::Update()
{

	TimeSlow_Update();
	/**m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };*/


	/*if (STATE_TYPE::DEATH != m_eState && CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		*m_colorMatrix = {
		   0.7f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   0.1f, 0.5f, 0.7f, 0.0f, 1.0f };
	}*/

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

	Key_Input();

	//================ 대쉬 중엔 히트박스 무효화 =======================
	if (STATE_TYPE::DASH == m_eState || STATE_TYPE::AIRDASH == m_eState || STATE_TYPE::DEATH == m_eState || STATE_TYPE::SKILL == m_eState)
	{
		if (m_pHitBox->Get_Collision())
			m_pHitBox->SetCollision(false);
	}
	else if (!m_pHitBox->Get_Collision())
		m_pHitBox->SetCollision(true);

	if (g_bSuper)
		m_pHitBox->SetCollision(false);

	//===========================================================

	//======================= 잔상효과 꺼짐 관련 =========================
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 1.f) // 속도 일반 상태
	{
		if (STATE_TYPE::DASH != m_eState && STATE_TYPE::AIRDASH != m_eState && STATE_TYPE::ATTACK != m_eState)
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
void CPlayer::Render(HDC _dc)
{
	if (m_bPlayMusic)
	{
		m_pAnimator->Render(_dc, Color(255, 255, 255), Color(255, 255, 255));
		return;
	}
	CObj::Render(_dc);

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 0.f || CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::STAGE_03)
		return;

	//Ghost 저장
	m_fGhostTime += RealfDT;
	if (m_fGhostTime > 0.016f)
	{
		CAnimation* pAnim = m_pAnimator->Get_CurAnim();
		tAnimFrm tFrm = pAnim->Get_Frame(pAnim->Get_CurFrame());

		GhostInfo ghost = GhostInfo(m_pAnimator->Get_CurKey(), m_vPos, m_vRenderDir, CCamera::Get_Instance()->Get_LookAt(), 1.f
			, (int)tFrm.vLT.x
			, (int)tFrm.vLT.y
			, (int)tFrm.vSlice.x
			, (int)tFrm.vSlice.y);

		CEditor::Get_Instance()->AddGhost(ghost);
		m_fGhostTime = 0.f;
	}
	

}
#pragma endregion 이니셜라이즈와 업데이트


#pragma region 충돌처리 관련
void CPlayer::OnCollision(CCollider * _pOther)
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

	case GROUP_TYPE::SUBWEAPON:
	{
		if (KEY(RBUTTON, TAP) && !m_bSubWeapon)
		{
			m_bSubWeapon = true;
			m_eSubType = dynamic_cast<CSubWeapon*>(pOtherObj)->Get_SubType();
			DeleteObject(pOtherObj);
			CSoundMgr::Get_Instance()->PlaySound(L"Player_GetSub.wav");
			CObj* pObj = CAbstractFactory<CEffects_Sub>::Create();
			pObj->SetOwner(this);
			dynamic_cast<CEffects_Sub*>(pObj)->SetSubType(m_eSubType);
			pObj->Initialize();
			CreateObject(pObj, GROUP_TYPE::EFFECTS);

		}
		break;
	}

	
	default:
		break;

	}
}

void CPlayer::OnCollisionEnter(CCollider * _pOther)
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

	default:
		break;

	}
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
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
			m_eState =(STATE_TYPE::AIR);
		}

		break;

	default:
		break;

	}
}

#pragma endregion 충돌처리 관련

#pragma region 캐릭터의 현재 상태별 키 업데이트
void CPlayer::Update_Default()
{
	Get_Animator()->Play(L"STANCE", true);

	if (!m_bAir)
	{
		if (KEY(A, HOLD))
		{
			Sit();
			SetRenderDir(Vec2(-1.f,0.f));
		}
		else if (KEY(D, HOLD))
		{
			Sit();
			SetRenderDir(Vec2(1.f, 0.f));
		}
		else if (KEY(SPACE, TAP))
		{
			Jump();
		}
		else if (KEY(LSHIFT, TAP))
		{
			Dash();
		}
		else if (KEY(S, HOLD))
		{
			Crouch();
		}

	}
	m_iAttackCount = 0;

	if (m_bPlayMusic)
		PlayMusic();
}

void CPlayer::Update_Dash()
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
		if (m_bAir == true)
			m_eState = STATE_TYPE::AIR;
		else
			Set();
	}
	if (0.28f <= m_fTime)
	{

		if (KEY(A, HOLD) && Get_Dir().x == -1.f)
		{
			m_fTime = 0.f;
			Sit();
			SetRenderDir(Vec2(-1.f,0.f));
			SetDir(Vec2(-1.f, 0.f));
		}
		else if (KEY(D, HOLD) && Get_Dir().x == 1.f)
		{
			m_fTime = 0.f;
			Sit();
			SetRenderDir(Vec2(1.f,0.f));
			SetDir(Vec2(1.f, 0.f));
		}
	}
}

void CPlayer::Update_Air()
{
	// 땅에 닿으면 처리
	if (!m_bAir)
	{
		Set();
		m_tPhysics.fXSpeed = 0.f;
		//CAbstractFactory<CEffects_LandingDust>::Create_Effects(this, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);

		//CreateEffects(EFFECT_TYPE::LANDINGDUST);
		return;
	}

	m_fTime += fDT;


	if (KEY(SPACE, HOLD) && 0.08f < m_fTime && m_fTime < 0.15f && 36.f > m_tPhysics.fYSpeed)
	{
		m_tPhysics.fYSpeed += (100.f) * RealfDT;
		m_iDashCount++;
	}

	if (m_tPhysics.bFalling)
	{
		Get_Animator()->Play(L"FALL", true);
	}
	else
	{
		Get_Animator()->Play(L"JUMP", true);
	}


	if (KEY(S, HOLD))
	{
		m_tPhysics.fAcc += 9 * fDT;
	}

	if (KEY(A, HOLD))
	{
		SetRenderDir(Vec2(-1.f,0.f));

		if (0 < m_tPhysics.fXSpeed) // 움직이고 있다는 가정 하에
		{
			if (0 < Get_Dir().x) // 오른쪽으로 움직이고 있다면
			{
				m_tPhysics.fXSpeed -= m_tPhysics.fAirSpeed * fDT;
			}
			else
			{
				if (m_tPhysics.fXSpeed < m_tPhysics.fMaxXSpeed)
					m_tPhysics.fXSpeed += m_tPhysics.fAirSpeed * fDT;
			}

		}
		else // 움직이질 않고 있었다면
		{
			SetDir(Vec2(-1.f, 0.f)); // 방향은 왼쪽

			if (m_tPhysics.fXSpeed < m_tPhysics.fMaxXSpeed)
				m_tPhysics.fXSpeed += m_tPhysics.fAirSpeed * fDT;
		}


	}
	else if (KEY(D, HOLD))
	{
		SetRenderDir(Vec2(1.f,0.f));

		if (0 < m_tPhysics.fXSpeed) // 움직이고 있다는 가정 하에
		{
			if (0 < Get_Dir().x) // 오른쪽으로 움직이고 있다면
			{
				if (m_tPhysics.fXSpeed < m_tPhysics.fMaxXSpeed)
					m_tPhysics.fXSpeed += m_tPhysics.fAirSpeed * fDT;
			}
			else
			{
				m_tPhysics.fXSpeed -= m_tPhysics.fAirSpeed * fDT;
			}

		}
		else // 움직이질 않고 있었다면
		{
			SetDir(Vec2(1.f, 0.f)); // 방향은 오른쪽


			if (m_tPhysics.fXSpeed < m_tPhysics.fMaxXSpeed)
				m_tPhysics.fXSpeed += m_tPhysics.fAirSpeed * fDT;
		}
	}
	else
		m_tPhysics.fAccel = 0.f;
}

void CPlayer::Update_Sit()
{

	if (0 == m_iDashCount)
	{
		Get_Animator()->Get_CurAnim()->SetFrame(0);
		m_iDashCount++;
	}

	m_fTime += fDT;

	if (0.15f <= m_fTime)
	{
		m_fTime = 0.f;

		if (KEY(A, HOLD))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Run.wav");

			m_eState =(STATE_TYPE::RUN);
			SetRenderDir(Vec2(-1.f,0.f));
			SetDir(Vec2(-1.f, 0.f));
			CreateDust3();

		}
		else if (KEY(D, HOLD))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Run.wav");

			m_eState =(STATE_TYPE::RUN);
			SetRenderDir(Vec2(1.f,0.f));
			SetDir(Vec2(1.f, 0.f));
			CreateDust3();

		}
		else
			Set();
	}

	if (KEY(SPACE, TAP))
	{
		Jump();
	}

	if (KEY(LSHIFT, TAP))
	{
		Dash();
	}

	if (m_bPlayMusic)
		PlayMusic();
}

void CPlayer::Update_PlayMusic()
{
	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (0.6f < m_fTime && m_fAcc == 0.f)
	{
		m_fAcc += 1.f;
		CSoundMgr::Get_Instance()->StopSound(BGM);

		CSoundMgr::Get_Instance()->PlaySound(L"Player_TurnMusic.wav");

	}

	if (TimeLimit <= m_fTime)
	{
		if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::STAGE_03)
		{
			if (!m_bEnd)
				CSoundMgr::Get_Instance()->PlayBGM(L"Music_Boss.wav", g_fSound);
			else
			{
				CSoundMgr::Get_Instance()->StopSound(BGM);
				CSoundMgr::Get_Instance()->PlayBGM(L"Music_Clear.wav", g_fSound);
				m_bPlayMusic = false;
				m_fAcc = 0.f;
				Animation();
				return;
			}
		}
		else
			CSoundMgr::Get_Instance()->PlayBGM(L"Music_Battle.wav", g_fSound);

		CreateObject(CAbstractFactory<CEffects_PlayMusic>::Create(), GROUP_TYPE::UI);
		m_bPlayMusic = false;
		m_fAcc = 0.f;
		Default();
	}
}

void CPlayer::Update_Animation()
{
	if (KEY(LBUTTON, TAP))
		DestroyWindow(g_hwnd);

}

void CPlayer::Update_Skill()
{
	m_fTime += fDT;
	if (1.f < m_fTime)
	{
		CCamera::Get_Instance()->SetZoom();

		SkillAttack();


		dynamic_cast<CBackGround*>(CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::DEFAULT).front())->SetNormal();

	}
}

void CPlayer::Update_Run()
{
	m_fTime += fDT;
	if (0.3f < m_fTime)
	{
		m_fTime = 0.f;
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk_3.wav");

		/*int iRand = random(0, 1);

		switch (iRand)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk_1.wav");
			break;

		case 1:
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk_2.wav");
			break;

		case 2:
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk_3.wav");
			break;
		}*/
	}

	m_iAttackCount = 0;

	Get_Animator()->Play(L"RUN", true);
	m_tPhysics.fAccel = m_tPhysics.fMaxAccel;

	if (KEY(A, AWAY) || KEY(D, AWAY))
		Set();

	if (KEY(SPACE, TAP))
	{
		Jump();
	}

	if (KEY(LSHIFT, TAP))
	{
		Dash();
	}
}

void CPlayer::Update_Attack()
{
	m_fTime += fDT;

	/*if (0 == m_iDashCount)
	{
		m_iDashCount++;
		m_fXSpeed *= 0.5f;
		m_fYSpeed *= 0.5f;
	}*/
	
	if (0.01f >= m_fTime && 160.f > m_tPhysics.fXSpeed && m_vDir.y < 0.2f)
		m_tPhysics.fXSpeed = 300.f;

	if (0.14f <= m_fTime)
	{
		//CCamera::Get_Instance()->SetZoom();
		//CTimeMgr::Get_Instance()->SetTimeSpeed(1.f);
	}
	

	if (0.24f <= m_fTime)
	{
		if (m_bAir)
		{
			m_tPhysics.fXSpeed *= 0.7f;
		}
		m_iDashCount = 0;
		m_fTime = 0.f;
		m_eState =(STATE_TYPE::DEFAULT);

		

		//if (Get_Dir().x < 0.4f && Get_Dir().x > -0.4f) // 거의 수직 점프인 경우
		//{
		//	m_fYSpeed = -100.f;
		//	m_fXSpeed = 0.f;
		//}
		//else
		//{
		//	m_fYSpeed = -20.f;
		//	m_fXSpeed /= 2.f;
		//}

		//SetDir(Vec2(Get_RenderDir(), 0.f));

		
	}
}

void CPlayer::Update_Crouch()
{
	m_fTime += fDT;

	if (m_fTime > 0.14f)
		Get_Animator()->Play(L"CROUCH", false);

	if (KEY(A, TAP))
	{
		SetRenderDir(Vec2(-1.f,0.f));
		Dash();
	}
	else if (KEY(D, TAP))
	{
		SetRenderDir(Vec2(1.f,0.f));
		Dash();
	}
	else if (KEY(S, AWAY))
	{
		Default();
	}


	if (CLineMgr::Get_Instance()->Get_Open(m_vPos, m_tPhysics.fOffsetY) || m_bLand)
	{
		//m_eState = STATE_TYPE::AIR;
		m_vPos.y += 11.f;
		JUMP(0);
	}

}

void CPlayer::Update_Hang()
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

	/*if (m_tPhysics.fYSpeed*10.f - m_tPhysics.fXSpeed >= 0.f && !m_bHold && m_fTime == 0.f)
	{
		m_bHold = true;
		m_tPhysics.fYSpeed = 0.f;
		m_tPhysics.fXSpeed = 0.f;
	}*/

	if (m_bHold)
	{
		m_fTime += fDT;
		if (0.2f < m_fTime)
		{
			m_bHold = false;
			m_tPhysics.fOriginY = m_vPos.y;
			m_tPhysics.fAcc = 0.f;
			m_tPhysics.fYSpeed = 0.f;
			m_bAir = true;
		}
	}
	else if (0.2f < m_fTime)
		m_tPhysics.fAcc -= 3.f * fDT;

	if (KEY(SPACE, TAP))
	{
		AirDash();
	}
}

void CPlayer::Update_Airdash()
{
	m_fTime += fDT;
	m_tPhysics.fAcc -= 3.f*fDT;


	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit <= m_fTime)
	{
		m_fTime = 0.f;
		m_tPhysics.fXSpeed /= 2.f;
		m_eState =(STATE_TYPE::AIR);
	}
}

void CPlayer::Update_Hit()
{
	m_fDashTime += fDT;

	if (0.01f < m_fDashTime)
	{
		CreateBlood(false);
		m_fDashTime = 0.f;
	}
}

void CPlayer::Update_Death()
{
	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit / 1.5f >= m_fTime)
	{
		m_fDashTime += fDT;
		if (0.05f < m_fDashTime)
		{
			CreateBlood(true);
			m_fDashTime = 0.f;
		}
	}
}

void CPlayer::Update_Set()
{
	m_fTime += fDT;

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit <= m_fTime)
	{
		Default();
	}

	else if (KEY(A, HOLD))
	{
		Sit();
		SetRenderDir(Vec2(-1.f,0.f));
	}
	else if (KEY(D, HOLD))
	{
		Sit();
		SetRenderDir(Vec2(1.f,0.f));
	}
	else if (KEY(SPACE, TAP))
	{
		Jump();
	}
	else if (KEY(S, HOLD))
	{
		m_eState =(STATE_TYPE::CROUCH);
	}
}

#pragma endregion 캐릭터의 현재 상태별 키 업데이트

#pragma region 캐릭터 모션
void CPlayer::Default()
{
	Get_Animator()->Play(L"STANCE", true);
	m_tPhysics.fAccel = 0.f;
	m_tPhysics.fYSpeed = 0.f;
	m_fTime = 0.f;
	//m_fAcc = 0.f;

	m_eState = (STATE_TYPE::DEFAULT);
	m_iAttackCount = 0;
	m_iDashCount = 0;
}

void CPlayer::Crouch()
{
	Get_Animator()->Play(L"SIT", false);
	Get_Animator()->Get_CurAnim()->SetFrame(0);
	m_eState = (STATE_TYPE::CROUCH);
	m_iAttackCount = 0;
}

void CPlayer::Attack()
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

//	CCamera::Get_Instance()->SetZoom();

	Get_Animator()->Play(L"ATTACK", true);

	//기본 상태 변경
	m_bAfter = true;
	m_bHold = false;
	m_iDashCount = 0;
	m_fTime = 0.f;

	//마우스 방향으로 진행, 슬래쉬 생성
	Vec2 vDir;
	Vec2 mousePos = CCamera::Get_Instance()->Get_RealPos(Get_MousePos());
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


	m_eState =(STATE_TYPE::ATTACK);	
	++m_iAttackCount;

}

void CPlayer::Jump()
{
	if (!m_bAir)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Jump.wav");

		m_iDashCount = 0;
		CAbstractFactory<CEffects_JumpDust>::Create_Effects(nullptr, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);
		m_fTime = 0.f;
		m_eState =(STATE_TYPE::AIR);

		JUMP(24.f);
		m_bAir = true;
	}
}

void CPlayer::Dash()
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
		m_eState =(STATE_TYPE::DASH);
		SetDir(Vec2(Get_RenderDir().x, 0.f));
		m_tPhysics.fXSpeed = m_tPhysics.fMaxXSpeed * 2.5f;
		m_tPhysics.fAccel = 0.f;
		m_bAfter = true; // 잔상효과

		
	}
}

void CPlayer::Hang()
{
	Get_Animator()->Play(L"HANG", false);
	Get_Animator()->Get_CurAnim()->SetFrame(0);
	SetRenderDir(m_vDir);
	m_eState =(STATE_TYPE::HANG);

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

	//m_fYSpeed = m_fXSpeed * -1.f;
}

void CPlayer::AirDash()
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
	m_eState =(STATE_TYPE::AIRDASH);

}

void CPlayer::Death()
{
	Get_Animator()->Play(L"DEATH", false);
	m_eState =(STATE_TYPE::DEATH);
	m_tPhysics.fYSpeed = 0.f;
	m_fDashTime = 0.f;
	m_pHitBox->SetCollision(false);

}

void CPlayer::Set()
{

	Get_Animator()->Play(L"STOP", false);
	Get_Animator()->Get_CurAnim()->SetFrame(0);
	m_eState =(STATE_TYPE::SET);
	m_fTime = 0.f;
	m_iAttackCount = 0;
	m_iDashCount = 0;
	m_tPhysics.fAccel = 0.f;
	m_tPhysics.fYSpeed = 0.f;
	m_tPhysics.fAcc = 0.f;
	m_vDir = m_vRenderDir;
	CAbstractFactory<CEffects_LandingDust>::Create_Effects(this, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);


}

void CPlayer::Sit()
{
	//CSoundMgr::Get_Instance()->PlaySound(L"Player_Landing.wav");

	Get_Animator()->Play(L"SIT", false);
	Get_Animator()->Get_CurAnim()->SetFrame(0);
	m_eState =(STATE_TYPE::SIT);
	m_iAttackCount = 0;
}

void CPlayer::ThrowSubWeapon()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Player_Throw.wav");

	m_bSubWeapon = false;

	Vec2 vDir;
	Vec2 mousePos = CCamera::Get_Instance()->Get_RealPos(Get_MousePos());
	vDir.x = mousePos.x - Get_Pos().x;
	vDir.y = mousePos.y - Get_Pos().y;
	vDir.Normalize();

	Vec2 vPos = m_vPos;
	vPos.x += 40.f * vDir.x;
	vPos.y += 40.f * vDir.y;


	CSub* pSub = nullptr;

	switch (m_eSubType)
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

	case SUB_TYPE::BEER:
		pSub = new CSub_Beer;
		break;
	}


	pSub->SetDir(vDir);
	pSub->Initialize();
	pSub->SetPos(vPos);
	pSub->SetObjType(GROUP_TYPE::SUBATTACK);
	CreateObject(pSub, GROUP_TYPE::SUBATTACK);



	m_eSubType = SUB_TYPE::END;

}

void CPlayer::PlayMusic()
{
	m_pAnimator->Play(L"PLAYSONG", true);
	m_eState = STATE_TYPE::PLAYMUSIC;

}

void CPlayer::Parring(CObj* pOther)
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
}

void CPlayer::Skill()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Player_Skill2.wav");

	dynamic_cast<CBackGround*>(CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::DEFAULT).front())->SetDark();
	CCamera::Get_Instance()->SetZoom();
	m_fAcc = 0.f;
	m_fTime = 0.f;
	m_eState = STATE_TYPE::SKILL;
	Get_Animator()->Play(L"SIT", false);
	Get_Animator()->Get_CurAnim()->SetFrame(0);

	m_vTargetPos = CCamera::Get_Instance()->Get_RealPos(Get_MousePos());

	if (m_vTargetPos.x > m_vPos.x)
	{
		m_vDir.x = 1.f;
	}
	else
		m_vDir.x = -1.f;

	m_vRenderDir = m_vDir;

	CAbstractFactory<CEffects_Breath>::Create_Effects(nullptr, m_vPos, m_vDir, GROUP_TYPE::SMOKE);
	CAbstractFactory<CEffects_Moon>::Create_Effects(nullptr, m_vPos, m_vDir, GROUP_TYPE::EFFECTS);

}

void CPlayer::SkillAttack()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Player_Skill.wav");

	Vec2 vPos = CCamera::Get_Instance()->Get_RealPos(Get_MousePos());

	if (m_eState == STATE_TYPE::SKILL)
		vPos = m_vTargetPos;

	m_bAir = true;

	if (vPos.x > m_vPos.x)
	{
		m_vDir.x = 1.f;
	}
	else
		m_vDir.x = -1.f;

	m_vRenderDir = m_vDir;

	Vec2 vDir = vPos - m_vPos;
	vDir.Normalize();

	Get_Animator()->Play(L"ATTACK", true);

	CreateSlash(vDir);
	CObj* pObj = new CEffects_Ilsum;
	pObj->SetOwner(this);
	pObj->SetPos(vPos);
	pObj->SetDir(vDir);
	pObj->Initialize();
	pObj->SetObjType(GROUP_TYPE::LASER_ATTACK);
	CreateObject(pObj, GROUP_TYPE::SLASH);

	/*if (m_eState == STATE_TYPE::SKILL)
	{
		SkillEffects(vPos);
	}*/

	m_eState = STATE_TYPE::ATTACK;


	m_vPos = vPos;
	m_fTime = 0.f;
	m_fAcc = 0.f;

	JUMP(0);
	m_vDir = vDir;
	m_tPhysics.fXSpeed = 200.f * abs(vDir.x);
	m_tPhysics.fYSpeed = 20.f * abs(vDir.y);
	m_bAfter = true;

}

void CPlayer::Hit(Vec2 _vDir)
{
	CAlive::Hit(_vDir);

	m_bAfter = false;

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		TimeSlow(false);
	}
	CSoundMgr::Get_Instance()->PlaySound(L"Player_Death.wav");
	CreateObject(CAbstractFactory<CEffects_DeadUI>::Create(), GROUP_TYPE::UI);
}

void CPlayer::LaserHit()
{
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 0.2f)
	{
		TimeSlow(false);
	}

	CAlive::LaserHit();
	CreateObject(CAbstractFactory<CEffects_DeadUI>::Create(), GROUP_TYPE::UI);
}

void CPlayer::Animation()
{
	CAlive::Animation();
	m_fTime = 0.f;
	m_fAcc = 0.f;
	m_pAnimator->Play(L"DANCE", true);
	CCamera::Get_Instance()->SetTarget(this);
	CCamera::Get_Instance()->SetZoom();
	dynamic_cast<CBackGround*>(CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::DEFAULT).front())->SetDark();
	g_bEnd = true;

	Vec2 vPos = m_vPos;
	vPos.y -= 15.f;
	//vPos.x += 10.f;
	CAbstractFactory<CEffects_Clear>::Create_Effects(vPos, GROUP_TYPE::UI);
}

void CPlayer::Key_Input()
{

	if (m_eState == STATE_TYPE::PLAYMUSIC || m_eState == STATE_TYPE::ANIMATION)
		return;

	if (KEY(NUM1, TAP))
	{
		CCamera::Get_Instance()->SetZoom();
	}


	if (KEY(A, NONE) && KEY(D, NONE))
			m_tPhysics.fAccel = 0.f;

	if (KEY(Q, TAP) && STATE_TYPE::HIT != m_eState && STATE_TYPE::DEATH != m_eState)
	{
		if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 1.f)
		{
			TimeSlow(true);
		}
		else
		{
			TimeSlow(false);
		}
	}

	/*if (KEY(RBUTTON, TAP))
	{
		m_vPos = CCamera::Get_Instance()->Get_RealPos(Get_MousePos());
	}*/
	if (KEY(LBUTTON, TAP))
	{
		if (m_eState != STATE_TYPE::ATTACK && m_eState != STATE_TYPE::HIT && m_eState != STATE_TYPE::DEATH)
			Attack();
	}
	if (KEY(RBUTTON, TAP))
	{
		if (m_bSubWeapon && m_eState != STATE_TYPE::HIT && m_eState != STATE_TYPE::DEATH)
			ThrowSubWeapon();
		
	}
	if (KEY(LSHIFT, TAP))
	{
		if (m_eState == STATE_TYPE::DEFAULT || m_eState == STATE_TYPE::RUN
			|| m_eState == STATE_TYPE::SET || m_eState == STATE_TYPE::SIT || m_eState == STATE_TYPE::CROUCH)
		{
			Dash();
		}
	}

	if (KEY(E, TAP))
	{
		if (!m_bAir)
			Skill();
		else
			SkillAttack();
	}
}

void CPlayer::TimeSlow_Update()
{
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		m_fSlowTime -= RealfDT;

		if (0 >= m_fSlowTime)
		{
			m_fSlowTime = 0.f;
			TimeSlow(false);
		}
	}
	else
	{
		if (m_fSlowMaxTime > m_fSlowTime)
		{
			m_fSlowTime += RealfDT * 2.5f;
		}
		else
		{
			m_fSlowTime = m_fSlowMaxTime;
		}
	}
}

void CPlayer::TimeSlow(bool _b)
{
	if (_b)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Slow_Start.wav");
		CSoundMgr::Get_Instance()->SetChannelVolume(BGM, 0.1f);
		CTimeMgr::Get_Instance()->SetTimeSpeed(0.2f);
		CAbstractFactory<CEffects_DarkScreen>::Create_Effects(m_vPos, GROUP_TYPE::DARKSCREEN);
		SetColorMatrix(_b);

		if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::STAGE_03)
		{
			CObj* pBoss = CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::MONSTER).front();
			dynamic_cast<CBoss*>(pBoss)->SetColorMatrix(_b);
		}
	}
	else
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Slow_Over.wav");
		CSoundMgr::Get_Instance()->SetChannelVolume(BGM, g_fSound);
		CTimeMgr::Get_Instance()->SetTimeSpeed(1.f);

		if (!CSceneMgr::Get_Instance()->IsReplay())
		{
			SetColorMatrix(_b);
			if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::STAGE_03)
			{
				CObj* pBoss = CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::MONSTER).front();
				dynamic_cast<CBoss*>(pBoss)->SetColorMatrix(_b);
			}
		}

	}
}

#pragma endregion 캐릭터 모션

#pragma region 이펙트 관련


void CPlayer::CreateAfterImage()
{
	if (m_bAfter)
	{
		if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW) // 속도 느린 상태면
		{
			m_fAfterColor[0] = 0.4f;
			m_fAfterColor[1] = 0.7f;
			m_fAfterColor[2] = 0.7f;
			m_fAfterDuration = 2.f;

		}
		else
		{
			m_iAfterCount = random(0, 6);
			m_fAfterDuration = 3.f;


			switch (m_iAfterCount)
			{
			case 0:
				m_fAfterColor[0] = 1.f;
				m_fAfterColor[1] = 0.f;
				m_fAfterColor[2] = 0.05f;


				break;

			case 1:
				m_fAfterColor[0] = 0.9f;
				m_fAfterColor[1] = 0.1f;
				m_fAfterColor[2] = 0.9f;

				break;

			case 2:
				m_fAfterColor[0] = 0.0f;
				m_fAfterColor[1] = 1.f;
				m_fAfterColor[2] = 1.f;

				break;

			case 3:
				m_fAfterColor[0] = 0.f;
				m_fAfterColor[1] = 0.f;
				m_fAfterColor[2] = 0.9f;

				break;

			case 4:
				m_fAfterColor[0] = 0.9f;
				m_fAfterColor[1] = 0.4f;
				m_fAfterColor[2] = 0.9f;

				break;

			case 5:
				m_fAfterColor[0] = 0.05f;
				m_fAfterColor[1] = 0.8f;
				m_fAfterColor[2] = 0.9f;

				break;

			case 6:
				m_fAfterColor[0] = 1.f;
				m_fAfterColor[1] = 0.f;
				m_fAfterColor[2] = 0.5f;

				break;
			}
		}

		if (g_bLaser)
		{
			m_fAfterColor[0] = 1.f;
			m_fAfterColor[1] = 0.5f;
			m_fAfterColor[2] = 0.0f;
		}

		CAfterImage* pImage = new CAfterImage;

		pImage->SetAnim(*Get_Animator()->Get_CurAnim());
		pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
		pImage->SetDir(Get_Dir());
		pImage->Set_RGB(m_fAfterColor);

		pImage->SetAlphaCount(m_fAfterDuration); // 낮게 설정할 수록 잔상이 오래 남음

		pImage->SetPos(Get_Pos());
		CreateObject(pImage, GROUP_TYPE::EFFECTS);


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
		CreateObject(pImage, GROUP_TYPE::EFFECTS);
	}

	


}

void CPlayer::CreateDust(float _f)
{
	Vec2 vDir;
	int iRand = random(1, 10);
	float fy = (float)iRand * -0.1f;

	Vec2 vEffectsPos = Get_Pos();
	vEffectsPos.x += float(iRand) * Get_RenderDir().x +_f;

	vDir.x = Get_RenderDir().x * -1.f;
	vDir.y = fy;

	vDir.Normalize();

	CAbstractFactory<CEffects_Dust>::Create_Effects(this, vEffectsPos, vDir, GROUP_TYPE::EFFECTS);
}

void CPlayer::CreateDust3()
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


void CPlayer::CreateSlash(Vec2 _vDir)
{
	CAbstractFactory<CEffects_Slash>::Create_Effects(this, m_vPos, _vDir, GROUP_TYPE::SLASH);
}
void CPlayer::SkillEffects(Vec2 vNextPos)
{
	Vec2 vDir = vNextPos - m_vPos;
	vDir.Normalize();

	float fTerm = 25.f;
	Vec2 vPos = m_vPos;

	m_fAfterDuration = 2.f;

	while (vPos.x + 10 < vNextPos.x || vPos.x - 10 > vNextPos.x)
	{
		//float fTemp = (float)random(0, 3);
		m_fAfterColor[0] = 1.f;
		m_fAfterColor[1] = 0.5f;
		m_fAfterColor[2] = 0.f;

		CAfterImage* pImage = new CAfterImage;
		pImage->SetAnim(*Get_Animator()->Get_CurAnim());
		pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
		pImage->SetDir(Get_Dir());
		pImage->Set_RGB(m_fAfterColor);

		pImage->SetAlphaCount(m_fAfterDuration); // 낮게 설정할 수록 잔상이 오래 남음
		m_fAfterDuration -= 0.05f;
		vPos.x += vDir.x * fTerm;
		vPos.y += vDir.y* fTerm;

		pImage->SetPos(vPos);
		CreateObject(pImage, GROUP_TYPE::EFFECTS);
	}
}
#pragma endregion 이펙트 관련

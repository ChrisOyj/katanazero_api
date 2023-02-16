#include "stdafx.h"
#include "CAlive.h"

#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CHitBox.h"

#include "CLaserImage.h"
#include "CLineMgr.h"
#include "CSoundMgr.h"

#include "CEffects_Blood.h"
#include "CAbstractFactory.h"

CAlive::CAlive()
	: m_eState(STATE_TYPE::END)
	, m_bHold(false)
	, m_bLand(false)
	, m_pHitBox(nullptr)
	, m_iAttackCount(0)
{
}

CAlive::~CAlive()
{
}

void CAlive::Initialize()
{
	// ============================== CreateComponent ==============================
	CreateCollider();

	float fWidth = 20.f;
	float fHeight = 4.f;
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));

	m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	// ==============================================================================

	m_bAir = true;
	m_eState = STATE_TYPE::AIR;

	Default();
	
}

void CAlive::Update()
{
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 0.f)
		return;

	switch (m_eState)
	{
	case STATE_TYPE::DEFAULT:
		Update_Default();
		break;

	case STATE_TYPE::WALK:
		Update_Walk();
		break;

	case STATE_TYPE::DASH:
		Update_Dash();
		break;

	case STATE_TYPE::AIR:
		Update_Air();
		break;

	case STATE_TYPE::SIT:
		Update_Sit();
		break;

	case STATE_TYPE::CROUCH:
		Update_Crouch();
		break;

	case STATE_TYPE::SET:
		Update_Set();
		break;

	case STATE_TYPE::RUN:
		Update_Run();
		break;

	case STATE_TYPE::ATTACK:
		Update_Attack();
		break;

	case STATE_TYPE::HANG:
		Update_Hang();
		break;

	case STATE_TYPE::AIRDASH:
		Update_Airdash();
		break;

	case STATE_TYPE::HIT:
		Update_Hit();
		break;

	case STATE_TYPE::DEATH:
		Update_Death();
		break;

	case STATE_TYPE::PARRING:
		Update_Parring();
		break;

	case STATE_TYPE::PLAYMUSIC:
		Update_PlayMusic();
		break;

	case STATE_TYPE::ANIMATION:
		Update_Animation();
		break;

	case STATE_TYPE::SKILL:
		Update_Skill();
		break;

	}

	Physics_Update();

	Get_Animator()->Update();
}

void CAlive::Hit(Vec2 _vDir)
{
	Get_Animator()->Play(L"HIT", false);
	m_eState = STATE_TYPE::HIT;
	m_fTime = 0.f;

	if (-0.2f < _vDir.y)
	{
		_vDir.y = 0.f;
	}

	//m_vDir = _vDir;

	m_tPhysics.fAccel = 0.f;
	m_tPhysics.fXSpeed = 550.f * abs(_vDir.x);
	m_tPhysics.fYSpeed = 60.f * abs(_vDir.y);
	m_tPhysics.fOriginY = m_vPos.y;
	m_tPhysics.fAcc = 0.f;
	m_bAir = true;

	if (0 < _vDir.x)
	{
		SetDir(Vec2(1.f, 0.f));
	}
	else
	{
		SetDir(Vec2(-1.f, 0.f));
	}

	if (0.f == _vDir.y)
	{
		Death();
	}

}

void CAlive::LaserHit()
{
	int iRand = random(0, 1);

	switch (iRand)
	{
	case 0:
		CSoundMgr::Get_Instance()->PlaySound(L"Laser_Death.wav");

		break;
	default:
		CSoundMgr::Get_Instance()->PlaySound(L"Laser_Death_2.wav");

	}


	CLaserImage* pImage = new CLaserImage;

	pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
	pImage->SetAnimFrm(Get_Animator()->Get_CurAnim()->Get_Frm(0));
	pImage->SetImage(Get_Animator()->Get_CurAnim()->Get_Image());

	pImage->SetDir(Get_Dir());
	pImage->SetPos(Get_Pos());
	CreateObject(pImage, GROUP_TYPE::PLAYER);

	SetState(STATE_TYPE::DEATH);
	m_pHitBox->SetCollision(false);

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}

void CAlive::Physics_Update()
{
	float fPrevY = m_vPos.y;

	if (m_bHold)
		return;

	//공중
	if (m_bAir)
	{
		m_tPhysics.fAcc += fDT * 9.5f;

		m_vPos.y = m_tPhysics.fOriginY - ((m_tPhysics.fYSpeed * m_tPhysics.fAcc) - (9.8f * 0.5f * m_tPhysics.fAcc * m_tPhysics.fAcc));

		if (0 < m_tPhysics.fXSpeed) // 속도가 존재하면
			m_tPhysics.fXSpeed -= m_tPhysics.fAirFric * fDT; // 속도는 m_fAirFric만큼 감소
		else
			m_tPhysics.fXSpeed = 0;
	}
	//땅
	else
	{
		if (0 < m_tPhysics.fXSpeed) // 속도가 존재하면
			m_tPhysics.fXSpeed -= m_tPhysics.fFriction * fDT; // 속도는 마찰만큼 감소
		else
			m_tPhysics.fXSpeed = 0;
	}

	if (m_tPhysics.fXSpeed < m_tPhysics.fMaxXSpeed + 30.f)
		m_tPhysics.fXSpeed += (m_tPhysics.fAccel) * 6 * fDT;

	if (m_bStair)
	{
		if (!m_bAir)
		{
			m_vPos.x += m_tPhysics.fXSpeed * m_vDir.x * 0.707f * fDT;
			m_vPos.y += m_tPhysics.fXSpeed * 0.707f * fDT;
		}
		else
		{
			m_vPos.x += m_tPhysics.fXSpeed * m_vDir.x * fDT;
			m_vPos.y += m_tPhysics.fXSpeed * m_vDir.y * fDT;
		}
		
	}
	else
	{
		m_vPos.x += m_tPhysics.fXSpeed * m_vDir.x * fDT;
		m_vPos.y += m_tPhysics.fXSpeed * m_vDir.y * fDT;
	}

	float fY = 0.f;
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_vPos, m_tPhysics.fOffsetY, &fY, &m_bStair, &m_iCurFloor);

	// 1. 땅에서 라인 충돌 중인 경우
	// 라인을 타게 한다.
	if (bLineCol)
	{
		if (m_bAir)
		{

			m_bAir = false;		// 일단 air false
			if (m_eState == STATE_TYPE::HIT) // 상태관련 분기
				Death();
			else if (m_eState == STATE_TYPE::ATTACK)
			{
				m_tPhysics.fXSpeed *= 0.5f;
				m_vDir = m_vRenderDir;

				if (!m_tPhysics.bFalling)
					m_bAir = true;
			}
			else if (m_eState != STATE_TYPE::DEATH) // 공격, 힛, 데스 다 아닐 때 (착지)
			{
				m_tPhysics.fXSpeed = 0.f;
				if (m_tPhysics.bFalling)
					Set();
				else
					m_bAir = true;
			}

		}
		else
		{
			m_vPos.y = fY;
		}
	}
	else if (!m_bAir)
	{
		if (m_bLand)
			return;

		m_bAir = true;
		JUMP(0.f);
	}

	if (m_vPos.y < fPrevY)
		m_tPhysics.bFalling = false;
	else if (m_bAir)
		m_tPhysics.bFalling = true;
}

void CAlive::CreateHitBox()
{
	m_pHitBox = new CHitBox;
	m_pHitBox->SetObjType(GROUP_TYPE::PLAYER_HITBOX);
	m_pHitBox->SetOwner(this);
	CreateObject(m_pHitBox, GROUP_TYPE::PLAYER_HITBOX);

}

void CAlive::CreateBlood(bool _bUp)
{
	Vec2 vPos = Get_Pos();
	float fx = random(-10, 10) * 1.f;
	float fy = random(-10, 10) * 1.f;

	vPos.x += fx * 2.f;

	if (!_bUp)
		vPos.y -= 10.f;
	else
		vPos.y += fy * 2.f;

	if (_bUp)
		fy = random(-10, 0) * 1.f;

	Vec2 vDir = { fx, fy };

	if (0 == fx && 0 == fy)
		vDir = Vec2(0.f, -1.f);

	vDir.Normalize();

	CAbstractFactory<CEffects_Blood>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);

	fx = random(-10, 10) * 1.f;
	fy = random(-10, 10) * 1.f;

	if (_bUp)
		fy = random(-10, 0) * 1.f;

	vDir = Vec2(fx, fy);

	if (0 == fx && 0 == fy)
		vDir = Vec2(0.f, -1.f);

	vDir.Normalize();
	CAbstractFactory<CEffects_Blood>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);
}

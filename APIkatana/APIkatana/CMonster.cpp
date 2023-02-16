#include "stdafx.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CAbstractFactory.h"
#include "CSceneMgr.h"
#include "CCamera.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CLand.h"
#include "CWall.h"
#include "CHitBox.h"
#include "CScene.h"

#include "CMark.h"
#include "CLaserImage.h"
#include "CSight.h"

#include "CLineMgr.h"



CMonster::CMonster()
	: m_fBloodTime(0.f)
	, m_pSight(nullptr)
{
	

}

CMonster::~CMonster()
{
}

void CMonster::OnCollision(CCollider * _pOther)
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
	}
}

void CMonster::OnCollisionEnter(CCollider * _pOther)
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
		SetDirX(Get_Dir().x * -1.f);
		SetRenderDir(Get_RenderDir() * -1.f);
		m_tPhysics.fXSpeed *= 0.5f;
		break;

	case GROUP_TYPE::PLAYER:
		if (STATE_TYPE::RUN == m_eState)
			Attack();

		break;

	default:
		break;

	}
}

void CMonster::OnCollisionExit(CCollider * _pOther)
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
	}
}

void CMonster::Question()
{
	CAlive::Default();
	SetMark(MARK_TYPE::QUESTION);
}

void CMonster::Initialize()
{
	CAlive::Initialize();

	Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜

	m_pHitBox = CAbstractFactory<CHitBox>::Create(this, GROUP_TYPE::MONSTER_HITBOX);
	CreateObject(m_pHitBox, GROUP_TYPE::MONSTER_HITBOX);

	//시야 충돌체
	m_pSight = CAbstractFactory<CSight>::Create(this, GROUP_TYPE::MONSTER_SIGHT);
	m_pSight->SetColSize(Vec2(300.f, 300.f));
	CreateObject(m_pSight, GROUP_TYPE::MONSTER_SIGHT);

	//마크
	m_pMark = new CMark;
	m_pMark->SetOwner(this);
	dynamic_cast<CMark*>(m_pMark)->SetMarkType(MARK_TYPE::END);
	m_pMark->Initialize();
	CreateObject(m_pMark, GROUP_TYPE::EFFECTS);
}

void CMonster::Update()
{
	Vec2 vPos = CCamera::Get_Instance()->Get_RenderPos(m_vPos);
	if ((float)WINCX+100.f < vPos.x || (float)WINCY + 100.f < vPos.y || -100.f > vPos.y || -100.f > vPos.x)
		return;


	*m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };


	if (STATE_TYPE::DEATH != m_eState && CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		*m_colorMatrix = {
			 0.2f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,   0.7f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	

	STATE_TYPE eState = STATE_TYPE::END;
	eState = dynamic_cast<CAlive*>(m_pOwner)->Get_State();

	if (eState == STATE_TYPE::DEATH || eState == STATE_TYPE::HIT)
	{
		if (m_eState != STATE_TYPE::HIT && m_eState != STATE_TYPE::DEATH)
		Default();
	}
	

	CAlive::Update();
}

void CMonster::Render(HDC _dc)
{
	Vec2 vPos = CCamera::Get_Instance()->Get_RenderPos(m_vPos);
	if ((float)WINCX + 100.f < vPos.x || (float)WINCY + 100.f < vPos.y || -100.f > vPos.y || -100.f > vPos.x)
		return;

	CObj::Render(_dc);
}



//void CMonster::physics_Update()
//{
//	Vec2 vPos = Get_Pos();
//	Vec2 vDir = Get_Dir();
//	STATE_TYPE m_eState = Get_State();
//
//
//	//공중
//	if (m_bAir)
//	{
//		if (m_tPhysics.fMaxYSpeed > m_tPhysics.fYSpeed)
//			m_tPhysics.fYSpeed += m_tPhysics.fGravity * fDT;
//		
//
//		if (0 < m_tPhysics.fXSpeed) // 속도가 존재하면
//			m_tPhysics.fXSpeed -= m_tPhysics.fAirFric * fDT; // 속도는 m_tPhysics.fAirFric만큼 감소
//		else
//			m_tPhysics.fXSpeed = 0;
//
//	}
//	//땅
//	else
//	{
//		if (0 < m_tPhysics.fXSpeed) // 속도가 존재하면
//			m_tPhysics.fXSpeed -= m_tPhysics.fFriction * fDT; // 속도는 마찰만큼 감소
//		else
//			m_tPhysics.fXSpeed = 0;
//	}
//	
//	if (m_tPhysics.fAccel)
//	m_tPhysics.fXSpeed = m_tPhysics.fAccel;
//
//	vPos.x += m_tPhysics.fXSpeed * Get_Dir().x * fDT;
//	vPos.y += m_tPhysics.fXSpeed * Get_Dir().y * fDT;
//
//	vPos.y += m_tPhysics.fYSpeed * fDT;
//
//	SetPos(vPos);
//
//}

void CMonster::Update_Default()
{
	m_fTime += fDT;

	if (10.f <= m_fTime)
	{
		Walk();
	}
}


void CMonster::Update_Run()
{
	Vec2 PlayerPos = dynamic_cast<CAlive*>(m_pOwner)->Get_Pos();
	m_tPhysics.fMaxXSpeed = 200.f;
	m_tPhysics.fAccel = m_tPhysics.fMaxAccel;

	if (dynamic_cast<CAlive*>(m_pOwner)->Get_CurFloor() == m_iCurFloor)
	{
		//if (PlayerPos.y < m_vPos.y - 100.f || PlayerPos.y > m_vPos.y + 100.f) // 높이가 많이 차이나면 포기
		//{
		//	//Default();
		//	//return;
		//}
		//else
		{
			//그냥 쫓아가면댐
			//vector<CObj*> vecLaser = CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::LASER);
			



			Vec2 vplayerPos = m_pOwner->Get_Pos();

			if (vplayerPos.x < m_vPos.x)
			{
				SetDirX(-1.f);
				SetRenderDir(Vec2(-1.f, 0.f));

				/*for (int i = 0; i < vecLaser.size(); ++i)
				{
					if (m_vPos.x - 30.f < vecLaser[i]->Get_Pos().x)
					{
						Default();
						return;
					}
						
				}*/

			}
			else
			{
				SetDirX(1.f);
				SetRenderDir(Vec2(1.f, 0.f));

				/*for (int i = 0; i < vecLaser.size(); ++i)
				{
					if (m_vPos.x + 30.f > vecLaser[i]->Get_Pos().x)
					{
						Default();
						return;
					}

				}*/
			}
		}
	}
	else // 층이 다르면 계단 찾기
	{
		Vec2 vStairPos = CLineMgr::Get_Instance()->Get_StairPos(m_iCurFloor, dynamic_cast<CAlive*>(m_pOwner)->Get_CurFloor());

		if (dynamic_cast<CAlive*>(m_pOwner)->Get_CurFloor() > m_iCurFloor) // 캐릭터가 더 높은 층에 있다
		{
			if (vStairPos.x + 0.f < m_vPos.x)
			{
				SetDirX(-1.f);
				SetRenderDir(Vec2(-1.f, 0.f));
			}
			else if (vStairPos.x - 0.f > m_vPos.x)
			{
				SetDirX(1.f);
				SetRenderDir(Vec2(1.f, 0.f));
			}
		}
		else // 캐릭터가 더 낮은 층에 있다
		{
			if (vStairPos.x + 30.f < m_vPos.x)
			{
				SetDirX(-1.f);
				SetRenderDir(Vec2(-1.f, 0.f));
			}
			else if (vStairPos.x - 30.f > m_vPos.x)
			{
				SetDirX(1.f);
				SetRenderDir(Vec2(1.f, 0.f));
			}
			else // 계단에 도착함
			{
				m_iCurFloor = dynamic_cast<CAlive*>(m_pOwner)->Get_CurFloor();
				m_vPos.y += 11.f;
				JUMP(0);
			}
		}


		
	}
		

	


}

void CMonster::Update_Walk()
{
	m_tPhysics.fMaxXSpeed = 50.f;

	m_tPhysics.fAccel = m_tPhysics.fMaxAccel / 2.f;

	m_fTime += fDT;

	if (10.f <= m_fTime)
	{
		Default();
	}

}

void CMonster::Update_Hit()
{

	m_fBloodTime += fDT;
	if (0.02f < m_fBloodTime)
	{
		CreateBlood(false);
		m_fBloodTime = 0.f;
	}
}

void CMonster::Update_Death()
{

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	if (TimeLimit / 1.5f <= m_fTime)
	{
		return;
	}
	else
	{
		m_fBloodTime += fDT;
		if (0.2f < m_fBloodTime)
		{
			CreateBlood(true);
			m_fBloodTime = 0.f;
		}
	}

	m_fTime += fDT;

}

void CMonster::Update_Parring()
{
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

	if (m_fTime >= 0.5f)
	{
		m_pHitBox->SetCollision(true);
	}
	if (TimeLimit <= m_fTime)
	{
		Run();
		m_iAttackCount = 0;
	}
}


void CMonster::Default()
{
	Get_Animator()->Play(L"STANCE", true);
	m_tPhysics.fAccel = 0.f;
	m_tPhysics.fYSpeed = 0.f;
	m_fTime = 0.f;
	m_eState =(STATE_TYPE::DEFAULT);

}

void CMonster::Attack()
{
	
		

	Get_Animator()->Play(L"ATTACK", true);
	m_tPhysics.fAccel = 0.f;
	m_fTime = 0.f;
	m_iAttackCount = 0;
	m_eState = STATE_TYPE::ATTACK;

	if (MOB_TYPE::GANGSTER != m_eMobType)
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Throw.wav");


}

void CMonster::Walk()
{
	Get_Animator()->Play(L"WALK", true);
	m_vDir.x *= -1.f;
	m_vRenderDir = m_vDir;

	m_fTime = 0.f;
	m_eState =(STATE_TYPE::WALK);


}

void CMonster::Run()
{
	Get_Animator()->Play(L"RUN", true);
	m_eState =(STATE_TYPE::RUN);
	m_fTime = 0.f;

	SetMark(MARK_TYPE::EXCLAIM2);

}

void CMonster::Parring(CObj* pOther)
{
	Get_Animator()->Play(L"PARRING", true);
	m_eState = STATE_TYPE::PARRING;
	m_fTime = 0.f;

	//m_vDir = _vDir;

	m_tPhysics.fAccel = 0.f;
	m_tPhysics.fXSpeed = 400.f;

	if (pOther->Get_Pos().x < m_vPos.x)
		m_vDir.x = 1.f;
	else
		m_vDir.x = -1.f;

	m_pHitBox->SetCollision(false);
}

void CMonster::Hit(Vec2 _vDir)
{
	CAlive::Hit(_vDir);

	if (g_bCinema)
	{
		CTimeMgr::Get_Instance()->SetTimeSpeed(0.1f);
		CCamera::Get_Instance()->SetTarget(this);
		CCamera::Get_Instance()->SetZoom(ZOOM);
	}

	if (m_pSight)
	{
		DeleteObject(m_pSight);
		m_pSight = nullptr;
	}

	SetMark(MARK_TYPE::END);

	int iRand = random(0, 1);
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		switch (iRand)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySound(L"Slow_Kill.wav");
			break;

		case 1:
			CSoundMgr::Get_Instance()->PlaySound(L"Slow_Kill_2.wav");
			break;
		}
	}
	else
	{
		switch (iRand)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySound(L"Monster_Hit.wav");
			break;

		case 1:
			CSoundMgr::Get_Instance()->PlaySound(L"Monster_Hit_2.wav");
			break;
		}
	}
}

void CMonster::LaserHit()
{
	CAlive::LaserHit();
	if (m_pSight)
	{
		DeleteObject(m_pSight);
		m_pSight = nullptr;
	}
	SetMark(MARK_TYPE::END);
	DeleteObject(this);
}


void CMonster::Death()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Monster_Death.wav");

	Get_Animator()->Play(L"DEATH", false);
	m_eState =(STATE_TYPE::DEATH);
	JUMP(0);
	m_fBloodTime = 0.f;
	m_pHitBox->SetCollision(false);

	if (m_pSight)
	{
		DeleteObject(m_pSight);
		m_pSight = nullptr;
	}

}

void CMonster::SetMark(MARK_TYPE _eType)
{
	dynamic_cast<CMark*>(m_pMark)->SetMarkType(_eType);
	m_pMark->Initialize();
}

//void CMonster::Physics_Update()
//{
//	//공중
//	if (m_bAir)
//	{
//		if (0 < m_tPhysics.fXSpeed) // 속도가 존재하면
//			m_tPhysics.fXSpeed -= m_tPhysics.fAirFric * fDT; // 속도는 m_fAirFric만큼 감소
//		else
//			m_tPhysics.fXSpeed = 0;
//	}
//	//땅
//	else
//	{
//		if (0 < m_tPhysics.fXSpeed) // 속도가 존재하면
//			m_tPhysics.fXSpeed -= m_tPhysics.fFriction * fDT; // 속도는 마찰만큼 감소
//		else
//			m_tPhysics.fXSpeed = 0;
//	}
//
//	if (m_tPhysics.fAccel)
//		m_tPhysics.fXSpeed = m_tPhysics.fAccel;
//
//	if (m_pLand)
//	{
//		Vec2 vDir = m_pLand->Get_Dir();
//		m_vPos.x += m_tPhysics.fXSpeed * m_vDir.x * vDir.x * fDT;
//		m_vPos.y += m_tPhysics.fXSpeed * m_vDir.y * fDT;
//	}
//	else
//	{
//		m_vPos.x += m_tPhysics.fXSpeed * m_vDir.x * fDT;
//		m_vPos.y += m_tPhysics.fXSpeed * m_vDir.y * fDT;
//	}
//
//
//	m_vPos.y += m_tPhysics.fYSpeed * fDT;
//}

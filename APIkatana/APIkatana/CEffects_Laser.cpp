#include "stdafx.h"
#include "CEffects_Laser.h"

#include "CTimeMgr.h"
#include "CAlive.h"

CEffects_Laser::CEffects_Laser()
{
}

CEffects_Laser::~CEffects_Laser()
{
}

void CEffects_Laser::OnCollisionEnter(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();

	switch (pOtherObj->Get_ObjType())
	{
	case GROUP_TYPE::PLAYER_HITBOX:
	case GROUP_TYPE::MONSTER_HITBOX:
		dynamic_cast<CAlive*>(pOtherObj->Get_Owner())->LaserHit();
		pOtherObj->SetCollision(false);
		break;


	case GROUP_TYPE::PLAYER:
	case GROUP_TYPE::MONSTER:
		if (STATE_TYPE::HIT == dynamic_cast<CAlive*>(pOtherObj)->Get_State() || STATE_TYPE::DEATH == dynamic_cast<CAlive*>(pOtherObj)->Get_State())
			dynamic_cast<CAlive*>(pOtherObj)->LaserHit();

		break;
	}
}

void CEffects_Laser::Initialize()
{
	CreateCollider();

	float fWidth = 10.f;
	float fHeight = 120.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, 60.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));

	SetScale(Vec2(10.f, 100.f));
	m_tInfo.RGB[0] = 0;
	m_tInfo.RGB[1] = 255;
	m_tInfo.RGB[2] = 255;
	m_tInfo.iAlpha = 255;
}

void CEffects_Laser::Update()
{
	m_fTime += fDT;

	Vec2 vScale = Get_Scale();
	vScale.x -= 35.f * fDT;
	SetScale(vScale);

	if (1.f >= vScale.x)
	{
		DeleteObject(this);
	}
	if (0.03 < m_fTime)
	{
		m_fTime = 0.f;
		if (m_tInfo.RGB[0] == 255)
		{
			m_tInfo.RGB[0] = 0;
			m_tInfo.RGB[1] = 255;
			m_tInfo.RGB[2] = 255;
		}
		else
		{
			m_tInfo.RGB[0] = 255;
			m_tInfo.RGB[1] = 190;
			m_tInfo.RGB[2] = 30;
		}
	}
}

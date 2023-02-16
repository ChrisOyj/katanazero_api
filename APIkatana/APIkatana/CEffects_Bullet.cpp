#include "stdafx.h"
#include "CEffects_Bullet.h"

#include "CAbstractFactory.h"
#include "CEffects_BulletReflect.h"
#include "CEffects_Cut.h"
#include "CSoundMgr.h"

CEffects_Bullet::CEffects_Bullet()
{
}

CEffects_Bullet::~CEffects_Bullet()
{
}

void CEffects_Bullet::OnCollisionEnter(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();

	DeleteObject(this);
	SetCollision(false);

	if (pOtherObj->Get_ObjType() == GROUP_TYPE::SLASH || pOtherObj->Get_ObjType() == GROUP_TYPE::SUBATTACK)
	{
		Vec2 vPos = m_vPos;
		Vec2 vDir = Get_Dir();
		vDir.x *= -1.f;
		vDir.y *= -1.f;

		CAbstractFactory<CEffects_Bullet>::Create_Effects(pOtherObj->Get_Owner(), m_vPos, vDir, GROUP_TYPE::SLASH);
		vPos.x += 20.f * vDir.x;
		vPos.y += 20.f * vDir.y;
		CAbstractFactory<CEffects_BulletReflect>::Create_Effects(nullptr, vPos, vDir, GROUP_TYPE::EFFECTS);
		CAbstractFactory<CEffects_Cut>::Create_Effects(nullptr, vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);
		CCamera::Get_Instance()->SetVibrate();

		int iRand = random(0, 2);

		if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
		{
			switch (iRand)
			{
			case 0:
				CSoundMgr::Get_Instance()->PlaySound(L"Slow_Reflect.wav");
				break;

			case 1:
				CSoundMgr::Get_Instance()->PlaySound(L"Slow_Reflect_2.wav");
				break;

			case 2:
				CSoundMgr::Get_Instance()->PlaySound(L"Slow_Reflect_3.wav");
				break;
			}
		}
		else
		{
			CSoundMgr::Get_Instance()->PlaySound(L"BulletReflect.wav");
		}

	}
	else
	{
		if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
			CSoundMgr::Get_Instance()->PlaySound(L"Slow_GunHit_2.wav");
		else
			CSoundMgr::Get_Instance()->PlaySound(L"Monster_GunHit.wav");

	}

}

void CEffects_Bullet::Initialize()
{
	CreateCollider();
	Get_Collider()->SetScale(Vec2(15.f, 4.f));

	Set_Texture(L"Effects_Bullet", 1, 0.03f, EFFECT_TYPE::BULLET);
	m_fSpeed = 1200.f;
	m_fTimeLimit = 30.f;

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;
}

void CEffects_Bullet::Update()
{
	Effects_Move();
	Effects_Time();
}

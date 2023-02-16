#include "stdafx.h"
#include "CSub_Knife.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"

#include "CAbstractFactory.h"
#include "CLineMgr.h"
#include "CSoundMgr.h"
#include "CTimeMgr.h"
#include "CEffects_BulletReflect.h"
#include "CEffects_Cut.h"

#include "CSubWeapon.h"

CSub_Knife::CSub_Knife()
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Knife", L"texture\\SubWeapon\\SubWeapon_Knife.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Knife", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	m_pAnimator->Play(L"SubWeapon_Knife", false);
}

CSub_Knife::~CSub_Knife()
{
}

void CSub_Knife::OnCollisionEnter(CCollider* _pOther)
{
	CSub::OnCollisionEnter(_pOther);

	GROUP_TYPE eType = _pOther->Get_Obj()->Get_ObjType();

	if (GROUP_TYPE::MONSTER_ATTACK == eType || GROUP_TYPE::MOBSUBATTACK == eType)
	{
		Vec2 vPos = m_vPos;
		Vec2 vDir = Get_Dir();
		vDir.x *= -1.f;
		vDir.y *= -1.f;

		CObj* pSub = CAbstractFactory<CSub_Knife>::Create();
		pSub->SetDir(vDir);
		pSub->SetOwner(_pOther->Get_Obj()->Get_Owner());
		pSub->SetPos(m_vPos);
		pSub->SetObjType(GROUP_TYPE::MOBSUBATTACK);
		CreateObject(pSub, GROUP_TYPE::MOBSUBATTACK);
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
	else if (GROUP_TYPE::SLASH == eType)
	{
		Vec2 vPos = m_vPos;
		Vec2 vDir = Get_Dir();
		vDir.x *= -1.f;
		vDir.y *= -1.f;

		CObj* pSub = CAbstractFactory<CSub_Knife>::Create();
		pSub->SetDir(vDir);
		pSub->SetOwner(_pOther->Get_Obj());
		pSub->SetPos(m_vPos);
		pSub->SetObjType(GROUP_TYPE::SUBATTACK);
		CreateObject(pSub, GROUP_TYPE::SUBATTACK);
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
	else if (GROUP_TYPE::MONSTER_HITBOX != eType && GROUP_TYPE::PLAYER_HITBOX != eType)
	{
		CObj* pObj = new CSubWeapon;
		pObj->SetPos(m_vPos);
		dynamic_cast<CSubWeapon*>(pObj)->SetSubType(SUB_TYPE::KNIFE);
		pObj->Initialize();
		pObj->SetTheta(m_fTheta);
		pObj->SetObjType(GROUP_TYPE::SUBWEAPON);
		CreateObject(pObj, GROUP_TYPE::SUBWEAPON);
		CSoundMgr::Get_Instance()->PlaySound(L"Knife.wav");
	}


	

}

void CSub_Knife::Update()
{
	CSub::Update();

	float fy = 0.f;
	bool bStair;
	int iFloor;

	if (CLineMgr::Get_Instance()->Collision_Line(m_vPos, 0.f, &fy, &bStair, &iFloor))
	{
		m_vPos.y = fy;
		CAbstractFactory<CSubWeapon>::Create_Sub(m_vPos, SUB_TYPE::KNIFE);
		DeleteObject(this);
	}


}

#include "stdafx.h"
#include "CSub_Smoke.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"

#include "CAbstractFactory.h"
#include "CLineMgr.h"

#include "CSubWeapon.h"
#include "CEffects_Smoke.h"

#include "CSoundMgr.h"

CSub_Smoke::CSub_Smoke()
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Smoke", L"texture\\SubWeapon\\SubWeapon_Smoke.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Smoke", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	m_pAnimator->Play(L"SubWeapon_Smoke", false);
}

CSub_Smoke::~CSub_Smoke()
{
}

void CSub_Smoke::OnCollisionEnter(CCollider* _pOther)
{
	CSub::OnCollisionEnter(_pOther);
	CreateSmoke();
}

void CSub_Smoke::Update()
{
	CSub::Update();

	float fy = 0.f;
	bool bStair;
	int iFloor;

	if (CLineMgr::Get_Instance()->Collision_Line(m_vPos, 0.f, &fy, &bStair, &iFloor))
	{
		m_vPos.y = fy;
		DeleteObject(this);
		CreateSmoke();
	}


}

void CSub_Smoke::CreateSmoke()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Smoke.wav");

	Vec2 vPos = m_vPos;
	Vec2 vDir = m_vDir;
	if (fabs(vDir.y) < fabs(vDir.x)) // аб©Л
	{
		if (vDir.x < 0)
			vDir.x = 1.f;
		else
			vDir.x = -1.f;

		vDir.y = 0.f;
	}
	else
	{
		if (vDir.y < 0)
			vDir.y = 1.f;
		else
			vDir.y = -1.f;

		vDir.x = 0.f;
	}

	for (int i = 0; i < 60; ++i)
	{
		CObj* pObj = CAbstractFactory<CEffects_Smoke>::Create(vPos, vDir, GROUP_TYPE::SMOKE);
		CreateObject(pObj, GROUP_TYPE::SMOKE);
	}
}

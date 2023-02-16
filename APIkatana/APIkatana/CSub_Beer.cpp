#include "stdafx.h"
#include "CSub_Beer.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"

#include "CAbstractFactory.h"
#include "CLineMgr.h"

#include "CSubWeapon.h"
#include "CEffects_Glass.h"

#include "CSoundMgr.h"

CSub_Beer::CSub_Beer()
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Beer", L"texture\\SubWeapon\\SubWeapon_Beer.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Beer", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);



	m_pAnimator->Play(L"SubWeapon_Beer", false);
}

CSub_Beer::~CSub_Beer()
{
}

void CSub_Beer::OnCollisionEnter(CCollider* _pOther)
{
	CSub::OnCollisionEnter(_pOther);
	CreateGlass();
}

void CSub_Beer::Update()
{
	CSub::Update();

	float fy = 0.f;
	bool bStair;
	int iFloor;

	if (CLineMgr::Get_Instance()->Collision_Line(m_vPos, 0.f, &fy, &bStair, &iFloor))
	{
		m_vPos.y = fy;
		DeleteObject(this);
		CreateGlass();
	}


}

void CSub_Beer::CreateGlass()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Bottle_2.wav");

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

	for (int i = 0; i < 20; ++i)
	{
		float fRand = (float)random(-5, 5);
		float fRand2 = (float)random(-5, 5);
		vPos.x += fRand;
		vPos.y += fRand2;
		CObj* pObj = CAbstractFactory<CEffects_Glass>::Create(vPos, vDir, GROUP_TYPE::GLASS);
		dynamic_cast<CEffects_Glass*>(pObj)->SetOriginY(vPos.y);
		dynamic_cast<CEffects_Glass*>(pObj)->SetOrange();
		CreateObject(pObj, GROUP_TYPE::GLASS);
	}
}

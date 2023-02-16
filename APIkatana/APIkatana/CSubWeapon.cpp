#include "stdafx.h"
#include "CSubWeapon.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"
#include "CCollider.h"

#include "CAbstractFactory.h"
#include "CEffects_PickUp.h"

#include "CKeyMgr.h"
#include "CPlayer.h"

CSubWeapon::CSubWeapon()
{
	CreateCollider();

	float fWidth = 100.f;
	float fHeight = 100.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, 50.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));

	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Knife", L"texture\\SubWeapon\\SubWeapon_Knife.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Knife", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Bottle", L"texture\\SubWeapon\\SubWeapon_Bottle.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Bottle", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Beer", L"texture\\SubWeapon\\SubWeapon_Beer.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Beer", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Smoke", L"texture\\SubWeapon\\SubWeapon_Smoke.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Smoke", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	CreateColorMatrix();

}

CSubWeapon::~CSubWeapon()
{
}

void CSubWeapon::OnCollisionEnter(CCollider * _pOther)
{
	if (_pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::PLAYER)
		CreatePickUp();
}


void CSubWeapon::OnCollisionExit(CCollider * _pOther)
{
	if (_pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::PLAYER)
		dynamic_cast<CEffects*>(m_pOwner)->Set_Delete();

}

void CSubWeapon::Initialize()
{

	switch (m_eType)
	{
	case SUB_TYPE::KNIFE:
		Get_Animator()->Play(L"SubWeapon_Knife", false);
		break;

	case SUB_TYPE::BOTTLE:
		Get_Animator()->Play(L"SubWeapon_Bottle", false);
		break;

	case SUB_TYPE::SMOKE:
		Get_Animator()->Play(L"SubWeapon_Smoke", false);
		break;

	case SUB_TYPE::BEER:
		Get_Animator()->Play(L"SubWeapon_Beer", false);
		break;
	}
}

void CSubWeapon::Update()
{
	
}

void CSubWeapon::Render(HDC _dc)
{
	m_pAnimator->dir_Render(_dc, Color(255, 255, 255), Color(255, 255, 255));
}

void CSubWeapon::CreatePickUp()
{
	Vec2 vPos = Get_Pos();
	vPos.y -= 20.f;
	m_pOwner = CAbstractFactory<CEffects_PickUp>::Create();
	m_pOwner->SetPos(vPos);
	CreateObject(m_pOwner, GROUP_TYPE::SUBWEAPON);
}
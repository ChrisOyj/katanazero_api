#include "stdafx.h"
#include "CMonster_Slash.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"
#include "CCollider.h"

#include "CSlash.h"

CMonster_Slash::CMonster_Slash()
	: m_fBulletSpeed(1200.f)
{
	CreateCollider();

	float fWidth = 50.f;
	float fHeight = 20.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));

	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_GrantSlash", L"texture\\Effects\\Effects_GrantSlash.png");
	iCount = 4;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Effects_GrantSlash", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.03f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_Bullet", L"texture\\Effects\\Effects_Bullet.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Effects_Bullet", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.03f, iCount);



}

CMonster_Slash::~CMonster_Slash()
{
}

void CMonster_Slash::OnCollisionEnter(CCollider* _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();

	//총알은 닿으면 무조건 삭제
	if (m_eType == EFFECT_TYPE::BULLET)
	{
		DeleteObject(this);
		SetCollision(false);
	}

	if (pOtherObj->Get_ObjType() == GROUP_TYPE::SLASH && m_eType == EFFECT_TYPE::BULLET)
	{
		CMonster_Slash* pNewBullet = new CMonster_Slash;
		pNewBullet->SetPos(Get_Pos());
		pNewBullet->SetEffectType(EFFECT_TYPE::BULLET);

		Vec2 vDir = Get_Dir();
		vDir.x *= -1.f;
		vDir.y *= -1.f;
		pNewBullet->SetDir(vDir);

		pNewBullet->SetOwner(pOtherObj->Get_Owner()); // 플레이어
		pNewBullet->SetObjType(GROUP_TYPE::SLASH);
		pNewBullet->Initialize();
		CreateObject(pNewBullet, GROUP_TYPE::SLASH);

		CreateReflect(vDir);
		CreateCut();
		CCamera::Get_Instance()->SetVibrate();


	}
}

void CMonster_Slash::Initialize()
{
	switch (m_eType)
	{
	case EFFECT_TYPE::GRANT_SLASH:
		Get_Animator()->Play(L"Effects_GrantSlash", false);

		break;

	case EFFECT_TYPE::BULLET:
		Get_Animator()->Play(L"Effects_Bullet", false);
		Get_Collider()->SetScale(Vec2(15.f, 4.f));


		break;
	}
}

void CMonster_Slash::Update()
{
	switch (m_eType)
	{
	case EFFECT_TYPE::GRANT_SLASH:
		Update_slash();

		break;

	case EFFECT_TYPE::BULLET:
		Update_bullet();


		break;
	}
}

void CMonster_Slash::Render(HDC _dc)
{
	CObj::Component_dir_Render(_dc);

	if (EFFECT_TYPE::BULLET == m_eType)
	{
		Get_Animator()->dir_Render(_dc);
	}
	else
		Get_Animator()->Render(_dc);
}

void CMonster_Slash::Update_slash()
{
	Vec2 vPos = Get_Owner()->Get_Pos();
	vPos.x += 10.f * Get_Dir().x;
	vPos.y -= 12.f;
	SetPos(vPos);

	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();
	m_fTime += fDT;

	if (TimeLimit <= m_fTime)
	{
		DeleteObject(this);
	}

	Get_Animator()->Update();
}

void CMonster_Slash::Update_bullet()
{
	Vec2 vPos = Get_Pos();
	Vec2 vDir = Get_Dir();

	vPos.x += m_fBulletSpeed * vDir.x * fDT;
	vPos.y += m_fBulletSpeed * vDir.y * fDT;

	SetPos(vPos);

}

void CMonster_Slash::CreateReflect(Vec2 _vDir)
{
	Vec2 vPos = Get_Pos();
	vPos.x += 20.f * _vDir.x;
	vPos.y += 20.f * _vDir.y;



	/*CEffects* pEffects = new CEffects;
	pEffects->SetEffectType(EFFECT_TYPE::BULLETREFLECT);
	pEffects->SetPos(vPos);
	pEffects->Initialize();
	CreateObject(pEffects, GROUP_TYPE::EFFECTS);*/
}

void CMonster_Slash::CreateCut()
{
	//Vec2 vPos = Get_Pos();
	//CEffects* pEffects = new CEffects;
	//pEffects->SetEffectType(EFFECT_TYPE::CUT);
	//pEffects->SetPos(vPos);
	//pEffects->Initialize();
	//CreateObject(pEffects, GROUP_TYPE::EFFECTS);

}

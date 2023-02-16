#include "stdafx.h"
#include "CEffects_Smoke.h"

#include "CSmokeCol.h"

CEffects_Smoke::CEffects_Smoke()
{
}

CEffects_Smoke::~CEffects_Smoke()
{
}


void CEffects_Smoke::OnCollisionEnter(CCollider * pOther)
{
	if (pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::SLASH)
		m_tInfo.bDelete = true;

}

void CEffects_Smoke::OnCollision(CCollider * pOther)
{
	if (pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::SMOKE)
	{
		Vec2 vOtherPos = pOther->Get_Obj()->Get_Pos();
		if (m_vPos.x < vOtherPos.x)
			m_vPos.x -= 1.f *fDT;
		else
			m_vPos.x += 1.f *fDT;

		if (m_vPos.y < vOtherPos.y)
			m_vPos.y -= 1.f *fDT;
		else
			m_vPos.y += 1.f *fDT;
	}
}

void CEffects_Smoke::OnCollisionExit(CCollider * pOther)
{
	
}

void CEffects_Smoke::Initialize()
{
	m_pOwner = new CSmokeCol;
	m_pOwner->Initialize();
	m_pOwner->SetOwner(this);
	m_pOwner->SetObjType(GROUP_TYPE::SMOKE);
	CreateObject(m_pOwner, GROUP_TYPE::SMOKE);

	CreateCollider();
	m_pCollider->SetScale(Vec2(8.f, 8.f));
	m_pCollider->SetCircle();

	Set_Texture(L"Effects_Smoke_Dissolve", 7, 0.08f, EFFECT_TYPE::GLASS);
	float fRand = (float)random(5, 15);
	fRand *= 0.01f;
	Set_Texture(L"Effects_Smoke_Loop", 5, fRand, EFFECT_TYPE::GLASS);
	Set_Texture(L"Effects_Smoke_Appear", 3, 0.08f, EFFECT_TYPE::GLASS);

	m_tInfo.bDelete = false;

	//¹æÇâ ·£´ý
	float fy = (float)random(-20, 20);

	if (m_vDir.y == 0.f) // ÁÂ, ¿ì
	{
		m_vDir.x *= 15.f;
		m_vDir.y = fy;
	}
	else // »ó, ÇÏ
	{
		m_vDir.y *= 15.f;
		m_vDir.x = fy;
	}

	m_vDir.Normalize();

	//¸ñÇ¥ÁöÁ¡ ·£´ý
	float fDis = (float)random(0, 100);

	m_vTargetPos.x = m_vPos.x + fDis * m_vDir.x;
	m_vTargetPos.y = m_vPos.y + fDis * m_vDir.y;

	*m_colorMatrix = {
		   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}

void CEffects_Smoke::Update()
{
	//if (m_fTime < 1.5f)
	//{
		if (m_vTargetPos.x - 1.f < m_vPos.x || m_vTargetPos.x + 1.f > m_vPos.x)
		{
			m_fSpeed = m_vTargetPos.x - m_vPos.x;
			m_vPos.x += m_fSpeed * fDT * 0.8f;
		}
		if (m_vTargetPos.y - 1.f < m_vPos.y || m_vTargetPos.y + 1.f > m_vPos.y)
		{
			m_fSpeed = m_vTargetPos.y - m_vPos.y;
			m_vPos.y += m_fSpeed * fDT * 0.8f;
		}
	//}

		float fRand = (float)random(-10, 10);
		float fRand2 = (float)random(-10, 10);
		m_vPos.x += fRand * fDT;
		m_vPos.y += fRand2 * fDT;
	


	if (m_tInfo.bDelete)
	{
		m_pAnimator->Play(L"Effects_Smoke_Dissolve", false);
		m_fAcc += fDT;
		m_fTimeLimit = m_pAnimator->Get_CurAnim()->Get_MaxTime();
		if (m_fTimeLimit < m_fAcc)
			DeleteObject(this);

	}
	else if (m_fTimeLimit <= m_fTime)
	{
		m_pAnimator->Play(L"Effects_Smoke_Loop", true);
		m_fTime += fDT;
	}
	else
		m_fTime += fDT;


	Get_Animator()->Update();

}

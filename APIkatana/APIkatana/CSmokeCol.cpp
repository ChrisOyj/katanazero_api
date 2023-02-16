#include "stdafx.h"
#include "CSmokeCol.h"

#include "CEffects.h"
#include "CTimeMgr.h"

#include "CPlayer.h"

CSmokeCol::CSmokeCol()
{
}

CSmokeCol::~CSmokeCol()
{
}

void CSmokeCol::OnCollisionEnter(CCollider * _pOther)
{
	
}

void CSmokeCol::OnCollision(CCollider * _pOther)
{
	if (_pOther->Get_Obj()->Get_ObjType() != GROUP_TYPE::SMOKE)
	{
		ColorMatrix cm = {
			 0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 0.7f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		_pOther->Get_Obj()->Get_Owner()->SetColorMatrix(cm);

		if (_pOther->Get_Obj()->Get_Owner()->Get_ObjType() == GROUP_TYPE::PLAYER)
			dynamic_cast<CPlayer*>(_pOther->Get_Obj()->Get_Owner())->SetSmoke();
	}

}

void CSmokeCol::OnCollisionExit(CCollider * _pOther)
{
	if (_pOther->Get_Obj()->Get_ObjType() != GROUP_TYPE::SMOKE)
	{
		if (m_fTime > 0.5f)
		{
			dynamic_cast<CEffects*>(m_pOwner)->Set_Delete();

			DeleteObject(this);
		}

		ColorMatrix cm = {
				 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
				0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
				0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
				0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

			_pOther->Get_Obj()->Get_Owner()->SetColorMatrix(cm);

			if (_pOther->Get_Obj()->Get_Owner()->Get_ObjType() == GROUP_TYPE::PLAYER)
				dynamic_cast<CPlayer*>(_pOther->Get_Obj()->Get_Owner())->SetSmoke(false);
		
	}

}

void CSmokeCol::Initialize()
{
	CreateCollider();
	m_pCollider->SetScale(Vec2(50.f, 50.f));
	m_pCollider->SetCircle();
}

void CSmokeCol::Update()
{
	m_fTime += fDT;
	m_vPos = m_pOwner->Get_Pos();
}

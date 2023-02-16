#include "stdafx.h"
#include "CFall.h"

#include "CAlive.h"
#include "CCamera.h"

#include "CAbstractFactory.h"
#include "CEffects_DeadUI.h"

CFall::CFall()
{
	CreateCollider();
	m_pCollider->SetScale(Vec2(300.f, 200.f));
}

CFall::~CFall()
{
}

void CFall::OnCollisionEnter(CCollider * pOther)
{
	dynamic_cast<CAlive*>(pOther->Get_Obj())->Death();
	CCamera::Get_Instance()->SetVibrate();

	if (pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::PLAYER)
		CreateObject(CAbstractFactory<CEffects_DeadUI>::Create(), GROUP_TYPE::UI);


}

void CFall::Update()
{
}

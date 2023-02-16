#include "stdafx.h"
#include "CCeiling.h"

#include "CAlive.h"
#include "CCollider.h"

CCeiling::CCeiling()
{
}

CCeiling::~CCeiling()
{
}

void CCeiling::SetScale(Vec2 _vScale)
{
	m_vScale = _vScale;
	Get_Collider()->SetScale(m_vScale);
	//Get_Collider()->SetOffSetPos(Vec2(0.f, m_vScale.y * 0.5f)); //오프셋 만져주면 충돌체 위치 바뀜

}

void CCeiling::Initialize()
{
	CreateCollider();

	m_vScale = Vec2(1000.f, 6.f);

	//Get_Collider()->SetOffSetPos(Vec2(0.f, m_vScale.y * 0.5f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(m_vScale);
}

void CCeiling::Update()
{
}

void CCeiling::OnCollisionEnter(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj()->Get_Owner();

	if (_pOther->Get_Obj()->Get_ObjType() != GROUP_TYPE::SUBATTACK && _pOther->Get_Obj()->Get_ObjType() != GROUP_TYPE::MOBSUBATTACK && _pOther->Get_Obj()->Get_ObjType() != GROUP_TYPE::GLASS)
	{
		dynamic_cast<CAlive*>(pOtherObj)->SetBlocked();
	}

	/*if (pOtherObj->Get_ObjType() == GROUP_TYPE::SUBATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::MONSTER_ATTACK)
	{

	}*/

}

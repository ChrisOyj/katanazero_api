#include "stdafx.h"
#include "CLand.h"

#include "CAlive.h"
#include "CCollider.h"

CLand::CLand()
{
}

CLand::~CLand()
{
}

void CLand::SetScale(Vec2 _vScale)
{
	m_vScale = _vScale;
	Get_Collider()->SetScale(m_vScale);
	//Get_Collider()->SetOffSetPos(Vec2(0.f, m_vScale.y * 0.5f)); //오프셋 만져주면 충돌체 위치 바뀜

}

void CLand::Initialize()
{
	CreateCollider();

	m_vScale = Vec2(1000.f, 6.f);

	//Get_Collider()->SetOffSetPos(Vec2(0.f, m_vScale.y * 0.5f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(m_vScale);
}

void CLand::Update()
{
}

void CLand::OnCollisionEnter(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();
	if (pOtherObj->Get_ObjType() == GROUP_TYPE::MONSTER_ATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::SUBATTACK
		|| pOtherObj->Get_ObjType() == GROUP_TYPE::MOBSUBATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::GLASS)
		return;

	PhysicsInfo tInfo = dynamic_cast<CAlive*>(pOtherObj)->Get_Physics();

	if (!tInfo.bFalling)
		return;

	if (dynamic_cast<CAlive*>(pOtherObj)->IsAir())
		dynamic_cast<CAlive*>(pOtherObj)->SetAir(false);

	if (dynamic_cast<CAlive*>(pOtherObj)->Get_State() == STATE_TYPE::HIT)
		dynamic_cast<CAlive*>(pOtherObj)->Death();

	dynamic_cast<CAlive*>(pOtherObj)->SetXSpeed(0.f);
}

void CLand::OnCollision(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();
	if (pOtherObj->Get_ObjType() == GROUP_TYPE::MONSTER_ATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::SUBATTACK
		|| pOtherObj->Get_ObjType() == GROUP_TYPE::MOBSUBATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::GLASS)
		return;
	PhysicsInfo tInfo = dynamic_cast<CAlive*>(pOtherObj)->Get_Physics();

	if (!tInfo.bFalling)
		return;

	if (dynamic_cast<CAlive*>(pOtherObj)->IsAir())
		dynamic_cast<CAlive*>(pOtherObj)->SetAir(false);

	if (dynamic_cast<CAlive*>(pOtherObj)->Get_State() == STATE_TYPE::HIT )
		dynamic_cast<CAlive*>(pOtherObj)->Death();

	Vec2 vPos = pOtherObj->Get_Pos();
	float fOffset = dynamic_cast<CAlive*>(pOtherObj)->Get_Physics().fOffsetY;
	vPos.y = m_vPos.y - fOffset;
	_pOther->Get_Obj()->SetPos(vPos);
}

void CLand::OnCollisionExit(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();
	if (pOtherObj->Get_ObjType() == GROUP_TYPE::MONSTER_ATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::SUBATTACK
		|| pOtherObj->Get_ObjType() == GROUP_TYPE::MOBSUBATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::GLASS)
		return;
	PhysicsInfo tInfo = dynamic_cast<CAlive*>(pOtherObj)->Get_Physics();
	if (!tInfo.bFalling)
		return;
	dynamic_cast<CAlive*>(pOtherObj)->SetAir(true);
}

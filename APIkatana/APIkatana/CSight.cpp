#include "stdafx.h"
#include "CSight.h"

#include "CCollider.h"
#include "CAlive.h"
#include "CMonster.h"

CSight::CSight()
{
	CreateCollider();

	float fWidth = 100.f;
	float fHeight = 100.f;

	m_pCollider->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜
	m_pCollider->SetScale(Vec2(fWidth, fHeight));
	m_pCollider->SetCircle();
}


CSight::~CSight()
{
}

void CSight::OnCollision(CCollider * _pOther)
{
	STATE_TYPE eState = dynamic_cast<CAlive*>(m_pOwner)->Get_State();
	MOB_TYPE mob_type = dynamic_cast<CMonster*>(m_pOwner)->Get_MobType();
	CObj* pPlayer = _pOther->Get_Obj()->Get_Owner();


	if (eState == STATE_TYPE::DEATH || eState == STATE_TYPE::HIT)
		return;


	switch (mob_type)
	{
	/*case MOB_TYPE::GRANT:
	case MOB_TYPE::POMP:
		if (dynamic_cast<CAlive*>(m_pOwner)->Get_CurFloor() == dynamic_cast<CAlive*>(pPlayer)->Get_CurFloor() )
		{
			if (!dynamic_cast<CPlayer*>(pPlayer)->IsSmoke() && eState != STATE_TYPE::RUN && eState != STATE_TYPE::ATTACK)
				dynamic_cast<CAlive*>(m_pOwner)->Run();
			else
				dynamic_cast<CMonster*>(m_pOwner)->Question();

		}
		break;*/

	case MOB_TYPE::GANGSTER:
		if (dynamic_cast<CAlive*>(m_pOwner)->Get_CurFloor() == dynamic_cast<CAlive*>(pPlayer)->Get_CurFloor() && eState != STATE_TYPE::ATTACK 
			&& !dynamic_cast<CPlayer*>(pPlayer)->IsSmoke())
			dynamic_cast<CAlive*>(m_pOwner)->Attack();

	}

}

void CSight::OnCollisionEnter(CCollider * _pOther)
{
	STATE_TYPE eState = dynamic_cast<CAlive*>(m_pOwner)->Get_State();
	MOB_TYPE mob_type = dynamic_cast<CMonster*>(m_pOwner)->Get_MobType();
	CObj* pPlayer = _pOther->Get_Obj()->Get_Owner();

	if (eState == STATE_TYPE::DEATH || eState == STATE_TYPE::HIT)
		return;

	switch (mob_type)
	{
	case MOB_TYPE::POMP:
	case MOB_TYPE::GRANT:
		if (STATE_TYPE::RUN != eState && STATE_TYPE::ATTACK != eState && STATE_TYPE::PARRING != eState)
			dynamic_cast<CAlive*>(m_pOwner)->Run();

		break;

	case MOB_TYPE::GANGSTER:
		if (dynamic_cast<CAlive*>(m_pOwner)->Get_CurFloor() != dynamic_cast<CAlive*>(pPlayer)->Get_CurFloor())
			return;
		dynamic_cast<CAlive*>(m_pOwner)->Attack();

	}
}

void CSight::OnCollisionExit(CCollider * _pOther)
{
	if (m_pOwner->Get_Owner() == nullptr)
		return;

	CObj* pPlayer = _pOther->Get_Obj()->Get_Owner();

	MOB_TYPE mob_type = dynamic_cast<CMonster*>(m_pOwner)->Get_MobType();
	STATE_TYPE eState = dynamic_cast<CAlive*>(m_pOwner)->Get_State();

	if (eState == STATE_TYPE::HIT || eState == STATE_TYPE::DEATH || eState == STATE_TYPE::PARRING)
		return;

	if (mob_type == MOB_TYPE::GANGSTER)
		dynamic_cast<CAlive*>(m_pOwner)->Run();

	if ((mob_type == MOB_TYPE::POMP || mob_type == MOB_TYPE::GRANT) &&  eState != STATE_TYPE::RUN && !dynamic_cast<CPlayer*>(pPlayer)->IsSmoke())
		dynamic_cast<CAlive*>(m_pOwner)->Run();

}

void CSight::Initialize()
{
	m_fOffset = m_pCollider->Get_Scale().x * 0.2f;
}

void CSight::Update()
{
	Vec2 vPos = m_pOwner->Get_Pos();

	vPos.x += m_fOffset * m_pOwner->Get_RenderDir().x;

	m_vPos = vPos;
}

void CSight::Render(HDC _dc)
{
	Component_Render(_dc);
}

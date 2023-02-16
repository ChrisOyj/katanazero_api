#include "stdafx.h"
#include "CHitBox.h"

#include "CCollider.h"

#include "CPlayer.h"
#include "CSlash.h"
#include "CMonster.h"
#include "CAlive.h"

#include "CEffects_BloodWall.h"
#include "CEffects_BulletReflect.h"
#include "CEffects_Impact.h"
#include "CEffects_Cut.h"
#include "CEffects_SlashHit.h"
#include "CAbstractFactory.h"

CHitBox::CHitBox()
{
	CreateCollider();

	float fWidth = 12.f;
	float fHeight = 30.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));
}

CHitBox::~CHitBox()
{
}

void CHitBox::Update()
{
	Vec2 vPos = Get_Owner()->Get_Pos();
	SetPos(vPos);
}

void CHitBox::Render(HDC _dc)
{
	Component_Render(_dc);
}

void CHitBox::OnCollision(CCollider * _pOther)
{
}

void CHitBox::OnCollisionEnter(CCollider * _pOther)
{
	STATE_TYPE eState = dynamic_cast<CAlive*>(m_pOwner)->Get_State();

	if (eState == STATE_TYPE::HIT || eState == STATE_TYPE::DEATH)
		return;


	CObj* pOtherObj = _pOther->Get_Obj();
	Vec2 vDir = Get_Dir();

	switch (pOtherObj->Get_ObjType())
	{
	case GROUP_TYPE::SUBATTACK:
		if (dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::HIT)
			return;

		if (dynamic_cast<CMonster*>(m_pOwner)->Get_MobType() == MOB_TYPE::BOSS && dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::ATTACK)
			return;
		{
		CObj* pPlayer;

		pPlayer = pOtherObj->Get_Owner(); // 플레이어

		//방향값 넣어주기
		Vec2 vDir;
		Vec2 vPos = Get_Owner()->Get_Pos();
		vDir = pOtherObj->Get_Dir();

		CAbstractFactory<CEffects_BloodWall>::Create_Effects(this, vPos, vDir, GROUP_TYPE::BLOOD);
		CAbstractFactory<CEffects_Cut>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);
		vPos.x += 100.f * vDir.x;
		vPos.y += 100.f * vDir.y;
		CAbstractFactory<CEffects_Impact>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);

		vPos = pOtherObj->Get_Pos();

		CAbstractFactory<CEffects_SlashHit>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);


		dynamic_cast<CAlive*>(Get_Owner())->Hit(vDir); // 몬스터
		//dynamic_cast<CMonster*>(Get_Owner())->LaserHit(); // 몬스터
		CCamera::Get_Instance()->SetVibrate();

		}
		break;

	case GROUP_TYPE::SLASH: // 몬스터가 슬래시에 닿았을 때
		if (dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::HIT)
			return;

		{
		if ((dynamic_cast<CMonster*>(m_pOwner)->Get_MobType() == MOB_TYPE::POMP || dynamic_cast<CMonster*>(m_pOwner)->Get_MobType() == MOB_TYPE::BOSS)
			&& (dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::ATTACK || dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::SKILL))
		{
			dynamic_cast<CAlive*>(m_pOwner)->Parring(pOtherObj->Get_Owner());
			dynamic_cast<CAlive*>(pOtherObj->Get_Owner())->Parring(m_pOwner);
			CAbstractFactory<CEffects_BulletReflect>::Create_Effects(this, m_vPos, m_vDir, GROUP_TYPE::EFFECTS);
			return;
		}

		CObj* pPlayer;

		pPlayer = pOtherObj->Get_Owner(); // 플레이어

		//방향값 넣어주기
		Vec2 vDir;
		Vec2 vPos = Get_Owner()->Get_Pos();
		vDir = pOtherObj->Get_Dir();

		CAbstractFactory<CEffects_BloodWall>::Create_Effects(this, vPos, vDir, GROUP_TYPE::BLOOD);
		CAbstractFactory<CEffects_Cut>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);
		vPos.x += 100.f * vDir.x;
		vPos.y += 100.f * vDir.y;
		CAbstractFactory<CEffects_Impact>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);

		vPos = pOtherObj->Get_Pos();

		CAbstractFactory<CEffects_SlashHit>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);

		if (g_bLaser)
			dynamic_cast<CMonster*>(Get_Owner())->LaserHit(); // 몬스터
		else
			dynamic_cast<CAlive*>(Get_Owner())->Hit(vDir); // 몬스터

		CCamera::Get_Instance()->SetVibrate();

		}
		break;

	case GROUP_TYPE::MONSTER_ATTACK:
		if (dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::HIT)
			return;
	{
		Get_Owner(); // 플레이어
		CObj* pMonster = pOtherObj->Get_Owner(); // 몬스터

		if ((dynamic_cast<CMonster*>(pMonster)->Get_MobType() == MOB_TYPE::POMP || dynamic_cast<CMonster*>(pMonster)->Get_MobType() == MOB_TYPE::BOSS)
			&& dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::ATTACK)
		{
			dynamic_cast<CAlive*>(m_pOwner)->Parring(pOtherObj->Get_Owner());
			dynamic_cast<CAlive*>(pOtherObj->Get_Owner())->Parring(m_pOwner);
			CAbstractFactory<CEffects_BulletReflect>::Create_Effects(this, m_vPos, m_vDir, GROUP_TYPE::EFFECTS);
			return;
		}


		//방향값 넣어주기
		Vec2 vDir;
		Vec2 vPlayerPos = Get_Owner()->Get_Pos();
		Vec2 vMonsterPos = pMonster->Get_Pos();
		vDir = vPlayerPos - vMonsterPos;
		vDir.Normalize();

		CAbstractFactory<CEffects_SlashHit>::Create_Effects(this, vPlayerPos, vDir, GROUP_TYPE::EFFECTS);

		CCamera::Get_Instance()->SetVibrate();


		dynamic_cast<CAlive*>(Get_Owner())->Hit(vDir); // 플레이어

	}
	break;

	case GROUP_TYPE::MOBSUBATTACK:
		if (dynamic_cast<CAlive*>(m_pOwner)->Get_State() == STATE_TYPE::HIT)
			return;
		{
			Get_Owner(); // 플레이어
			CObj* pMonster = pOtherObj->Get_Owner(); // 몬스터


			//방향값 넣어주기
			Vec2 vDir;
			Vec2 vPlayerPos = Get_Owner()->Get_Pos();
			Vec2 vMonsterPos = pMonster->Get_Pos();
			vDir = vPlayerPos - vMonsterPos;
			vDir.Normalize();

			CAbstractFactory<CEffects_SlashHit>::Create_Effects(this, vPlayerPos, vDir, GROUP_TYPE::EFFECTS);

			CCamera::Get_Instance()->SetVibrate();


			dynamic_cast<CAlive*>(Get_Owner())->Hit(vDir); // 플레이어

		}
		break;


	case GROUP_TYPE::SMOKE:
	{
		/*ColorMatrix cm = {
		   0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 0.6f, 0.0f,
		   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		m_pOwner->SetColorMatrix(cm);*/

	}

		break;
	}

}

void CHitBox::OnCollisionExit(CCollider * _pOther)
{
}


//void CHitBox::CreateEffects(EFFECT_TYPE _eType, Vec2 _vDir, Vec2 _vPos)
//{
//	CEffects* pEffects = new CEffects;
//	Vec2 vEffectsPos = _vPos;
//
//
//	switch (_eType)
//	{
//	case EFFECT_TYPE::IMPACT:
//		pEffects->SetRenderDir(Get_Owner()->Get_RenderDir());
//		pEffects->SetEffectType(EFFECT_TYPE::IMPACT);
//		vEffectsPos.x += 30.f * _vDir.x;
//		vEffectsPos.y += 30.f * _vDir.y;
//		pEffects->SetSpeed(90.f);
//		break;
//
//	case EFFECT_TYPE::CUT:
//		pEffects->SetEffectType(EFFECT_TYPE::CUT);
//		vEffectsPos.x += 30.f * _vDir.x;
//		vEffectsPos.y += 30.f * _vDir.y;
//		pEffects->SetSpeed(90.f);
//		pEffects->SetDir(Vec2(1.f, 0.f));
//		pEffects->SetPos(vEffectsPos);
//		pEffects->Initialize();
//		CreateObject(pEffects, GROUP_TYPE::EFFECTS);
//		return;
//
//	case EFFECT_TYPE::SLASH:
//		pEffects->SetRenderDir(Get_Owner()->Get_RenderDir());
//		pEffects->SetEffectType(EFFECT_TYPE::SLASH);
//		pEffects->SetSpeed(2000.f);
//
//		break;
//
//	case EFFECT_TYPE::BLOODWALL:
//		pEffects->SetRenderDir(Get_Owner()->Get_RenderDir());
//		pEffects->SetEffectType(EFFECT_TYPE::BLOODWALL);
//		vEffectsPos.x += 90.f * _vDir.x;
//		vEffectsPos.y += 90.f * _vDir.y;
//		pEffects->SetDir(_vDir);
//		pEffects->SetPos(vEffectsPos);
//		pEffects->Initialize();
//		CreateObject(pEffects, GROUP_TYPE::BLOOD);
//
//
//		return;
//
//	}
//
//	pEffects->SetDir(_vDir);
//	pEffects->SetPos(vEffectsPos);
//	pEffects->Initialize();
//	CreateObject(pEffects, GROUP_TYPE::EFFECTS);
//}

#include "stdafx.h"
#include "CPortal.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CAbstractFactory.h"
#include "CEffects_Go.h"

#include "CKeyMgr.h"

CPortal::CPortal()
	: m_bClear(false)
	, m_bChange(false)
{
	

}

CPortal::~CPortal()
{
}

void CPortal::OnCollision(CCollider * _pOther)
{
	if (m_bClear && _pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::PLAYER)
	{
		if (!m_bChange && m_fAcc == 0.f)
		{
			m_bChange = true;
			m_fAcc += 1.f;
			CSceneMgr::Get_Instance()->SceneChange(false);
		}
		SetCollision(false);
	}
}

void CPortal::Initialize()
{
	CreateCollider();
	m_pCollider->SetScale(Vec2(30.f, 200.f));
}

void CPortal::Update()
{
	if (KEY(F1, TAP))
	{
		m_bChange = true;
		CSceneMgr::Get_Instance()->SceneChange(false);

	}

	if (!m_bClear && CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::MONSTER_SIGHT).empty())
	{
		m_bClear = true;
		Vec2 vPos = m_vPos;
		vPos.x -= 30.f;
		vPos.y -= 20.f;
		CAbstractFactory<CEffects_Go>::Create_Effects(vPos, GROUP_TYPE::UI);
		CSoundMgr::Get_Instance()->PlaySound(L"Clear.wav");

		if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::STAGE_02)
		{
			SetImage();

		}
	}

	if (m_bChange)
	{
		m_fTime += RealfDT;
		if (0.6f < m_fTime)
		{
			m_fTime = 0.f;
			m_bChange = false;
			UINT curScene = (UINT)CSceneMgr::Get_Instance()->Get_CurSceneType();
			curScene++;
			ChangeScene(SCENE_TYPE(curScene));
		}
	}
}

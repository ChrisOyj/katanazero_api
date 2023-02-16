#include "stdafx.h"
#include "CEventMgr.h"

#include "CObj.h"
#include "CSceneMgr.h"
#include "CScene.h"


CEventMgr::CEventMgr()
{}

CEventMgr::~CEventMgr()
{}

void CEventMgr::Update()
{
	if (CSceneMgr::Get_Instance()->IsReplay())
	{
		return;
	}
	// ================================================
	// ���� �����ӿ� ����ص� Dead Object���� ���� ��Ų��.
	// ================================================

	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		if (nullptr != m_vecDead[i])
			delete m_vecDead[i];
	}
	m_vecDead.clear();

	// ==========
	// Event ó��
	// ==========
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear(); // �̺�Ʈ �ϴ� �����



}

void CEventMgr::Excute(const tEvent & _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		// lParam : Object Adress
		// wParam : Group Type

	{
		CObj* pNewObj = (CObj*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::Get_Instance()->Get_CurScene()->AddObject(pNewObj, eType);
	}

	break;

	case EVENT_TYPE::DELETE_OBJECT:
		//Object�� dead ���·� ����
	{
		CObj* pDeadObj = (CObj*)_eve.lParam;

		pDeadObj->SetDead();

		for (size_t i = 0; i < m_vecDead.size(); ++i)
		{
			if (m_vecDead[i] == pDeadObj)
				return;
		}

		m_vecDead.push_back(pDeadObj);

	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : Next Scene Type
	{
		m_vecDead.clear();
		CSceneMgr::Get_Instance()->ChangeScene((SCENE_TYPE)_eve.lParam);
	}

	break;
	}
}

#include "stdafx.h"
#include "CScene.h"

#include "CObj.h"
#include "CKeyMgr.h"

#include "CAlive.h"
#include "CLineMgr.h"

CScene::CScene()
	: m_bColliderVisible(false)
{
}

CScene::~CScene()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];
		}
	}
}
void CScene::Update()
{

	if (KEY(TAB, TAP))
	{
		m_bColliderVisible = !m_bColliderVisible;
	}


	for (int i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{

			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Update();
			}

			if (m_bColliderVisible)
				m_arrObj[i][j]->SetColliderVisible(true);
			else
				m_arrObj[i][j]->SetColliderVisible(false);


			
		}
	}
}

void CScene::Final_Update()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->Final_Update();
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObj*>::iterator iter = m_arrObj[i].begin(); // 오브젝트가 죽은 상태면 배열에서 빼주기 위해 이터레이터로 돌림

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}

	if (m_bColliderVisible)
	Debuger_Render(_dc);
}

void CScene::AddObject(CObj * _pObj, GROUP_TYPE _eType)
{
	m_arrObj[(UINT)_eType].push_back(_pObj);
}

void CScene::DeleteGroup(GROUP_TYPE _eType)
{
	//Safe_Delete_Vec<CObj*>(m_arrObj[(UINT)_eType]); // 함수 템플릿
	for (size_t i = 0; i < m_arrObj[(UINT)_eType].size(); ++i)
	{
		if (nullptr != m_arrObj[(UINT)_eType][i])
			delete m_arrObj[(UINT)_eType][i];
	}
	m_arrObj[(UINT)_eType].clear();
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::DeleteEventAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			DeleteObject(m_arrObj[i][j]);
		}
		m_arrObj[i].clear();
	}
}

void CScene::Debuger_Render(HDC _dc)
{
	// 라인매니져
	CLineMgr::Get_Instance()->Render(_dc);

	//폰트
	SetTextColor(_dc, RGB(0, 200, 255));

	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));
	SelectObject(_dc, hFont);
	DeleteObject(hFont);

	CObj*		pPlayer = m_arrObj[(UINT)GROUP_TYPE::PLAYER].front();
	TCHAR szBuff[64];
	Vec2 vLook = CCamera::Get_Instance()->Get_LookAt();
	Vec2 vPos = pPlayer->Get_Pos();
	Vec2 vMousePos = Get_MousePos();
	Vec2 vRealPos = CCamera::Get_Instance()->Get_RealPos(vMousePos);
	Vec2 vDiff = vRealPos - vMousePos;
	Vec2 vDir = vRealPos - vPos;
	vDir.Normalize();
	Vec2 vDia = vRealPos - vPos;
	float fXSpeed = dynamic_cast<CAlive*>(pPlayer)->Get_Physics().fXSpeed;
	float fTime = pPlayer->Get_Time();

	swprintf_s(szBuff, L"캐릭터 x,y : (%d, %d)", (int)vPos.x, (int)vPos.y);
	TextOut(_dc, 10, 30, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"Speed : %f", fXSpeed);
	TextOut(_dc, 10, 45, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"vDir : (%f, %f)", vDir.x, vDir.y);
	TextOut(_dc, 10, 60, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"vLookAt : (%d, %d)", (int)vLook.x, (int)vLook.y);
	TextOut(_dc, 10, 75, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"bFalling : %d", dynamic_cast<CAlive*>(pPlayer)->Get_Physics().bFalling);
	TextOut(_dc, 10, 90, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"화면 상 x,y : (%d, %d)", (int)vMousePos.x, (int)vMousePos.y);
	TextOut(_dc, (int)vMousePos.x, (int)vMousePos.y, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"실제 x,y : (%d, %d)", (int)vRealPos.x, (int)vRealPos.y);
	TextOut(_dc, (int)vMousePos.x, (int)vMousePos.y + 20, szBuff, lstrlen(szBuff));

}


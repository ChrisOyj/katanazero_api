#include "stdafx.h"
#include "CLineMgr.h"

#include "CAlive.h"
#include "CCollider.h"
#include "CSceneMgr.h"


CLineMgr::CLineMgr()
	: m_iCurFloor(0)
	, m_pPlayer(nullptr)
	, m_bEditMode(false)
	//, m_bCol(false)
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

Vec2 CLineMgr::Get_StairPos(int _iCurFloor, int _iTargetFloor)
{
	LINEINFO TargetInfo;

	if (_iCurFloor < _iTargetFloor) // 목표가 더 높은 층일 때
	{
		for (size_t i = 0; i < m_arrLine[_iCurFloor].size(); ++i)
		{
			TargetInfo = m_arrLine[_iCurFloor][i]->Get_Info();

			if (TargetInfo.bStair)
				break;
		}

		if (TargetInfo.vLeftPoint.y + 10.f < TargetInfo.vRightPoint.y) // 왼쪽이 더 높이 있다면
			return TargetInfo.vLeftPoint;
		else
			return TargetInfo.vRightPoint;
	}
	else // 목표가 더 낮은 층일 때
	{
		for (size_t i = 0; i < m_arrLine[_iCurFloor-1].size(); ++i) // 한 층 아래를 조사
		{
			TargetInfo = m_arrLine[_iCurFloor-1][i]->Get_Info();

			if (TargetInfo.bStair)
				break;
		}

		if (TargetInfo.vLeftPoint.y + 10.f < TargetInfo.vRightPoint.y) // 왼쪽이 더 높이 있다면
			return TargetInfo.vLeftPoint;
		else
			return TargetInfo.vRightPoint;
	}
}

bool CLineMgr::Get_Open(Vec2& vPos, float fOffset)
{
	int iCurFloor = 0;
	CLine* pTargetLine = nullptr;

	for (size_t i = 0; i < m_arrLine.size(); ++i)
	{
		for (size_t j = 0; j < m_arrLine[i].size(); ++j)
		{
			if (vPos.y + fOffset <= m_arrLine[i][0]->Get_Info().vRightPoint.y + 5.f)
				iCurFloor = (int)i;
		}
	}

	// 2. 그 층에서 타겟 라인 찾기
	for (auto& iter : m_arrLine[iCurFloor])
	{
		if (vPos.x >= iter->Get_Info().vLeftPoint.x &&
			vPos.x <= iter->Get_Info().vRightPoint.x)
		{
			pTargetLine = iter;
		}
	}

	if (!pTargetLine)
	{
		return false;
	}

	return pTargetLine->Get_Info().bOpen;



}

void CLineMgr::Initialize(void)
{
	vector<CLine*> vecLine;
	m_arrLine.push_back(vecLine);

	////Load_Line(1);
	//
	//vector<CLine*> vecLine;

	///*Vec2 FirstFloor[4] = {
	//	{ 0.f, 400.f},
	//	{ 700.f, 400.f },
	//	{ 300.f, 300.f },
	//	{ 600.f, 300.f }

	//};

	//vecLine.push_back(new CLine(FirstFloor[0], FirstFloor[1], false, false));
	//vecLine.push_back(new CLine(FirstFloor[2], FirstFloor[3], false, true));
	//m_arrLine.push_back(vecLine);*/

	//Vec2 FirstFloor[3] = {
	//	{ 0.f, 295.f},
	//	{ 100.f, 400.f },
	//	{ 1000.f, 400.f }
	//};

	//Vec2 SecondFloor[4] = {
	//	{ 0.f, 300.f},
	//	{ 100.f, 300.f },
	//	{ 900.f, 300.f},
	//	{ 1000.f, 195.f}
	//};

	//Vec2 ThirdFloor[3] = {
	//	{ 0.f, 200.f },
	//	{ 800.f, 200.f},
	//	{ 1000.f, 200.f}

	//};

	//vecLine.push_back(new CLine(FirstFloor[0], FirstFloor[1], true, false));
	//vecLine.push_back(new CLine(FirstFloor[1], FirstFloor[2], false, false));

	//m_arrLine.push_back(vecLine);
	//vecLine.clear();

	//vecLine.push_back(new CLine(SecondFloor[0], SecondFloor[1], false, true));
	//vecLine.push_back(new CLine(SecondFloor[1], SecondFloor[2], false, false));
	//vecLine.push_back(new CLine(SecondFloor[2], SecondFloor[3], true, false));
	//m_arrLine.push_back(vecLine);
	//vecLine.clear();

	//vecLine.push_back(new CLine(ThirdFloor[0], ThirdFloor[1], false, false));
	//vecLine.push_back(new CLine(ThirdFloor[1], ThirdFloor[2], false, true));

	//m_arrLine.push_back(vecLine);
	//vecLine.clear();
}

void CLineMgr::Update()
{

	//플레이어의 현재 플로어 갱신
	if (CSceneMgr::Get_Instance()->IsReplay())
	{
		return;
	}

	if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::MAINMENU)
		return;

	if (m_pPlayer)
	{
		if (dynamic_cast<CAlive*>(m_pPlayer)->Get_State() == STATE_TYPE::DEATH)
		{
			m_pPlayer = nullptr;
			return;
		}

		Vec2 vPos = m_pPlayer->Get_Pos();
		vPos.y += m_pPlayer->Get_Collider()->Get_OffSetPos().y;

		for (size_t i = 0; i < m_arrLine.size(); ++i)
		{
			if (vPos.y <= m_arrLine[i][0]->Get_Info().vRightPoint.y + 10.f)
				m_iCurFloor = (int)i;
		}

		CLine* pTargetLine = nullptr;

		// 캐릭터가 계단에 있는지
		for (auto& iter : m_arrLine[m_iCurFloor])
		{
			if (vPos.x >= iter->Get_Info().vLeftPoint.x &&
				vPos.x <= iter->Get_Info().vRightPoint.x)
			{
				pTargetLine = iter;
			}
		}

		if (!pTargetLine)
		{
			return;
		}

		m_bStair = pTargetLine->Get_Info().bStair;


	}
}

void CLineMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < m_arrLine.size(); ++i)
	{
		for (size_t j = 0; j < m_arrLine[i].size(); ++j)
			m_arrLine[i][j]->Render(hDC);
	}
}

void CLineMgr::Release(void)
{
	for (size_t i = 0; i < m_arrLine.size(); ++i)
	{
		Safe_Delete_Vec(m_arrLine[i]);
		m_arrLine[i].clear();
	}
	m_arrLine.clear();

}

bool CLineMgr::Collision_Line(Vec2& vPos, float fOffsetY, float* pY, bool* pStair, int* iFloor)
{
	if (m_arrLine.empty())
	{
		return false;
	}
	
	CLine* pTargetLine = nullptr;
	int iCurFloor = 0;

	//1. 층 찾기
	for (size_t i = 0; i < m_arrLine.size(); ++i)
	{
		for (size_t j = 0; j < m_arrLine[i].size(); ++j)
		{
			if (vPos.y + fOffsetY <= m_arrLine[i][0]->Get_Info().vRightPoint.y + 10.f )
				iCurFloor = (int)i;
		}
		
	}

	*iFloor = iCurFloor;

	// 2. 그 층에서 타겟 라인 찾기
	for (auto& iter : m_arrLine[iCurFloor])
	{
		if (vPos.x >= iter->Get_Info().vLeftPoint.x &&
			vPos.x <= iter->Get_Info().vRightPoint.x)
		{
			pTargetLine = iter;
		}
	}

	if (!pTargetLine)
	{
		return false;
	}

	float fX1 = pTargetLine->Get_Info().vLeftPoint.x;
	float fX2 = pTargetLine->Get_Info().vRightPoint.x;
	float fY1 = pTargetLine->Get_Info().vLeftPoint.y;
	float fY2 = pTargetLine->Get_Info().vRightPoint.y;

	float fLineY = ((fY2 - fY1) / (fX2 - fX1)) * (vPos.x - fX1) + fY1;

	if (fLineY-1.f <= vPos.y + fOffsetY)
	{
		*pY = fLineY - fOffsetY;
		*pStair = pTargetLine->Get_Info().bStair;
		pTargetLine->Set_Col(true);
		return true;
	}

	*pStair = pTargetLine->Get_Info().bStair;

	Line_ColFalse();
	return false;
	

}

void CLineMgr::Add_Line(CLine * pLine, int iFloor)
{
	if (m_arrLine.size() == iFloor)
	{
		vector<CLine*> vec;
		m_arrLine.push_back(vec);
	}
	m_arrLine[iFloor].push_back(pLine);
}


void CLineMgr::Line_ColFalse()
{
	for (size_t i = 0; i < m_arrLine.size(); ++i)
	{
		for (size_t j = 0; j < m_arrLine[i].size(); ++j)
			m_arrLine[i][j]->Set_Col(false);
	}
}

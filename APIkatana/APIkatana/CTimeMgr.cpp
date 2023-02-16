#include "stdafx.h"
#include "CTimeMgr.h"

#include "CKeyMgr.h"
#include "CAbstractFactory.h"
#include "CMenu.h"
#include "CSceneMgr.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0)
	, m_iCallCount(0)
	, m_fTimeSpeed(1.f)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Initialize()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency); // 1초당 카운트가 얼마나 발생하는 지 구하는 함수


}

void CTimeMgr::Update()
{
	


	QueryPerformanceCounter(&m_llCurCount);

	// 아까잰거랑 지금 잰거랑 계속 비교하면서 차이가 나옴
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount;


#ifdef _DEBUG // 디버그 모드일 때만 작동하게 코드 작성
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);

#endif
	if (KEY(ESC, TAP))
	{
		if ((UINT)CSceneMgr::Get_Instance()->Get_CurSceneType() < (UINT)SCENE_TYPE::START)
			return;

		if (m_fTimeSpeed == 1.f)
		{
			m_fTimeSpeed = 0.f;
			CreateObject(CAbstractFactory<CMenu>::Create(), GROUP_TYPE::UI);
		}
		else
			m_fTimeSpeed = 1.f;
	}
}

void CTimeMgr::Render()
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT가 dAcc에 누적되는 중

	if (1 <= m_dAcc) { // 1초가 지난 시점

		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"Katana ZERO                                                                 FPS : %d,  DT : %f", m_iFPS, m_dDT);
		SetWindowText(g_hwnd, szBuffer);

	}
}

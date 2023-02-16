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
	QueryPerformanceFrequency(&m_llFrequency); // 1�ʴ� ī��Ʈ�� �󸶳� �߻��ϴ� �� ���ϴ� �Լ�


}

void CTimeMgr::Update()
{
	


	QueryPerformanceCounter(&m_llCurCount);

	// �Ʊ���Ŷ� ���� ��Ŷ� ��� ���ϸ鼭 ���̰� ����
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount;


#ifdef _DEBUG // ����� ����� ���� �۵��ϰ� �ڵ� �ۼ�
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
	m_dAcc += m_dDT; // DT�� dAcc�� �����Ǵ� ��

	if (1 <= m_dAcc) { // 1�ʰ� ���� ����

		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"Katana ZERO                                                                 FPS : %d,  DT : %f", m_iFPS, m_dDT);
		SetWindowText(g_hwnd, szBuffer);

	}
}

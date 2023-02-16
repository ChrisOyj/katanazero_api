#include "stdafx.h"
#include "CCamera.h"

#include "CObj.h"
#include "CMainGame.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CLineMgr.h"

#include "CEffects_DarkScreen.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"

#include "CScene.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fVibSpeed(2000.f)
	, m_fMaxVibSpeed(2000.f)
	, m_vLookAt{}
	, m_iCount(1)
	, m_bVibrate(false)
	, m_fTime(0.f)
	, m_fCurZoom(1.f)
	, m_fTargetZoom(1.f)

{}

CCamera::~CCamera()
{}


void CCamera::Update()
{
	if (m_bEdit)
		Update_Edit();

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 0.f)
		return;

	//=========================================================
	if (g_bCinema && CSceneMgr::Get_Instance()->Get_CurSceneType() != SCENE_TYPE::STAGE_03)
	{
		if (m_fTargetZoom == ZOOM)
		{
			m_fTime += RealfDT;

			CTimeMgr::Get_Instance()->SetTimeSpeed(0.3f);

			if (m_fTime > 0.8f)
			{
				m_fTargetZoom = 1.f;
				m_fTime = 0.f;
				CTimeMgr::Get_Instance()->SetTimeSpeed(1.f);
				m_pTargetObj = CSceneMgr::Get_Instance()->Get_CurScene()->Get_Player();

			}
		}
	}


	if (m_fCurZoom <= m_fTargetZoom + 0.01f && m_fCurZoom >= m_fTargetZoom - 0.01f)
	{
		m_fCurZoom = m_fTargetZoom;
	}
	else
	{
		m_fZoomSpeed = (m_fTargetZoom - m_fCurZoom) * 0.08f;

		m_fCurZoom += m_fZoomSpeed;
	}

	if (m_fCurZoom == 0.5f)
		m_bZoom = false;

	
	//=========================================================
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
			m_pTargetObj = nullptr;
		else
			Physics_Update();
	}

	if (m_bVibrate)
	{
		Vibrate_Update();
	}

	//ȭ�� �߾���ǥ�� ī�޶� Lookat ���� ���̸� ���
	CalDiff();


}
void CCamera::Update_Edit()
{
	if (KEY(W, HOLD))
	{
		m_vLookAt.y -= 300.f * RealfDT;
	}
	if (KEY(A, HOLD))
	{
		m_vLookAt.x -= 300.f * RealfDT;
	}
	if (KEY(S, HOLD))
	{
		m_vLookAt.y += 300.f * RealfDT;
	}
	if (KEY(D, HOLD))
	{
		m_vLookAt.x += 300.f * RealfDT;
	}
}




void CCamera::Physics_Update()
{
	Vec2 vPos = m_pTargetObj->Get_Pos();

	if (m_fCurZoom != ZOOM && m_fCurZoom != 1.0f && !m_bZoom) // �� off �ǰ� ��
	{
		Vec2 vMaxLT;
		Vec2 vMaxRB;

		vMaxLT.x = CLineMgr::Get_Instance()->Get_vecLine().front().front()->Get_Info().vLeftPoint.x + (float)WINCX*0.5f;
		vMaxLT.y = CLineMgr::Get_Instance()->Get_vecLine().back().front()->Get_Info().vRightPoint.y + (float)WINCY*0.1f;

		vMaxRB.x = CLineMgr::Get_Instance()->Get_vecLine().back().back()->Get_Info().vRightPoint.x - (float)WINCX*0.5f;
		vMaxRB.y = CLineMgr::Get_Instance()->Get_vecLine().front().front()->Get_Info().vRightPoint.y - (float)WINCY*0.4f;

		if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::STAGE_03)
			vMaxRB.y = (WINCY / 2.f);

		if (m_vLookAt.x <= vMaxLT.x)
			vPos.x = vMaxLT.x;

		if (m_vLookAt.x >= vMaxRB.x)
			vPos.x = vMaxRB.x;

		if (m_vLookAt.y <= vMaxLT.y)
			vPos.y = vMaxLT.y;

		if (m_vLookAt.y >= vMaxRB.y)
			vPos.y = vMaxRB.y;
	}

	float TargetY = vPos.y;


	//x ��ǥ�� ������ �÷��̾� �Ѿư�
	if (m_vLookAt.x <= vPos.x + 0.01f && m_vLookAt.x >= vPos.x - 0.01f)
	{
		m_vLookAt.x = vPos.x;
	}
	else
	{
		m_fSpeed = (vPos.x - m_vLookAt.x) * 0.07f;

		m_vLookAt.x += m_fSpeed;
	}

	if (m_fCurZoom == 1.0f) // �� off�� Ÿ�� y ����
	{
		if (CLineMgr::Get_Instance()->Get_Stair())
			TargetY = vPos.y;
		else
			TargetY = CLineMgr::Get_Instance()->Get_CurFloorY();
	}

	//y ��ǥ�� Ÿ��Y�� ����
	if (m_vLookAt.y <= TargetY + 0.01f && m_vLookAt.y >= TargetY - 0.01f)
	{
		m_vLookAt.y = TargetY;
	}
	else
	{
		m_fSpeed = (TargetY - m_vLookAt.y) * 0.07f;

		m_vLookAt.y += m_fSpeed;
	}

	

	if (m_fCurZoom == 1.0f) // �� off
	{
		Vec2 vMousePos = Get_MousePos();
		Vec2 vCenter = { float(WINCX / 2), float(WINCY / 2) };

		m_vLookAt.x += (vMousePos.x - vCenter.x) * 0.012f;
		m_vLookAt.y += (vMousePos.y - vCenter.y) * 0.008f;

		Screen_Update();
	}
	
}

void CCamera::CalDiff()
{
	Vec2 vCenter = { float(WINCX / 2), float(WINCY / 2) };
	m_vDiff = m_vLookAt - vCenter;
}

void CCamera::CreateDarkScreen()
{
	CAbstractFactory<CEffects_DarkScreen>::Create_Effects(m_vLookAt, GROUP_TYPE::DARKSCREEN);
}

void CCamera::Vibrate_Update()
{
	//m_fTime += RealfDT;

	//if (0.25f < m_fTime)
	//{
	//	m_bVibrate = false;
	//	//m_vLookAt = m_vPrevLook;
	//	m_fTime = 0.f;
	//	m_fVibSpeed = m_fMaxVibSpeed;
	//	m_iCount = 1;
	//	return;
	//}

	if (10.f > fabs(m_fVibSpeed))
	{
		m_bVibrate = false;
		//m_vLookAt = m_vPrevLook;
		m_fVibSpeed = m_fMaxVibSpeed;
		m_iCount = 1;
		return;
	}

	if (m_iCount == 1) // ���� ��ȯ ī��Ʈ
	{
		m_fVibSpeed *= 0.8f;
	}

	if (m_iCount == 2)
	{
		m_fVibSpeed *= -1.f;
		m_iCount = 0;
	}

	m_vLookAt.x += m_fVibSpeed * RealfDT;
	m_vLookAt.y -= m_fVibSpeed * RealfDT;

	m_iCount++;

}

void CCamera::ZoomSet(HDC _dc)
{
	HDC hDC = CMainGame::Get_Instance()->Get_MainDC();
	HDC hZoomDC(0);
	HBITMAP hZoomBit;
	HBITMAP hOldBit;

	hZoomDC = CreateCompatibleDC(hDC);

	hZoomBit = CreateCompatibleBitmap(hDC, WINCX, WINCY);
	hOldBit = (HBITMAP)SelectObject(hZoomDC, hZoomBit);
	DeleteObject(hOldBit);

	BitBlt(hZoomDC, 0, 0, WINCX, WINCY
		, _dc, 0, 0, SRCCOPY);

	/*float	fPower = 50.f;
	m_fTheta += 10.f * fDT;
	float fsin = sinf(m_fTheta);


	int iRand = random(0, 1);
	if (iRand == 1)
		fsin = cosf(m_fTheta);

	POINT  m_tPoint[3] = {};

	m_tPoint[0].x = (LONG)(100);
	m_tPoint[0].y = (LONG)(fPower * fsin);

	m_tPoint[1].x = (LONG)(WINCX);
	m_tPoint[1].y = (LONG)(-fPower * fsin);

	m_tPoint[2].x = (LONG)(0);
	m_tPoint[2].y = (LONG)(WINCY) + (LONG)(fPower * fsin);*/

	POINT  m_tPoint[3] = {};

	m_tPoint[0].x = (LONG)(0);
	m_tPoint[0].y = (LONG)(0);

	m_tPoint[1].x = (LONG)(WINCX);
	m_tPoint[1].y = (LONG)(0);

	m_tPoint[2].x = (LONG)(0);
	m_tPoint[2].y = (LONG)(WINCY);

	

	// ������ 2����

	float left, top, width, height;
	
	width = float(WINCX) * m_fCurZoom;
	height = float(WINCY) * m_fCurZoom;
	left = float (WINCX) * 0.5f - width * 0.5f;
	top = float(WINCY) * 0.5f - height * 0.5f;



	PlgBlt(_dc
		, m_tPoint
		, hZoomDC
		, (int)left
		, (int)top
		, (int)width
		, (int)height
		, NULL
		, NULL
		, NULL
	);

	DeleteObject(hZoomBit);
	DeleteDC(hZoomDC);

}

void CCamera::Screen_Update()
{

	Vec2 vMaxLT;
	Vec2 vMaxRB;

	vMaxLT.x = CLineMgr::Get_Instance()->Get_vecLine().front().front()->Get_Info().vLeftPoint.x + (float)WINCX*0.5f;
	vMaxLT.y = CLineMgr::Get_Instance()->Get_vecLine().back().front()->Get_Info().vRightPoint.y + (float)WINCY*0.1f;

	vMaxRB.x = CLineMgr::Get_Instance()->Get_vecLine().back().back()->Get_Info().vRightPoint.x - (float)WINCX*0.5f;
	vMaxRB.y = CLineMgr::Get_Instance()->Get_vecLine().front().front()->Get_Info().vRightPoint.y - (float)WINCY*0.4f;

	if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::STAGE_03)
		vMaxRB.y = (WINCY / 2.f);

	if (m_vLookAt.x <= vMaxLT.x)
		m_vLookAt.x = vMaxLT.x;

	if (m_vLookAt.x >= vMaxRB.x)
		m_vLookAt.x = vMaxRB.x;

	if (m_vLookAt.y <= vMaxLT.y)
		m_vLookAt.y = vMaxLT.y;

	if (m_vLookAt.y >= vMaxRB.y)
		m_vLookAt.y = vMaxRB.y;
}

#include "stdafx.h"
#include "CSceneMgr.h"

#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CSoundMgr.h"
#include "CEditor.h"

#include "CSceneChange.h"

#include "CScene_Start.h"
#include "CScene_MainMenu.h"
#include "CScene_Edit.h"
#include "CScene_Stage2.h"
#include "CScene_Stage3.h"
#include "CScene_Boss.h"

#include "CPlayer.h"



CSceneMgr::CSceneMgr()
	:m_arrScene{}
	, m_pCurScene(nullptr)
	, m_bReplay(false)
	, m_fTime(0.f)
	, m_bReplaysave(false)

{}
CSceneMgr::~CSceneMgr() {
	//씬 전부 삭제
	for (int i = 0; i < (UINT)SCENE_TYPE::END; ++i) {
		if (m_arrScene[i])
			delete m_arrScene[i];
	}

	for (size_t i = 0; i < m_vecvecReplay.size(); ++i)
	{
		Safe_Delete_Vec(m_vecvecReplay[i]);

		/*for (size_t j = 0; j < m_vecvecReplay[i].size(); ++j)
		{
			delete m_vecvecReplay[i][j];
		}*/
	}
}


void CSceneMgr::Initialize() {

	//씬 생성
	m_arrScene[(UINT)SCENE_TYPE::MAINMENU] = new CScene_MainMenu;
	m_arrScene[(UINT)SCENE_TYPE::MAINMENU]->SetName(L"Main Menu");

	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage2;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetName(L"Stage1");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage3;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02]->SetName(L"Stage2");

	m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new CScene_Boss;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_03]->SetName(L"Stage3");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Edit;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Edit Scene");
	//현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::MAINMENU];
	m_pCurScene->Enter(false);
	m_eCurScene = SCENE_TYPE::MAINMENU;
}

void CSceneMgr::Update()
{
	if (m_bReplay)
	{
		if (KEY(LBUTTON, TAP) || KEY(RBUTTON, TAP))
		{
			Replay_over();
		}


		return;
	}
	else
	{
		if (m_pCurScene != m_arrScene[(UINT)SCENE_TYPE::MAINMENU] && m_pCurScene != m_arrScene[(UINT)SCENE_TYPE::TOOL])
		{
			if (KEY(R, TAP) || m_bDragonReplay)
			{
				Replay();
			}

			m_fTime += fDT;

			m_bReplaysave = false;

			if (0.02f < m_fTime)
			{
				m_bReplaysave = true;
				m_fTime = 0.f;
			}
		}
		


		m_pCurScene->Update();

		m_pCurScene->Final_Update();
	}

	

}

void CSceneMgr::Render(HDC _dc)
{
	if (m_bReplay)
	{
		Replay_Render(_dc);
		return;
	}
	else
	{
		m_pCurScene->Render(_dc);

		if (!m_vecReplay.empty())
		{
			m_vecvecReplay.push_back(m_vecReplay);
			m_vecReplay.clear();
		}
		

	}

}

void CSceneMgr::AddReplay(ReplayInfo * _Info)
{
	m_vecReplay.push_back(_Info);
}

void CSceneMgr::DragonReplay()
{
	m_bDragonReplay = true;
}

void CSceneMgr::SceneChange(bool _bEnter)
{
	CSceneChange* pSceneChange;

	if (false == _bEnter)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"SceneChange_2.wav");

		for (int i = 0; i < (int)WINCX / 18; ++i)
		{
			for (int j = 0; j < (int)WINCY / 18; ++j)
			{
				pSceneChange = new CSceneChange;
				pSceneChange->SetPos(Vec2(i * 20, j * 20)); 
				pSceneChange->SetScale(Vec2(0.f, 0.f));
				pSceneChange->SetDelayTime(0.01f + (0.005f * (float)((int)WINCX / 10 - i)));
				CreateObject(pSceneChange, GROUP_TYPE::UI);
			}
		}
	}
	else
	{
		CSoundMgr::Get_Instance()->PlaySound(L"SceneChange_1.wav");

		for (int i = -1; i < (int)WINCX / 18; ++i)
		{
			for (int j = 0; j < (int)WINCY / 18; ++j)
			{
				pSceneChange = new CSceneChange;
				pSceneChange->SetPos(Vec2(i * 20, j * 20));
				pSceneChange->SetScale(Vec2(40.f, 40.f));
				pSceneChange->SetDelayTime(0.01f + (0.005f * (float)((int)WINCX / 10 - i)));
				pSceneChange->SetEnter();
				CreateObject(pSceneChange, GROUP_TYPE::UI);
			}
		}
	}
	
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	if (m_eCurScene != SCENE_TYPE::MAINMENU && m_eCurScene != SCENE_TYPE::TOOL && m_eCurScene != SCENE_TYPE::STAGE_03
		&& _eNext != SCENE_TYPE::MAINMENU)
	{
		SaveGhost();
	}


	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_eCurScene = _eNext;

	m_pCurScene->Enter(false);

	Replay_over();

}

void CSceneMgr::SaveGhost()
{
	int iSlot = (UINT)m_eCurScene;
	float fCurRecord = (float)g_iMinute * 60.f + (float)g_iSec + g_fTime;
	float fRecord = CEditor::Get_Instance()->LoadTimeRecord(iSlot);

	if (fRecord > fCurRecord)
	{
		CEditor::Get_Instance()->SaveGhost(iSlot);
	}
	CEditor::Get_Instance()->ClearGhost();
}

void CSceneMgr::Replay()
{
	CSoundMgr::Get_Instance()->PlaySound(L"ReplayStart.wav");
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		CObj* pPlayer = m_pCurScene->Get_GroupObject(GROUP_TYPE::PLAYER)[0];
		dynamic_cast<CPlayer*>(pPlayer)->TimeSlow(false);
	}
	m_pCurScene->DeleteAll();
	m_bReplay = true;
	CCamera::Get_Instance()->SetTarget(nullptr);
	
	//CEventMgr::Get_Instance()->ClearEvent();

}

void CSceneMgr::Replay_over()
{
	for (size_t i = 0; i < m_vecvecReplay.size(); ++i)
	{
		Safe_Delete_Vec(m_vecvecReplay[i]);
		/*for (size_t j = 0; j < m_vecvecReplay[i].size(); ++j)
		{
			delete m_vecvecReplay[i][j];
		}*/
		//m_vecvecReplay[i].clear();
	}
	m_vecvecReplay.clear();


}

void CSceneMgr::Replay_Render(HDC _dc)
{

	if (m_vecvecReplay.empty())
	{
		m_bReplay = false;
		CEventMgr::Get_Instance()->ClearEvent();
		m_pCurScene->Enter(true);
		m_fTime = 0.f;
		CCamera::Get_Instance()->SetVibrate();
		CSoundMgr::Get_Instance()->PlaySound(L"ReplayDone.wav");
		m_bDragonReplay = false;
		return;
	}


	for (int i = 0; i < m_vecvecReplay[m_vecvecReplay.size() - 1].size(); ++i)
	{
		vector<ReplayInfo*>		vecCurReplay = m_vecvecReplay[m_vecvecReplay.size() - 1];

		ReplayInfo* pCurReplay = vecCurReplay[i]; // 첫놈

		

		if (0 != pCurReplay->vDir.y)
		{
			dir_Render(_dc, pCurReplay);
		}
		else
		{
			normal_Render(_dc, pCurReplay);
		}

		delete vecCurReplay[i];
	}

	//=================== 화면 효과 =============================

	Vec2 vPos = CCamera::Get_Instance()->Get_RealPos(Vec2(0.f, 0.f));
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);

	Graphics g(_dc);

	int iRand = random(50, 100);
	int iAlpha = random(0, 2);
	if (0 == iAlpha)
	{
		iAlpha = 90;
	}
	else
	{
		iAlpha = 110;
	}

	int iCount = 10;

	if(m_bDragonReplay)
		g.FillRectangle(&SolidBrush(Color(iAlpha, 255, 10, 60)), (int)vPos.x, (int)vPos.y, (int)WINCX, (int)WINCY);
	else
		g.FillRectangle(&SolidBrush(Color(iAlpha, 60, 10, 255)), (int)vPos.x, (int)vPos.y, (int)WINCX, (int)WINCY);

	

	int iRandY = random(0, 400);
	int iRandY2 = random(1, 4);
	vPos.y += (float)iRandY;
	g.FillRectangle(&SolidBrush(Color(60, 0, 255- iRand, 150+ iRand)), (int)vPos.x, (int)vPos.y, (int)WINCX, iRandY2);
	vPos.y -= (float)iRandY;


	iRandY2 = random(10, (int)WINCY - 10);


	//흰 줄
	for (int i = 0; i < iCount; ++i)
	{
		iRandY = random(3, 20);
		int iRandX = random(0, (int)WINCX - 10);
		iAlpha = random(50, 190);

		g.FillRectangle(&SolidBrush(Color(iAlpha, 255, 255, 255)), (int)vPos.x + iRandX, (int)vPos.y + iRandY2, iRandY, 1);
	}

	//==========================================================

	m_vecvecReplay[m_vecvecReplay.size() - 1].clear();
	m_vecvecReplay.pop_back();
	
	
}

void CSceneMgr::normal_Render(HDC _dc, ReplayInfo * pCurReplay)
{
	//============camera============
	CCamera::Get_Instance()->SetLookAt(pCurReplay->vLookAt);


	//==============================


	//============vPos 세팅==============

	Vec2 vPos = pCurReplay->vPos;

	vPos = CCamera::Get_Instance()->Get_RealPos(vPos);
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	//======================================


	Graphics g(_dc);

	ImageAttributes* imgAttr = pCurReplay->ImgAttr;

	//2가지 기능
	// 1. SetColorKey

	float fRatio = pCurReplay->fRatio;

	int LTX = (int)(vPos.x - pCurReplay->Slicex * fRatio / 2.f);
	int LTY = (int)(vPos.y - pCurReplay->Slicey * fRatio / 2.f);
	int RBX = (int)(vPos.x + pCurReplay->Slicex * fRatio / 2.f);
	int RBY = (int)(vPos.y + pCurReplay->Slicey * fRatio / 2.f);

	Point LTpoint, RTpoint, LBpoint;


	if (0 <= pCurReplay->vDir.x)
	{
		LTpoint = Point(LTX, LTY);
		RTpoint = Point(RBX, LTY);
		LBpoint = Point(LTX, RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(pCurReplay->Img
			, destinationPoints, 3
			, pCurReplay->LTx
			, pCurReplay->LTy
			, pCurReplay->Slicex
			, pCurReplay->Slicey
			, UnitPixel, imgAttr, NULL, NULL);
	}
	else
	{
		LTpoint = Point(LTX + int(pCurReplay->Slicex * fRatio), LTY);
		RTpoint = Point(LTX - (RBX - LTX) + (int)(pCurReplay->Slicex * fRatio), LTY);
		LBpoint = Point(LTX + (int)(pCurReplay->Slicex * fRatio), RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(pCurReplay->Img
			, destinationPoints, 3
			, pCurReplay->LTx
			, pCurReplay->LTy
			, pCurReplay->Slicex
			, pCurReplay->Slicey
			, UnitPixel, imgAttr, NULL, NULL);
	}


}

void CSceneMgr::dir_Render(HDC _dc, ReplayInfo * pCurReplay)
{

	//============camera============
	CCamera::Get_Instance()->SetLookAt(pCurReplay->vLookAt);
	//==============================

	//============vPos 세팅==============

	Vec2 vPos = pCurReplay->vPos;

	vPos = CCamera::Get_Instance()->Get_RealPos(vPos);
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	//======================================


	Graphics g(_dc);

	ImageAttributes* imgAttr = pCurReplay->ImgAttr;
	imgAttr->SetColorKey(Color(255,255,255), Color(255, 255, 255), ColorAdjustTypeBitmap);


	//2가지 기능
	// 1. SetColorKey

	float fRatio = pCurReplay->fRatio;

	int LTX = (int)(vPos.x - pCurReplay->Slicex * fRatio / 2.f);
	int LTY = (int)(vPos.y - pCurReplay->Slicey * fRatio / 2.f);
	int RBX = (int)(vPos.x + pCurReplay->Slicex * fRatio / 2.f);
	int RBY = (int)(vPos.y + pCurReplay->Slicey * fRatio / 2.f);

	float fAngle = acos(pCurReplay->vDir.x) * (180.f / PI); // 각도 구하기

	if (0 > pCurReplay->vDir.y)
	{
		fAngle *= -1.f;
	}


	Point LTpoint = rotate(vPos, Point(LTX, LTY), fAngle);
	Point RTpoint = rotate(vPos, Point(RBX, LTY), fAngle);
	Point LBpoint = rotate(vPos, Point(LTX, RBY), fAngle);

	Point destinationPoints[] = {
	LTpoint,   // destination for upper-left point of original
	RTpoint,  // destination for upper-right point of original
	LBpoint };  // destination for lower-left point of original

	g.DrawImage(pCurReplay->Img
		, destinationPoints, 3
		, pCurReplay->LTx
		, pCurReplay->LTy
		, pCurReplay->Slicex
		, pCurReplay->Slicey
		, UnitPixel, imgAttr, NULL, NULL);
}

#include "stdafx.h"
#include "CMainGame.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "SelectGDI.h"
#include "CLineMgr.h"
#include "CSoundMgr.h"

//CMainGame* CMainGame::g_pInst = nullptr;

CMainGame::CMainGame()
	: m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CMainGame::~CMainGame()
{
	ReleaseDC(g_hwnd, m_hDC); // 윈도우한테 DC 해제하라고 알리는 함수

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int CMainGame::Initialize()
{
	CreateBrushPen();

	RECT rt = { 0, 0, WINCX, WINCY };

	//해상도에 맞게 윈도우 크기 조정
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(g_hwnd, nullptr, 500, 200, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(g_hwnd);

	//이중 버퍼링 용도의 비트맵과 DC 생성
	m_hBit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP holdBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // DC와 비트맵핸들을 연결시켜주기. 기존의 DC가 가리키던 비트맵핸들이 리턴으로 나온다.
	DeleteObject(holdBit); // 이전 비트맵핸들 제거.
	
	//폰트 배경
	SetBkMode(m_memDC, TRANSPARENT);

	//Manager초기화
	CSoundMgr::Get_Instance()->Initialize();
	CPathMgr::Get_Instance()->Initialize();
	CTimeMgr::Get_Instance()->Initialize();
	CKeyMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Initialize();
	CCollisionMgr::Get_Instance()->Initialize();

	return S_OK; // 성공한 경우 윈도우에서 리턴하는 값
}


void CMainGame::Progress()
{
	// ==============
	// Manager Update
	// ==============
	CTimeMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

	// ============
	// Scene Update
	// ============
	CSceneMgr::Get_Instance()->Update();

	CCollisionMgr::Get_Instance()->Update();

	// =========
	// Rendering
	// =========
	//화면 클리어

	SelectGDI brush(m_memDC, BRUSH_TYPE::BLACK);
	Rectangle(m_memDC, -1, -1, WINCX + 1, WINCY + 1);

	CSceneMgr::Get_Instance()->Render(m_memDC);

	CCamera::Get_Instance()->ZoomSet(m_memDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::Get_Instance()->Render();

	// ==============
	// 이벤트 지연처리
	// ==============
	CEventMgr::Get_Instance()->Update();
	
}

void CMainGame::CreateBrushPen()
{
	//hollow 색은 기본 제공 해주는거라 따로 delete 안해도 됨
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//red pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

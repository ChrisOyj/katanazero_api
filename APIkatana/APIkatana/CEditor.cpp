#include "stdafx.h"
#include "CEditor.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCamera.h"

#include "SelectGDI.h"
#include "CTexture.h"
#include "CBG_Outside.h"
#include "CBG_Mansion_1.h"
#include "CBG_Mansion_2.h"
#include "CBG_Boss.h"
#include "CMansionDark.h"

#include "CPlayer.h"
#include "CLineMgr.h"
#include "CSceneMgr.h"
#include "CMonster_Grant.h"
#include "CMonster_Gangster.h"
#include "CMonster_Pomp.h"
#include "CLaser.h"
#include "CSubWeapon.h"
#include "CLand.h"
#include "CWall.h"
#include "CCeiling.h"
#include "CAbstractFactory.h"

#include "CScene.h"
#include "CAlive.h"

CEditor::CEditor()
{
	


}

CEditor::~CEditor()
{}

void CEditor::SaveGhost(int _i)
{
	wstring strFile = L"../SaveData/Ghost";
	TCHAR strNum[16];
	_itow_s(_i, strNum, 10);

	strFile += strNum;
	strFile += L".dat";

	HANDLE		hFile = CreateFile(strFile.c_str()
		, GENERIC_WRITE			// 파일 접근 모드 (출력 : WRTIE, 입력 : READ)
		, NULL					// 공유 방식, NULL 지정시 공유 안함. (다른거 해주면 파일 열려있을 때 접근 가능)
		, NULL					// 보안 속성 모드
		, CREATE_ALWAYS			// 파일이 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 씀 (no생성)
		, FILE_ATTRIBUTE_NORMAL // 파일 속성 (읽기 전용, 숨김 파일 등등) 설정
		, NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hwnd, L"Save 실패", L"Fail", MB_OK);
	}

	DWORD		dwByte = 0;
	for (auto& iter : m_arrGhost)
	{
		WriteFile(hFile, &iter, sizeof(GhostInfo), &dwByte, nullptr);
	}


	CloseHandle(hFile);

	SaveTimeRecord(_i);
	
}

void CEditor::SaveTimeRecord(int _i)
{
	// =========================== 기록 저장 ===============================
	wstring strFile = L"../SaveData/TimeRecord";
	TCHAR strNum[16];
	_itow_s(_i, strNum, 10);

	strFile += strNum;
	strFile += L".dat";

	HANDLE	hFile = CreateFile(strFile.c_str()
		, GENERIC_WRITE			// 파일 접근 모드 (출력 : WRTIE, 입력 : READ)
		, NULL					// 공유 방식, NULL 지정시 공유 안함. (다른거 해주면 파일 열려있을 때 접근 가능)
		, NULL					// 보안 속성 모드
		, CREATE_ALWAYS			// 파일이 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 씀 (no생성)
		, FILE_ATTRIBUTE_NORMAL // 파일 속성 (읽기 전용, 숨김 파일 등등) 설정
		, NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hwnd, L"Save 실패", L"Fail", MB_OK);
	}

	DWORD		dwByte = 0;

	WriteFile(hFile, &g_iMinute, sizeof(int), &dwByte, nullptr);
	WriteFile(hFile, &g_iSec, sizeof(int), &dwByte, nullptr);
	WriteFile(hFile, &g_fTime, sizeof(float), &dwByte, nullptr);


	CloseHandle(hFile);
}

vector<GhostInfo> CEditor::LoadGhost(int _i)
{
	m_arrGhost.clear();

	wstring strFile = L"../SaveData/Ghost";
	TCHAR strNum[16];
	_itow_s(_i, strNum, 10);

	strFile += strNum;
	strFile += L".dat";

	// 파일 개방 함수
	HANDLE	hFile = CreateFile(strFile.c_str(),	// 파일의 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근 모드 (출력 : WRITE, 입력 : READ)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용하는가에 대한 설정, NULL 지정 시 공유안함
		NULL,				// 보안 속성 모드, NULL인 경우 기본값 설정
		OPEN_EXISTING,		// 파일이 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING - 파일이 있는 경우에만 로드
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 파일 등등을 설정), 아무런 속성이 없는 파일 모드 생성
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓸것이기 때문에 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		//MessageBox(g_hwnd, L"Load 실패", L"Fail", MB_OK);

		return vector<GhostInfo>();
	}

	DWORD			dwByte = 0;
	GhostInfo		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(GhostInfo), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_arrGhost.push_back(tInfo);
	}

	CloseHandle(hFile);

	return m_arrGhost;
}

float CEditor::LoadTimeRecord(int _i)
{
	wstring strFile = L"../SaveData/TimeRecord";
	TCHAR strNum[16];
	_itow_s(_i, strNum, 10);

	strFile += strNum;
	strFile += L".dat";


	// 파일 개방 함수
	HANDLE	hFile = CreateFile(strFile.c_str(),	// 파일의 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근 모드 (출력 : WRITE, 입력 : READ)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용하는가에 대한 설정, NULL 지정 시 공유안함
		NULL,				// 보안 속성 모드, NULL인 경우 기본값 설정
		OPEN_EXISTING,		// 파일이 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING - 파일이 있는 경우에만 로드
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 파일 등등을 설정), 아무런 속성이 없는 파일 모드 생성
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓸것이기 때문에 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return 9999.f;
	}

	DWORD			dwByte = 0;
	int				iMinute = 0;
	int				iSec = 0;
	float			fTime = 0.f;
	float			fReturn = 0.f;

	ReadFile(hFile, &iMinute, sizeof(int), &dwByte, nullptr);
	fReturn += (float)iMinute * 60.f;

	ReadFile(hFile, &iSec, sizeof(int), &dwByte, nullptr);
	fReturn += (float)iSec;

	ReadFile(hFile, &fTime, sizeof(float), &dwByte, nullptr);
	fReturn += (float)fTime;



	CloseHandle(hFile);

	return fReturn;
}

void CEditor::Initialize()
{
	m_pBG = CAbstractFactory<CBG_Outside>::Create();
	CreateObject(m_pBG, GROUP_TYPE::DEFAULT);

	m_tCurInfo.eEditType = EDIT_TYPE::LINE;

	CResMgr::Get_Instance()->LoadTexture(L"Player_Stance", L"texture\\Player\\Player_Idle_11.png");
	CResMgr::Get_Instance()->LoadTexture(L"Monster_Grant_Stance", L"texture\\Monster\\Monster_Grant_Stance.png");
	CResMgr::Get_Instance()->LoadTexture(L"Monster_Gangster_Stance_8", L"texture\\Monster\\Monster_Gangster_Stance_8.png");
	CResMgr::Get_Instance()->LoadTexture(L"Monster_Pomp_Idle", L"texture\\Monster\\Monster_Pomp_Idle.png");
	CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Knife", L"texture\\SubWeapon\\SubWeapon_Knife.png");
	CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Bottle", L"texture\\SubWeapon\\SubWeapon_Bottle.png");
	CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Beer", L"texture\\SubWeapon\\SubWeapon_Beer.png");
	CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Smoke", L"texture\\SubWeapon\\SubWeapon_Smoke.png");
	CResMgr::Get_Instance()->LoadTexture(L"Effects_CeilingLaser", L"texture\\Effects\\Effects_CeilingLaser.png");
}

void CEditor::Update()
{
	Key_Input();

	m_tCurInfo.vPos = Get_MousePos();
	m_tCurInfo.vPos = CCamera::Get_Instance()->Get_RealPos(m_tCurInfo.vPos);

	switch (m_tCurInfo.eEditType)
	{
	case EDIT_TYPE::LINE:
		Update_Line();
		break;
	case EDIT_TYPE::LAND:
		Update_Land();
		break;
	case EDIT_TYPE::WALL:
		Update_Wall();
		break;
	case EDIT_TYPE::CEILING:
		Update_Ceiling();
		break;
	case EDIT_TYPE::PLAYER:
		Update_Player();
		break;
	case EDIT_TYPE::MONSTER:
		Update_Monster();
		break;
	case EDIT_TYPE::LASER:
		Update_Laser();
		break;

	case EDIT_TYPE::SUB:
		Update_Sub();
		break;

	default:
		break;
	}
}

void CEditor::Render(HDC _dc)
{
	for (size_t i = 0; i < m_arrInfo.size(); ++i)
	{
		Render_Object(_dc, m_arrInfo[(int)i]);
	}

	SetTextColor(_dc, RGB(0, 200, 255));

	HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));
	SelectObject(_dc, hFont);
	DeleteObject(hFont);

	Render_Guide(_dc);
	Render_Info(_dc);
	Render_MousePos(_dc);
}

void CEditor::Release()
{
}

void CEditor::Set_Stage(int _iStageNum)
{
	Load(_iStageNum);

	for (size_t i = 0; i < m_arrInfo.size(); ++i)
	{
		switch (m_arrInfo[i].eEditType)
		{
		case EDIT_TYPE::LINE:
			Add_Line(m_arrInfo[i]);
			break;

		case EDIT_TYPE::LAND:
			Add_Land(m_arrInfo[i]);
			break;

		case EDIT_TYPE::WALL:
			Add_Wall(m_arrInfo[i]);
			break;

		case EDIT_TYPE::CEILING:
			Add_Ceiling(m_arrInfo[i]);
			break;
		case EDIT_TYPE::PLAYER:
			Add_Player(m_arrInfo[i]);
			break;
		case EDIT_TYPE::MONSTER:
			Add_Monster(m_arrInfo[i]);
			break;
		case EDIT_TYPE::SUB:
			Add_Sub(m_arrInfo[i]);
			break;
		case EDIT_TYPE::LASER:
			Add_Laser(m_arrInfo[i]);
			break;
		}
	}

	switch (_iStageNum)
	{
	case 1:
		CreateObject(CAbstractFactory<CBG_Outside>::Create(), GROUP_TYPE::DEFAULT);
		break;

	case 2:
		CreateObject(CAbstractFactory<CBG_Mansion_1>::Create(), GROUP_TYPE::DEFAULT);
		CreateObject(CAbstractFactory<CMansionDark>::Create(), GROUP_TYPE::MANSION);

		break;

	case 3:
		CreateObject(CAbstractFactory<CBG_Mansion_2>::Create(), GROUP_TYPE::DEFAULT);

		break;

	case 4:
		CreateObject(CAbstractFactory<CBG_Boss>::Create(), GROUP_TYPE::DEFAULT);

	}
}

void CEditor::Update_Line()
{
	if (KEY(LBUTTON, TAP))
	{
		m_tCurInfo.tLineInfo.vLeftPoint = m_tCurInfo.vPos;
	}
	if (KEY(LBUTTON, HOLD))
	{
		m_tCurInfo.tLineInfo.vRightPoint = m_tCurInfo.vPos;

		if (m_tCurInfo.tLineInfo.bStair)
		{
			m_tCurInfo.tLineInfo.vRightPoint.y = m_tCurInfo.tLineInfo.vLeftPoint.y- fabs(m_tCurInfo.tLineInfo.vRightPoint.x - m_tCurInfo.tLineInfo.vLeftPoint.x);
		}
		else
			m_tCurInfo.tLineInfo.vRightPoint.y = m_tCurInfo.tLineInfo.vLeftPoint.y;
	}
	if (KEY(LBUTTON, AWAY))
	{
		if (m_tCurInfo.tLineInfo.bStair)
		{
			if (m_tCurInfo.vPos.x < m_tCurInfo.tLineInfo.vLeftPoint.x)
			{
				Vec2 vTemp = m_tCurInfo.tLineInfo.vRightPoint;
				m_tCurInfo.tLineInfo.vRightPoint = m_tCurInfo.tLineInfo.vLeftPoint;
				m_tCurInfo.tLineInfo.vLeftPoint = vTemp;
			}
		}
		m_arrInfo.push_back(m_tCurInfo);
	}


	if (KEY(NUM1, TAP))
	{
		m_tCurInfo.tLineInfo.bStair = !m_tCurInfo.tLineInfo.bStair;
	}
	if (KEY(NUM2, TAP))
	{
		m_tCurInfo.tLineInfo.bOpen = !m_tCurInfo.tLineInfo.bOpen;
	}
	if (KEY(NUM3, TAP))
	{
		m_tCurInfo.iFloor--;
	}
	if (KEY(NUM4, TAP))
	{
		m_tCurInfo.iFloor++;
	}
}

void CEditor::Update_Land()
{
	if (KEY(LBUTTON, TAP))
	{
		m_tCurInfo.tLineInfo.vLeftPoint = m_tCurInfo.vPos;
	}
	if (KEY(LBUTTON, HOLD))
	{
		m_tCurInfo.tLineInfo.vRightPoint = m_tCurInfo.vPos;

		m_tCurInfo.vScale.y = 6.f;
		m_tCurInfo.vScale.x = m_tCurInfo.tLineInfo.vRightPoint.x - m_tCurInfo.tLineInfo.vLeftPoint.x;

		m_tCurInfo.vPos.y = m_tCurInfo.tLineInfo.vLeftPoint.y + m_tCurInfo.vScale.y * 0.5f;
		m_tCurInfo.vPos.x = m_tCurInfo.tLineInfo.vLeftPoint.x + m_tCurInfo.vScale.x * 0.5f;

	}
	if (KEY(LBUTTON, AWAY))
	{
		m_tCurInfo.tLineInfo.vRightPoint = m_tCurInfo.vPos;

		m_tCurInfo.vScale.y = 6.f;
		m_tCurInfo.vScale.x = m_tCurInfo.tLineInfo.vRightPoint.x - m_tCurInfo.tLineInfo.vLeftPoint.x;

		m_tCurInfo.vPos.y = m_tCurInfo.tLineInfo.vLeftPoint.y + m_tCurInfo.vScale.y * 0.5f;
		m_tCurInfo.vPos.x = m_tCurInfo.tLineInfo.vLeftPoint.x + m_tCurInfo.vScale.x * 0.5f;

		m_arrInfo.push_back(m_tCurInfo);
		ZeroMemory(&m_tCurInfo, sizeof(m_tCurInfo));
		m_tCurInfo.eEditType = EDIT_TYPE::LAND;
	}

}

void CEditor::Update_Wall()
{
	if (KEY(LBUTTON, TAP))
	{
		m_tCurInfo.tLineInfo.vLeftPoint = m_tCurInfo.vPos;
	}
	if (KEY(LBUTTON, HOLD))
	{
		m_tCurInfo.tLineInfo.vRightPoint = m_tCurInfo.vPos;

		m_tCurInfo.vScale.x = 10.f;
		m_tCurInfo.vScale.y = m_tCurInfo.tLineInfo.vRightPoint.y - m_tCurInfo.tLineInfo.vLeftPoint.y;

		m_tCurInfo.vPos.x = m_tCurInfo.tLineInfo.vLeftPoint.x + m_tCurInfo.vScale.x * 0.5f;
		m_tCurInfo.vPos.y = m_tCurInfo.tLineInfo.vLeftPoint.y + m_tCurInfo.vScale.y * 0.5f;

		if (m_tCurInfo.tLineInfo.vLeftPoint.x > m_tCurInfo.tLineInfo.vRightPoint.x) // 마우스가 왼쪽
		{
			m_tCurInfo.vPos.x -= m_tCurInfo.vScale.x;
		}

	}
	if (KEY(LBUTTON, AWAY))
	{
		m_tCurInfo.tLineInfo.vRightPoint = m_tCurInfo.vPos;

		m_tCurInfo.vScale.x = 10.f;
		m_tCurInfo.vScale.y = m_tCurInfo.tLineInfo.vRightPoint.y - m_tCurInfo.tLineInfo.vLeftPoint.y;

		m_tCurInfo.vPos.x = m_tCurInfo.tLineInfo.vLeftPoint.x + m_tCurInfo.vScale.x * 0.5f;
		m_tCurInfo.vPos.y = m_tCurInfo.tLineInfo.vLeftPoint.y + m_tCurInfo.vScale.y * 0.5f;

		m_tCurInfo.bLeft = false;

		if (m_tCurInfo.tLineInfo.vLeftPoint.x > m_tCurInfo.tLineInfo.vRightPoint.x) // 마우스가 왼쪽
		{
			m_tCurInfo.vPos.x -= m_tCurInfo.vScale.x;
			m_tCurInfo.bLeft = true;
		}

		m_arrInfo.push_back(m_tCurInfo);
		ZeroMemory(&m_tCurInfo, sizeof(m_tCurInfo));
		m_tCurInfo.eEditType = EDIT_TYPE::WALL;
	}



	if (KEY(NUM1, TAP))
	{
		m_tCurInfo.bClimb = !m_tCurInfo.bClimb;
	}
	if (KEY(NUM2, TAP))
	{
		m_tCurInfo.bLeft = !m_tCurInfo.bLeft;
	}
}

void CEditor::Update_Ceiling()
{
	if (KEY(LBUTTON, TAP))
	{
		m_tCurInfo.tLineInfo.vLeftPoint = m_tCurInfo.vPos;
	}
	if (KEY(LBUTTON, HOLD))
	{
		m_tCurInfo.tLineInfo.vRightPoint = m_tCurInfo.vPos;

		m_tCurInfo.vScale.y = 6.f;
		m_tCurInfo.vScale.x = m_tCurInfo.tLineInfo.vRightPoint.x - m_tCurInfo.tLineInfo.vLeftPoint.x;

		m_tCurInfo.vPos.y = m_tCurInfo.tLineInfo.vLeftPoint.y - m_tCurInfo.vScale.y * 0.5f;
		m_tCurInfo.vPos.x = m_tCurInfo.tLineInfo.vLeftPoint.x + m_tCurInfo.vScale.x * 0.5f;

	}
	if (KEY(LBUTTON, AWAY))
	{
		m_tCurInfo.tLineInfo.vRightPoint = m_tCurInfo.vPos;

		m_tCurInfo.vScale.y = 6.f;
		m_tCurInfo.vScale.x = m_tCurInfo.tLineInfo.vRightPoint.x - m_tCurInfo.tLineInfo.vLeftPoint.x;

		m_tCurInfo.vPos.y = m_tCurInfo.tLineInfo.vLeftPoint.y - m_tCurInfo.vScale.y * 0.5f;
		m_tCurInfo.vPos.x = m_tCurInfo.tLineInfo.vLeftPoint.x + m_tCurInfo.vScale.x * 0.5f;

		m_arrInfo.push_back(m_tCurInfo);
		ZeroMemory(&m_tCurInfo, sizeof(m_tCurInfo));
		m_tCurInfo.eEditType = EDIT_TYPE::CEILING;
	}
}

void CEditor::Update_Player()
{
	if (KEY(LBUTTON, TAP))
		m_arrInfo.push_back(m_tCurInfo);
}

void CEditor::Update_Monster()
{
	if (KEY(LBUTTON, TAP))
		m_arrInfo.push_back(m_tCurInfo);

	if (KEY(NUM1, TAP) && (UINT)m_tCurInfo.eMobType > (UINT)MOB_TYPE::GRANT)
	{
		UINT iCur = (UINT)m_tCurInfo.eMobType;
		--iCur;
		m_tCurInfo.eMobType = (MOB_TYPE)iCur;

	}

	if (KEY(NUM2, TAP) && (UINT)m_tCurInfo.eMobType < (UINT)MOB_TYPE::BOSS - 1)
	{
		UINT iCur = (UINT)m_tCurInfo.eMobType;
		++iCur;
		m_tCurInfo.eMobType = (MOB_TYPE)iCur;
	}

	if (KEY(NUM3, TAP))
	{
		m_tCurInfo.vDir.x *= -1.f;
	}
}

void CEditor::Update_Laser()
{
	if (KEY(LBUTTON, TAP))
		m_arrInfo.push_back(m_tCurInfo);
}

void CEditor::Update_Sub()
{
	if (KEY(LBUTTON, TAP))
		m_arrInfo.push_back(m_tCurInfo);

	if (KEY(NUM1, TAP) && (UINT)m_tCurInfo.eSubType > (UINT)SUB_TYPE::KNIFE)
	{
		UINT iCur = (UINT)m_tCurInfo.eSubType;
		--iCur;
		m_tCurInfo.eSubType = (SUB_TYPE)iCur;

	}

	if (KEY(NUM2, TAP) && (UINT)m_tCurInfo.eSubType < (UINT)SUB_TYPE::END - 1)
	{
		UINT iCur = (UINT)m_tCurInfo.eSubType;
		++iCur;
		m_tCurInfo.eSubType = (SUB_TYPE)iCur;
	}
}

void CEditor::Render_Tex(HDC _dc, SAVEINFO _Info)
{
	INT iFrame = 0;
	Image* pImage = nullptr;
	float fRatio = 1.f;

	switch (_Info.eEditType)
	{
	case EDIT_TYPE::PLAYER:
		iFrame = 11;
		pImage = CResMgr::Get_Instance()->FindTexture(L"Player_Stance")->Get_Image();
		break;

	case EDIT_TYPE::LASER:
		iFrame = 1;
		pImage = CResMgr::Get_Instance()->FindTexture(L"Effects_CeilingLaser")->Get_Image();
		break;

	case EDIT_TYPE::MONSTER:
		iFrame = 8;

		if (_Info.eMobType == MOB_TYPE::GRANT)
			pImage = CResMgr::Get_Instance()->FindTexture(L"Monster_Grant_Stance")->Get_Image();
		else if (_Info.eMobType == MOB_TYPE::GANGSTER)
			pImage = CResMgr::Get_Instance()->FindTexture(L"Monster_Gangster_Stance_8")->Get_Image();
		else
			pImage = CResMgr::Get_Instance()->FindTexture(L"Monster_Pomp_Idle")->Get_Image();

		break;

	case EDIT_TYPE::SUB:
		iFrame = 1;
		if (_Info.eSubType == SUB_TYPE::KNIFE)
			pImage = CResMgr::Get_Instance()->FindTexture(L"SubWeapon_Knife")->Get_Image();
		else if (_Info.eSubType == SUB_TYPE::BOTTLE)
			pImage = CResMgr::Get_Instance()->FindTexture(L"SubWeapon_Bottle")->Get_Image();
		else if (_Info.eSubType == SUB_TYPE::BEER)
			pImage = CResMgr::Get_Instance()->FindTexture(L"SubWeapon_Beer")->Get_Image();
		else
			pImage = CResMgr::Get_Instance()->FindTexture(L"SubWeapon_Smoke")->Get_Image();

		break;
	}

	INT iSlice = pImage->GetWidth() / iFrame;
	INT iHeight = pImage->GetHeight();


	//============vPos 세팅==============
	Vec2 vPos = CCamera::Get_Instance()->Get_RenderPos(_Info.vPos);
	//======================================

	Graphics g(_dc);
	ImageAttributes ImgAttr;
	ImgAttr.SetColorKey(Color(255, 255, 255), Color(255, 255, 255));

	int LTX = (int)(vPos.x - iSlice * fRatio / 2.f);
	int LTY = (int)(vPos.y - iHeight * fRatio / 2.f);
	int RBX = (int)(vPos.x + iSlice * fRatio / 2.f);
	int RBY = (int)(vPos.y + iHeight * fRatio / 2.f);

	Point LTpoint, RTpoint, LBpoint;


	if (0 <= _Info.vDir.x)
	{
		LTpoint = Point(LTX, LTY);
		RTpoint = Point(RBX, LTY);
		LBpoint = Point(LTX, RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(pImage
			, destinationPoints, 3
			, 0
			, 0
			, (int)iSlice
			, (int)iHeight
			, UnitPixel, &ImgAttr, NULL, NULL);
	}
	else
	{
		LTpoint = Point(LTX + (int)(iSlice * fRatio), LTY);
		RTpoint = Point(LTX - (RBX - LTX) + (int)(iSlice * fRatio), LTY);
		LBpoint = Point(LTX + (int)(iSlice * fRatio), RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(pImage
			, destinationPoints, 3
			, 0
			, 0
			, (int)iSlice
			, (int)iHeight
			, UnitPixel, &ImgAttr, NULL, NULL);
	}

	if (_Info.eEditType == EDIT_TYPE::LASER)
	{
		PEN_TYPE ePen = PEN_TYPE::RED;
		SelectGDI pen(_dc, ePen);

		MoveToEx(_dc, (int)vPos.x, (int)vPos.y + 10, nullptr);
		LineTo(_dc, (int)vPos.x, (int)vPos.y + 110);
	}
	

}

void CEditor::Render_Line(HDC _dc, SAVEINFO _Info)
{
	//============vPos 세팅==============
	Vec2 vLeftPoint = CCamera::Get_Instance()->Get_RenderPos(_Info.tLineInfo.vLeftPoint);
	Vec2 vRightPoint = CCamera::Get_Instance()->Get_RenderPos(_Info.tLineInfo.vRightPoint);
	//======================================

	PEN_TYPE ePen = PEN_TYPE::GREEN;
	SelectGDI pen(_dc, ePen);

	MoveToEx(_dc, (int)vLeftPoint.x, (int)vLeftPoint.y, nullptr);
	LineTo(_dc, (int)vRightPoint.x, (int)vRightPoint.y);
}

void CEditor::Render_Rect(HDC _dc, SAVEINFO _Info)
{
	//============vPos 세팅==============
	Vec2 vPos = CCamera::Get_Instance()->Get_RenderPos(_Info.vPos);
	//======================================

	PEN_TYPE ePen = PEN_TYPE::GREEN;
	BRUSH_TYPE eBrush = BRUSH_TYPE::HOLLOW;
	SelectGDI pen(_dc, ePen);
	SelectGDI brush(_dc, eBrush);

	Rectangle(_dc, (int)(vPos.x - _Info.vScale.x * 0.5f)
		, (int)(vPos.y - _Info.vScale.y * 0.5f)
		, (int)(vPos.x + _Info.vScale.x * 0.5f)
		, (int)(vPos.y + _Info.vScale.y * 0.5f));
}

void CEditor::Render_MousePos(HDC _dc)
{
	Render_Object(_dc, m_tCurInfo);

	TCHAR szBuff[64];
	Vec2 vRenderPos = CCamera::Get_Instance()->Get_RenderPos(m_tCurInfo.vPos);

	swprintf_s(szBuff, L"마우스 좌표 : (%d, %d)", (int)m_tCurInfo.vPos.x, (int)m_tCurInfo.vPos.y);
	TextOut(_dc, (int)vRenderPos.x + 10, (int)vRenderPos.y, szBuff, lstrlen(szBuff));
}

void CEditor::Render_Guide(HDC _dc)
{
	TCHAR szBuff[64];

	int startY = 0;

	swprintf_s(szBuff, L"========== 조작키 ==========");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"Q, E : 오브젝트 변경");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"1, 2, 3, 4 : 오브젝트 세부 조정");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"WASD : 카메라 이동");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"O, P : 슬롯 변경");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"F1, F2 : 저장, 불러오기");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"좌클릭 : 오브젝트 생성");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"우클릭 : 오브젝트 제거");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"BACKSPACE : 이전 행동 취소");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"DELETE : 전부 지우기");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"ESC : 메인 메뉴");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"============================");
	TextOut(_dc, 10, startY += 15, szBuff, lstrlen(szBuff));
}

void CEditor::Render_Info(HDC _dc)
{
	TCHAR szBuff[64];

	int startY = 0;

	swprintf_s(szBuff, L"========== INFO ==========");
	TextOut(_dc, 300, startY += 15, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"현재 슬롯 : %d", m_iCurSlot);
	TextOut(_dc, 300, startY += 15, szBuff, lstrlen(szBuff));

	switch (m_tCurInfo.eEditType)
	{
	case EDIT_TYPE::LINE:
		swprintf_s(szBuff, L"현재 선택 중인 오브젝트 : 라인");

		break;
	case EDIT_TYPE::WALL:
		swprintf_s(szBuff, L"현재 선택 중인 오브젝트 : 벽");

		break;
	case EDIT_TYPE::LAND:
		swprintf_s(szBuff, L"현재 선택 중인 오브젝트 : 땅");

		break;
	case EDIT_TYPE::PLAYER:
		swprintf_s(szBuff, L"현재 선택 중인 오브젝트 : 플레이어");

		break;
	case EDIT_TYPE::MONSTER:
		swprintf_s(szBuff, L"현재 선택 중인 오브젝트 : 몬스터");

		break;
	case EDIT_TYPE::SUB:
		swprintf_s(szBuff, L"현재 선택 중인 오브젝트 : 서브웨폰");

		break;
	case EDIT_TYPE::LASER:
		swprintf_s(szBuff, L"현재 선택 중인 오브젝트 : 레이져");

		break;
	case EDIT_TYPE::CEILING:
		swprintf_s(szBuff, L"현재 선택 중인 오브젝트 : 천장");

		break;

	default:
		break;
	}

	TextOut(_dc, 300, startY += 15, szBuff, lstrlen(szBuff));

	switch (m_tCurInfo.eEditType)
	{
	case EDIT_TYPE::LINE:
		swprintf_s(szBuff, L"STAIR, OPEN, FLOOR : (%d, %d, %d)", m_tCurInfo.tLineInfo.bStair, m_tCurInfo.tLineInfo.bOpen, m_tCurInfo.iFloor);

		break;
	case EDIT_TYPE::WALL:
		swprintf_s(szBuff, L"CLIMB, LEFT : (%d, %d)", m_tCurInfo.bClimb, m_tCurInfo.bLeft);

		break;
	case EDIT_TYPE::LAND:
		swprintf_s(szBuff, L" ");

		break;
	case EDIT_TYPE::PLAYER:
		swprintf_s(szBuff, L" ");

		break;
	case EDIT_TYPE::MONSTER:
		swprintf_s(szBuff, L"몬스터 타입 : (%d)", (UINT)m_tCurInfo.eMobType);

		break;
	case EDIT_TYPE::SUB:
		swprintf_s(szBuff, L"서브웨폰 타입 : (%d)", (UINT)m_tCurInfo.eSubType);

		break;
	case EDIT_TYPE::LASER:
		swprintf_s(szBuff, L" ");

		break;
	case EDIT_TYPE::CEILING:
		swprintf_s(szBuff, L" ");

		break;

	default:
		break;
	}

	TextOut(_dc, 300, startY += 15, szBuff, lstrlen(szBuff));
}

void CEditor::Render_Object(HDC _dc, SAVEINFO _Info)
{
	switch (_Info.eEditType)
	{
	case EDIT_TYPE::LINE:
		Render_Line(_dc, _Info);
		break;

	case EDIT_TYPE::WALL:
	case EDIT_TYPE::CEILING:
	case EDIT_TYPE::LAND:
		Render_Rect(_dc, _Info);
		break;

	case EDIT_TYPE::MONSTER:
	case EDIT_TYPE::LASER:
	case EDIT_TYPE::SUB:
	case EDIT_TYPE::PLAYER:
		Render_Tex(_dc, _Info);
		break;

	default:
		break;
	}
}

void CEditor::Add_Line(SAVEINFO & _Info)
{
	CLine* pLine = new CLine(_Info.tLineInfo);
	CLineMgr::Get_Instance()->Add_Line(pLine, _Info.iFloor);
}

void CEditor::Add_Wall(SAVEINFO & _Info)
{
	CObj* pObj = CAbstractFactory<CWall>::Create(_Info.vPos, GROUP_TYPE::WALL);
	pObj->SetScale(_Info.vScale);
	if (!_Info.bLeft)
		dynamic_cast<CWall*>(pObj)->SetWallRight();

	if (_Info.bClimb)
		dynamic_cast<CWall*>(pObj)->SetClimbTrue();

	CreateObject(pObj, GROUP_TYPE::WALL);

}

void CEditor::Add_Land(SAVEINFO & _Info)
{
	CObj* pObj = CAbstractFactory<CLand>::Create(_Info.vPos, GROUP_TYPE::LAND);
	pObj->SetScale(_Info.vScale);
	CreateObject(pObj, GROUP_TYPE::LAND);

}

void CEditor::Add_Ceiling(SAVEINFO & _Info)
{
	CObj* pObj = CAbstractFactory<CCeiling>::Create(_Info.vPos, GROUP_TYPE::CEILING);
	pObj->SetScale(_Info.vScale);
	CreateObject(pObj, GROUP_TYPE::CEILING);
}

void CEditor::Add_Player(SAVEINFO & _Info)
{
	CObj* pObj = CAbstractFactory<CPlayer>::Create(_Info.vPos, GROUP_TYPE::PLAYER);
	CSceneMgr::Get_Instance()->Get_CurScene()->AddObject(pObj, GROUP_TYPE::PLAYER);
	dynamic_cast<CAlive*>(pObj)->SetOriginY(_Info.vPos.y);
	//CreateObject(pObj, GROUP_TYPE::PLAYER);
	m_pPlayer = pObj;
}

void CEditor::Add_Monster(SAVEINFO & _Info)
{
	switch (_Info.eMobType)
	{
	case MOB_TYPE::GRANT:
		CAbstractFactory<CMonster_Grant>::Create_Monster(m_pPlayer, _Info.vPos, _Info.vDir);
		break;

	case MOB_TYPE::GANGSTER:
		CAbstractFactory<CMonster_Gangster>::Create_Monster(m_pPlayer, _Info.vPos, _Info.vDir);
		break;

	case MOB_TYPE::POMP:
		CAbstractFactory<CMonster_Pomp>::Create_Monster(m_pPlayer, _Info.vPos, _Info.vDir);
		break;

	default:
		break;
	}
}

void CEditor::Add_Laser(SAVEINFO & _Info)
{
	CObj* pObj = CAbstractFactory<CLaser>::Create(_Info.vPos, GROUP_TYPE::LASER);
	CreateObject(pObj, GROUP_TYPE::LASER);
}

void CEditor::Add_Sub(SAVEINFO & _Info)
{
	CAbstractFactory<CSubWeapon>::Create_Sub(_Info.vPos, _Info.eSubType);
}

void CEditor::EraseObject()
{
	bool bCol = false;
	int iIndex = 0;
	float fRange = 20.f;
	Vec2 vPos = m_tCurInfo.vPos;

	for (;iIndex < m_arrInfo.size(); ++iIndex)
	{
		if (m_arrInfo[iIndex].vPos.x - fRange < vPos.x && m_arrInfo[iIndex].vPos.x + fRange > vPos.x
			&& m_arrInfo[iIndex].vPos.y - fRange < vPos.y && m_arrInfo[iIndex].vPos.y + fRange > vPos.y)
		{
			bCol = true;
			break;
		}
	}

	if (bCol)
	{
		auto iter = m_arrInfo.begin();
		iter += iIndex;
		m_arrInfo.erase(iter);
	}

}

void CEditor::Key_Input()
{
	if (KEY(F1, TAP))
		Save(m_iCurSlot);

	if (KEY(F2, TAP))
		Load(m_iCurSlot);


	if (KEY(T, TAP))
	{
		DeleteObject(m_pBG);
		m_pBG = CAbstractFactory<CBG_Outside>::Create();
		CreateObject(m_pBG, GROUP_TYPE::DEFAULT);
	}
	if (KEY(Y, TAP))
	{
		DeleteObject(m_pBG);
		m_pBG = CAbstractFactory<CBG_Mansion_1>::Create();
		CreateObject(m_pBG, GROUP_TYPE::DEFAULT);
	}
	if (KEY(U, TAP))
	{
		DeleteObject(m_pBG);
		m_pBG = CAbstractFactory<CBG_Mansion_2>::Create();
		CreateObject(m_pBG, GROUP_TYPE::DEFAULT);
	}
	if (KEY(I, TAP))
	{
		DeleteObject(m_pBG);
		m_pBG = CAbstractFactory<CBG_Boss>::Create();
		CreateObject(m_pBG, GROUP_TYPE::DEFAULT);
	}
	if (KEY(O, TAP))
	{
		if (0 < m_iCurSlot)
			m_iCurSlot--;
	}
	if (KEY(P, TAP))
	{
			m_iCurSlot++;
	}

	if (KEY(ESC, TAP))
	{
		ChangeScene(SCENE_TYPE::MAINMENU);
	}

	if (KEY(BACKSPACE, TAP))
	{
		auto iter = m_arrInfo.end();
		m_arrInfo.erase(--iter);
	}

	if (KEY(RBUTTON, TAP))
	{
		EraseObject();
	}

	if (KEY(DELETEKEY, TAP))
	{
		m_arrInfo.clear();
	}

	if (KEY(Q, TAP) && (UINT)m_tCurInfo.eEditType > (UINT)EDIT_TYPE::LINE)
	{
		UINT iCur = (UINT)m_tCurInfo.eEditType;
		--iCur;
		m_tCurInfo.eEditType = (EDIT_TYPE)iCur;
		m_tCurInfo.vDir.x = 1.f;

	}

	if (KEY(E, TAP) && (UINT)m_tCurInfo.eEditType < (UINT)EDIT_TYPE::END - 1)
	{
		UINT iCur = (UINT)m_tCurInfo.eEditType;
		++iCur;
		m_tCurInfo.eEditType = (EDIT_TYPE)iCur;
		m_tCurInfo.vDir.x = 1.f;
	}


}

void CEditor::Save(int _iStageNum)
{
	wstring strFile = L"../SaveData/Stage";
	TCHAR strNum[16];
	_itow_s(_iStageNum, strNum, 10);

	strFile += strNum;
	strFile += L".dat";
	
	
	/*const TCHAR* strFile;


	switch (_iStageNum)
	{
	case 1:
		strFile = L"../SaveData/Stage1.dat";

		break;

	case 2:
		strFile = L"../SaveData/Stage2.dat";

		break;

	case 3:
		strFile = L"../SaveData/Stage3.dat";

		break;

	case 4:
		strFile = L"../SaveData/Stage4.dat";

		break;

	default:
		return;
	}*/

	HANDLE		hFile = CreateFile(strFile.c_str()
		, GENERIC_WRITE			// 파일 접근 모드 (출력 : WRTIE, 입력 : READ)
		, NULL					// 공유 방식, NULL 지정시 공유 안함. (다른거 해주면 파일 열려있을 때 접근 가능)
		, NULL					// 보안 속성 모드
		, CREATE_ALWAYS			// 파일이 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 씀 (no생성)
		, FILE_ATTRIBUTE_NORMAL // 파일 속성 (읽기 전용, 숨김 파일 등등) 설정
		, NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hwnd, L"Save 실패", L"Fail", MB_OK);
	}

	DWORD		dwByte = 0;
	for (auto& iter : m_arrInfo)
	{
		WriteFile(hFile, &iter, sizeof(SAVEINFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hwnd, L"Save 성공", L"성공", MB_OK);

}

void CEditor::Load(int _iStageNum)
{
	m_arrInfo.clear();

	wstring strFile = L"../SaveData/Stage";
	TCHAR strNum[16];
	_itow_s(_iStageNum, strNum, 10);

	strFile += strNum;
	strFile += L".dat";

	/*const TCHAR* strFile;

	switch (_iStageNum)
	{
	case 1:
		strFile = L"../SaveData/Stage1.dat";

		break;

	case 2:
		strFile = L"../SaveData/Stage2.dat";

		break;

	case 3:
		strFile = L"../SaveData/Stage3.dat";

		break;

	case 4:
		strFile = L"../SaveData/Stage4.dat";

		break;

	default:
		return;
	}*/


	// 파일 개방 함수
	HANDLE	hFile = CreateFile(strFile.c_str(),	// 파일의 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근 모드 (출력 : WRITE, 입력 : READ)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용하는가에 대한 설정, NULL 지정 시 공유안함
		NULL,				// 보안 속성 모드, NULL인 경우 기본값 설정
		OPEN_EXISTING,		// 파일이 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING - 파일이 있는 경우에만 로드
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 파일 등등을 설정), 아무런 속성이 없는 파일 모드 생성
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓸것이기 때문에 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hwnd, L"Load 실패", L"Fail", MB_OK);

		return;
	}

	DWORD			dwByte = 0;
	SAVEINFO		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(SAVEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_arrInfo.push_back(tInfo);
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 성공"), _T("성공"), MB_OK);

}

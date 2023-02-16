#include "stdafx.h"
#include "CKeyMgr.h"

#include "CMainGame.h"

int g_Arr[(int)KEY::LAST] = {
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	'1',
	'2',
	'3',
	'4',
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU,//ALT,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_CONTROL,//CTRL,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,
	VK_TAB,
	VK_LBUTTON,
	VK_RBUTTON,
	VK_BACK,
	VK_DELETE,
	//LAST
};


CKeyMgr::CKeyMgr()
{}

CKeyMgr::~CKeyMgr()
{}

void CKeyMgr::Initialize()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
}

void CKeyMgr::Update()
{
	HWND hWnd = GetFocus(); // 포커싱 잡고있는 윈도우의 핸들 값 리턴함

	if (hWnd != nullptr) 
	{
		for (int i = 0; i < (int)KEY::LAST; ++i) 
		{
			if (GetAsyncKeyState(g_Arr[i]) & 0x8000) { // 키가 눌려 있다
				if (m_vecKey[i].bPrevPush) // 전에도 눌렸으면
					m_vecKey[i].eState = KEY_STATE::HOLD; // 홀드인걸로
				else
					m_vecKey[i].eState = KEY_STATE::TAP; // 아니면 걍 탭

				m_vecKey[i].bPrevPush = true; // 전에 눌린거 활성화
			}
			else 
			{ // 키가 안눌려있다
				if (m_vecKey[i].bPrevPush) // 전에는 눌렸다면
					m_vecKey[i].eState = KEY_STATE::AWAY;
				else
					m_vecKey[i].eState = KEY_STATE::NONE;

				m_vecKey[i].bPrevPush = false; // 전에 눌린거 비활성화
			}
		}
	}
	else 
	{ // 포커싱이 null이라면
		for (int i = 0; i < (int)KEY::LAST; ++i) 
		{
			m_vecKey[i].bPrevPush = false;

			switch (m_vecKey[i].eState) {
			case KEY_STATE::TAP:
			case KEY_STATE::HOLD:
				m_vecKey[i].eState = KEY_STATE::AWAY;

				break;

			default:
				m_vecKey[i].eState = KEY_STATE::NONE;
				break;
			}
		}


	}
}

KEY_STATE CKeyMgr::Get_KeyState(KEY _key)
{
	return m_vecKey[(int)_key].eState;
}

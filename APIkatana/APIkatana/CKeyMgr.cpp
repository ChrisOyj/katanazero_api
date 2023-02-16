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
	HWND hWnd = GetFocus(); // ��Ŀ�� ����ִ� �������� �ڵ� �� ������

	if (hWnd != nullptr) 
	{
		for (int i = 0; i < (int)KEY::LAST; ++i) 
		{
			if (GetAsyncKeyState(g_Arr[i]) & 0x8000) { // Ű�� ���� �ִ�
				if (m_vecKey[i].bPrevPush) // ������ ��������
					m_vecKey[i].eState = KEY_STATE::HOLD; // Ȧ���ΰɷ�
				else
					m_vecKey[i].eState = KEY_STATE::TAP; // �ƴϸ� �� ��

				m_vecKey[i].bPrevPush = true; // ���� ������ Ȱ��ȭ
			}
			else 
			{ // Ű�� �ȴ����ִ�
				if (m_vecKey[i].bPrevPush) // ������ ���ȴٸ�
					m_vecKey[i].eState = KEY_STATE::AWAY;
				else
					m_vecKey[i].eState = KEY_STATE::NONE;

				m_vecKey[i].bPrevPush = false; // ���� ������ ��Ȱ��ȭ
			}
		}
	}
	else 
	{ // ��Ŀ���� null�̶��
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

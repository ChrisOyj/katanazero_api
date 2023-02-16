#pragma once

enum class KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NUM1, NUM2, NUM3, NUM4,
	F1, F2, F3, F4,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,
	ALT,
	LSHIFT,
	SPACE,
	CTRL,
	ENTER,
	ESC,
	TAB,
	LBUTTON,
	RBUTTON,
	BACKSPACE,
	DELETEKEY,
	LAST,

};

enum class KEY_STATE {
	TAP, // �� ���� ����
	HOLD,// �� ������ ����
	AWAY,// �� �� ����
	NONE,// �� �ȴ��� ����


};

struct tKeyInfo {
	KEY_STATE eState;
	bool bPrevPush; // ���� ������ üũ �뵵
};


class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo>	m_vecKey; // ���� ���� �ε����� �� Ű ���� �ǹ���

public:
	KEY_STATE	Get_KeyState(KEY _key);

public:
	void		Initialize();
	void		Update();



};


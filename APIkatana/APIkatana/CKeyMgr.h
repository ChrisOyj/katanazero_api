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
	TAP, // 막 누른 시점
	HOLD,// 꾹 누르고 있음
	AWAY,// 막 뗀 시점
	NONE,// 걍 안눌린 상태


};

struct tKeyInfo {
	KEY_STATE eState;
	bool bPrevPush; // 이전 프레임 체크 용도
};


class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo>	m_vecKey; // 벡터 안의 인덱스가 곧 키 값을 의미함

public:
	KEY_STATE	Get_KeyState(KEY _key);

public:
	void		Initialize();
	void		Update();



};


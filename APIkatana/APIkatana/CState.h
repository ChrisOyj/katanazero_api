#pragma once

enum class KEY_SLOT
{
	Q, W, E, R, T, A, S, D, F, G , NUM3, NUM4
	, END


};


class CState
{
public:
	CState();
	~CState();

public:
	void		Enter();
	void		Exit();

	CState*		Update();

};


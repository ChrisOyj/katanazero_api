#pragma once
#include "CKeyMgr.h"

class Command;

class CKeySlot
{
public:
	CKeySlot();
	~CKeySlot();

public:
	void		Update();


private:
	KEY			m_eCurKey;
	Command*	m_pCommand;
};


#pragma once
#include "CAlive.h"

class CMonster_Dragon
	: public CAlive
{
public:
	CMonster_Dragon();
	virtual ~CMonster_Dragon();

	CLONE(CMonster_Dragon);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);
	
public:
	void		Default();
	void		Run();
	void		Set();
	void		Sit();
	void		Dash();

private:
	void		Update_Default();
	void		Update_Sit();
	void		Update_Run();
	void		Update_Dash();
	void		Update_Set();
	void		CreateAfterImage();


private:
	CObj*		m_pMark;
	bool		m_bPeace = true;
	bool		m_bAfter = false;
	float		m_fAlpha = 1.f;
	float		m_fDashTime = 0.f;
};


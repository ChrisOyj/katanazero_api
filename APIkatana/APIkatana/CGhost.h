#pragma once
#include "CObj.h"

class CGhost
	: public CObj
{
public:
	CGhost();
	virtual ~CGhost();

	CLONE(CGhost);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);

private:
	vector<GhostInfo>					m_arrGhost;
	vector<GhostInfo>::iterator			m_CurGhost;
};


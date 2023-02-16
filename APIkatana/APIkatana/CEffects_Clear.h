#pragma once
#include "CEffects_Draw.h"


class CEffects_Clear :
	public CEffects_Draw
{
public:
	CEffects_Clear();
	virtual ~CEffects_Clear();

	CLONE(CEffects_Clear);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);

private:
	bool		m_bNewRecord = false;

};



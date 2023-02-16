#pragma once
#include "CEffects_Draw.h"


class CEffects_DarkScreen :
	public CEffects_Draw
{
public:
	CEffects_DarkScreen();
	virtual ~CEffects_DarkScreen();

	CLONE(CEffects_DarkScreen);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);
};


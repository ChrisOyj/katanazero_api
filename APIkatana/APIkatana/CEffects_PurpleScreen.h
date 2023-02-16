#pragma once
#include "CEffects_Draw.h"


class CEffects_PurpleScreen :
	public CEffects_Draw
{
public:
	CEffects_PurpleScreen();
	virtual ~CEffects_PurpleScreen();

	CLONE(CEffects_PurpleScreen);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);


};



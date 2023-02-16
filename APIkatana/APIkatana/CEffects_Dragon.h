#pragma once
#include "CEffects_Draw.h"


class CEffects_Dragon :
	public CEffects_Draw
{
public:
	CEffects_Dragon();
	virtual ~CEffects_Dragon();

	CLONE(CEffects_Dragon);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);


};




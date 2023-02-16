
#pragma once
#include "CEffects_Draw.h"


class CEffects_DeadUI :
	public CEffects_Draw
{
public:
	CEffects_DeadUI();
	virtual ~CEffects_DeadUI();

	CLONE(CEffects_DeadUI);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);


};



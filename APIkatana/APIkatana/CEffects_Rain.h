#pragma once
#include "CEffects_Draw.h"
class CEffects_Rain :
	public CEffects_Draw
{
public:
	CEffects_Rain();
	virtual ~CEffects_Rain();

	CLONE(CEffects_Rain);

public:
	void		Initialize();
	void		Update();
};


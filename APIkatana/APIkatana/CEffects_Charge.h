#pragma once
#include "CEffects_Draw.h"
class CEffects_Charge :
	public CEffects_Draw
{
public:
	CEffects_Charge();
	virtual ~CEffects_Charge();

	CLONE(CEffects_Charge);

public:
	void		Initialize();
	void		Update();
};


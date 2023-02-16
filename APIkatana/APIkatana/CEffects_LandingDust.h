#pragma once
#include "CEffects_Tex.h"

class CEffects_LandingDust :
	public CEffects_Tex
{
public:
	CEffects_LandingDust();
	virtual ~CEffects_LandingDust();

	CLONE(CEffects_LandingDust);


public:
	virtual void Initialize();
	virtual void Update();
};


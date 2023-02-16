#pragma once
#include "CEffects_Tex.h"

class CEffects_JumpDust :
	public CEffects_Tex
{
public:
	CEffects_JumpDust();
	virtual ~CEffects_JumpDust();

	CLONE(CEffects_JumpDust);


public:
	virtual void Initialize();
	virtual void Update();
};




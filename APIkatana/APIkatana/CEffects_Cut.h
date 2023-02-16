#pragma once
#include "CEffects_Tex.h"

class CEffects_Cut :
	public CEffects_Tex
{
public:
	CEffects_Cut();
	virtual ~CEffects_Cut();

	CLONE(CEffects_Cut);


public:
	virtual void Initialize();
	virtual void Update();
};



#pragma once
#include "CEffects_Tex.h"

class CEffects_Blood :
	public CEffects_Tex
{
public:
	CEffects_Blood();
	virtual ~CEffects_Blood();

	CLONE(CEffects_Blood);


public:
	virtual void Initialize();
	virtual void Update();
};


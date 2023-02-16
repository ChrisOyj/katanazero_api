#pragma once
#include "CEffects_Tex.h"

class CEffects_PompSlash :
	public CEffects_Tex
{
public:
	CEffects_PompSlash();
	virtual ~CEffects_PompSlash();

	CLONE(CEffects_PompSlash);


public:
	virtual void Initialize();
	virtual void Update();
};






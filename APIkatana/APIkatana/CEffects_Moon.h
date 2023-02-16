#pragma once
#include "CEffects_Tex.h"

class CEffects_Moon :
	public CEffects_Tex
{
public:
	CEffects_Moon();
	virtual ~CEffects_Moon();

	CLONE(CEffects_Moon);


public:
	virtual void Initialize();
	virtual void Update();
};


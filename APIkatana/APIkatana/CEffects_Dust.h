#pragma once
#include "CEffects_Tex.h"

class CEffects_Dust
	: public CEffects_Tex
{
public:
	CEffects_Dust();
	virtual ~CEffects_Dust();

	CLONE(CEffects_Dust);

public:
	virtual void Initialize();
	virtual void Update();
};


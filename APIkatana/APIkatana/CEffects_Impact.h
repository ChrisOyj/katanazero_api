#pragma once
#include "CEffects_Tex.h"

class CEffects_Impact :
	public CEffects_Tex
{
public:
	CEffects_Impact();
	virtual ~CEffects_Impact();

	CLONE(CEffects_Impact);


public:
	virtual void Initialize();
	virtual void Update();
};


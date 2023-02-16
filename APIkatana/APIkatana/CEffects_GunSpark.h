#pragma once
#include "CEffects_Tex.h"

class CEffects_GunSpark :
	public CEffects_Tex
{
public:
	CEffects_GunSpark();
	virtual ~CEffects_GunSpark();

	CLONE(CEffects_GunSpark);


public:
	virtual void Initialize();
	virtual void Update();
};


#pragma once
#include "CEffects_Tex.h"

class CEffects_GunFire :
	public CEffects_Tex
{
public:
	CEffects_GunFire();
	virtual ~CEffects_GunFire();

	CLONE(CEffects_GunFire);


public:
	virtual void Initialize();
	virtual void Update();
};




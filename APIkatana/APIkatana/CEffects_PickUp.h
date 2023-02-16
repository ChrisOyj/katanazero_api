#pragma once
#include "CEffects_Tex.h"

class CEffects_PickUp :
	public CEffects_Tex
{
public:
	CEffects_PickUp();
	virtual ~CEffects_PickUp();

	CLONE(CEffects_PickUp);


public:
	virtual void Initialize();
	virtual void Update();
};




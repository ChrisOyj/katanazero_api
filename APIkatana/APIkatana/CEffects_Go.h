#pragma once
#include "CEffects_Tex.h"

class CEffects_Go :
	public CEffects_Tex
{
public:
	CEffects_Go();
	virtual ~CEffects_Go();

	CLONE(CEffects_Go);


public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render(HDC _dc);
};




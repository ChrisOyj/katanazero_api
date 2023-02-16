#pragma once
#include "CEffects_Tex.h"

class CEffects_Breath
	: public CEffects_Tex
{
public:
	CEffects_Breath();
	virtual ~CEffects_Breath();

	CLONE(CEffects_Breath);

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render(HDC _dc);
};



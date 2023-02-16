#pragma once
#include "CEffects_Tex.h"

class CEffects_BloodWall :
	public CEffects_Tex
{
public:
	CEffects_BloodWall();
	virtual ~CEffects_BloodWall();

	CLONE(CEffects_BloodWall);

public:
	void	SetColorMatrix(ColorMatrix cm);

public:
	virtual void Initialize();
	virtual void Update();
};



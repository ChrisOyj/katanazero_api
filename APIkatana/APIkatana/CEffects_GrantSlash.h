#pragma once
#include "CEffects_Tex.h"

class CEffects_GrantSlash :
	public CEffects_Tex
{
public:
	CEffects_GrantSlash();
	virtual ~CEffects_GrantSlash();

	CLONE(CEffects_GrantSlash);


public:
	virtual void Initialize();
	virtual void Update();
};




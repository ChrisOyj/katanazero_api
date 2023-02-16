#pragma once
#include "CEffects_Tex.h"

class CDragon_Slash :
	public CEffects_Tex
{
public:
	CDragon_Slash();
	virtual ~CDragon_Slash();

	CLONE(CDragon_Slash);

public:
	virtual void Initialize();
	virtual void Update();
};




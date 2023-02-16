#pragma once
#include "CEffects_Tex.h"

class CEffects_Slash :
	public CEffects_Tex
{
public:
	CEffects_Slash();
	virtual ~CEffects_Slash();

	CLONE(CEffects_Slash);

public:
	virtual void Initialize();
	virtual void Update();

private:
	void		CreateAfterImage();
};




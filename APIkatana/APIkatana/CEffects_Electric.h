#pragma once
#include "CEffects_Draw.h"
class CEffects_Electric :
	public CEffects_Draw
{
public:
	CEffects_Electric();
	virtual ~CEffects_Electric();

	CLONE(CEffects_Electric);

public:
	void		Initialize();
	void		Update();
};


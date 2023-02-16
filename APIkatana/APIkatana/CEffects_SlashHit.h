#pragma once
#include "CEffects_Draw.h"

class CEffects_SlashHit :
	public CEffects_Draw
{
public:
	CEffects_SlashHit();
	virtual ~CEffects_SlashHit();

	CLONE(CEffects_SlashHit);

public:
	virtual void	Initialize();
	virtual void	Update();
	virtual void	Render(HDC _dc);



};



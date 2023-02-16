#pragma once
#include "CEffects_Draw.h"

class CEffects_Laser :
	public CEffects_Draw
{
public:
	CEffects_Laser();
	virtual ~CEffects_Laser();

	CLONE(CEffects_Laser);

public:
	void OnCollisionEnter(CCollider* _pOther) override;

public:
	void	Initialize();
	void	Update();

};


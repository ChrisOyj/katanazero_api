#pragma once
#include "CEffects_Draw.h"

class CEffects_Ilsum :
	public CEffects_Draw
{
public:
	CEffects_Ilsum();
	virtual ~CEffects_Ilsum();

	CLONE(CEffects_Ilsum);

public:
	void OnCollisionEnter(CCollider* _pOther) override;

public:
	void	Initialize();
	void	Update();
	void	Render(HDC _dc);

};


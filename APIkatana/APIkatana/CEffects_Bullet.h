#pragma once
#include "CEffects_Tex.h"

class CEffects_Bullet :
	public CEffects_Tex
{
public:
	CEffects_Bullet();
	virtual ~CEffects_Bullet();

	CLONE(CEffects_Bullet);

public:
	void OnCollisionEnter(CCollider* _pOther) override;


public:
	virtual void Initialize();
	virtual void Update();
};



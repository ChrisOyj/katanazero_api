#pragma once
#include "CEffects_Tex.h"

class CEffects_BulletReflect :
	public CEffects_Tex
{
public:
	CEffects_BulletReflect();
	virtual ~CEffects_BulletReflect();

	CLONE(CEffects_BulletReflect);


public:
	virtual void Initialize();
	virtual void Update();
};



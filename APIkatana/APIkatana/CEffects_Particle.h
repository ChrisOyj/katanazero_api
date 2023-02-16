#pragma once
#include "CAlive.h"
#include "CEffects_Draw.h"

class CEffects_Particle :
	public CEffects_Draw
{
public:
	CEffects_Particle();
	virtual ~CEffects_Particle();

	CLONE(CEffects_Particle);

public:
	virtual void Initialize();
	virtual void Update();

private:
	PhysicsInfo		m_tPhysics;


};


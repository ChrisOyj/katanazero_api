#pragma once
#include "CEffects_Tex.h"
#include "CAlive.h"

class CEffects_Glass
	: public CEffects_Tex
{
public:
	CEffects_Glass();
	virtual ~CEffects_Glass();

	CLONE(CEffects_Glass);

public:
	void		OnCollisionEnter(CCollider* pOther);
	void		OnCollisionExit(CCollider* pOther);

public:
	void		SetOriginY(float _f) { m_tPhysics.fOriginY = _f; }
	void		SetGreen();

	void		SetOrange();

public:
	virtual void Initialize();
	virtual void Update();

private:
	PhysicsInfo		m_tPhysics;
	bool			m_bLand = false;
};


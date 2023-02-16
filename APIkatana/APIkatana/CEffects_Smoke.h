#pragma once
#include "CEffects_Tex.h"
#include "CAlive.h"

class CEffects_Smoke
	: public CEffects_Tex
{
public:
	CEffects_Smoke();
	virtual ~CEffects_Smoke();

	CLONE(CEffects_Smoke);

public:
	void		OnCollisionEnter(CCollider* pOther);
	void		OnCollision(CCollider* pOther);
	void		OnCollisionExit(CCollider* pOther);

public:
	virtual void Initialize();
	virtual void Update();

private:
	Vec2		m_vTargetPos;
};


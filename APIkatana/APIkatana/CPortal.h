#pragma once
#include "CObj.h"
#include "CAnimator.h"

class CPortal
	: public CObj
{
public:
	CPortal();
	virtual ~CPortal();

	CLONE(CPortal);

public:
	void	SetImage() {m_pAnimator->Play(L"Effects_MansionDoor", false); }

	void	OnCollision(CCollider* _pOther);

public:
	void	Initialize();
	void	Update();

protected:
	bool	m_bClear;
	bool	m_bChange;
};


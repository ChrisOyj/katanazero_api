#pragma once
#include "CObj.h"

class CFall
	: public CObj
{
public:
	CFall();
	virtual ~CFall();

	CLONE(CFall);
	
public:
	void	OnCollisionEnter(CCollider* pOther);

public:
	void	Update();

};


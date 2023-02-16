#pragma once
#include "CObj.h"

class CSmokeCol
	: public CObj
{
public:
	CSmokeCol();
	virtual ~CSmokeCol();

	CLONE(CSmokeCol);

public:
	void		OnCollisionEnter(CCollider* _pOther);
	void		OnCollision(CCollider* _pOther);
	void		OnCollisionExit(CCollider* _pOther);

public:
	void		Initialize();
	void		Update();


};


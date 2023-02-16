#pragma once
#include "CSub.h"

class CSub_Smoke
	: public CSub
{
public:
	CSub_Smoke();
	virtual ~CSub_Smoke();

	CLONE(CSub_Smoke);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

	virtual void Update();

private:
	void		CreateSmoke();
};




#pragma once
#include "CSub.h"

class CSub_Bottle
	: public CSub
{
public:
	CSub_Bottle();
	virtual ~CSub_Bottle();

	CLONE(CSub_Bottle);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

	virtual void Update();

private:
	void		CreateGlass();
};




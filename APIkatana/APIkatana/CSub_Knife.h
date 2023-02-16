#pragma once
#include "CSub.h"

class CSub_Knife
	: public CSub
{
public:
	CSub_Knife();
	virtual ~CSub_Knife();

	CLONE(CSub_Knife);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

	virtual void Update();
};




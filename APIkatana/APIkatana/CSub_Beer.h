#pragma once
#include "CSub.h"

class CSub_Beer
	: public CSub
{
public:
	CSub_Beer();
	virtual ~CSub_Beer();

	CLONE(CSub_Beer);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

	virtual void Update();

private:
	void		CreateGlass();
};





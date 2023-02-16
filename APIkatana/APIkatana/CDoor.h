#pragma once
#include "CObj.h"

class CDoor
	: public CObj
{
public:
	CDoor();
	virtual ~CDoor();

	CLONE(CDoor);

public:
	void		OnCollisionEnter(CCollider* pOther);

public:
	void		Initialize();
	void		Update();

private:
	bool		m_bOpen = false;
	bool		m_bCreate = false;
};


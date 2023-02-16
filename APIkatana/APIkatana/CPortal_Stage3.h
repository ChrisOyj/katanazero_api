#pragma once
#include "CPortal.h"

class CPortal_Stage3
	: public CPortal
{
public:
	CPortal_Stage3();
	virtual ~CPortal_Stage3();

public:
	void		Initialize();
	void		Update();

private:
	bool		m_bOpen = false;


};


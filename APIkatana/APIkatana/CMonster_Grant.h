#pragma once
#include "CMonster.h"

class CMonster_Grant
	: public CMonster
{
public:
	CMonster_Grant();
	~CMonster_Grant() override;

	CLONE(CMonster_Grant);

public:
	void	Initialize() override;

private:
	virtual void Update_Attack() override;

};


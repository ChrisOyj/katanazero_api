#pragma once
#include "CMonster.h"

class CMonster_Pomp
	: public CMonster
{
public:
	CMonster_Pomp();
	~CMonster_Pomp() override;

	CLONE(CMonster_Pomp);

public:
	void	Initialize() override;
	//void	OnCollisionEnter(CCollider * _pOther) override;

private:
	virtual void Update_Attack() override;
};


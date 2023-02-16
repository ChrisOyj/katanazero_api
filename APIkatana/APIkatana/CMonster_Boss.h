#pragma once
#include "CMonster.h"

class CMonster_Boss
	: public CMonster
{
public:
	CMonster_Boss();
	~CMonster_Boss() override;

	CLONE(CMonster_Boss);

public:
	void	Initialize() override;
	void	Update();
	void	Render(HDC _dc);

private:
	virtual void Update_Attack() override;






};




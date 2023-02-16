#pragma once
#include "CMonster.h"

class CMark;

class CMonster_Gangster
	: public CMonster
{
public:
	CMonster_Gangster();
	~CMonster_Gangster() override;

	CLONE(CMonster_Gangster);

public:
	void Initialize() override;

private:
	void			Default() override;
	void			Attack() override;
	virtual void	Run();
	void			Hit(Vec2 _vDir) override;
	void			LaserHit() override;
	virtual void	Update_Attack() override;

private:
	void CreateArm();

	CMark* m_pArm;






};



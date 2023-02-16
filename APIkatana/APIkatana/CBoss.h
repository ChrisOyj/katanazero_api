#pragma once
#include "CMonster.h"

class CHitBox;

class CBoss :
	public CMonster
{
public:
	CBoss();
	~CBoss() override;

	CLONE(CBoss);

public:
	void			SetColorMatrix(bool _b);

public:
	void			Initialize()	final;
	void			Update()		final;
	void			Render(HDC _dc);

	void			OnCollision(CCollider* _pOther) override;
	void			OnCollisionEnter(CCollider* _pOther) override;
	void			OnCollisionExit(CCollider* _pOther) override;

	virtual void		Hit(Vec2 _vDir) override;
	void				LaserHit() override;

private:
	void	Update_Default() override;
	void	Update_Dash() override;
	void	Update_Air() override;
	void	Update_Run() override;
	void	Update_Attack() override;
	void	Update_Hang() override;
	void	Update_Airdash() override;
	void	Update_Hit() override;
	void	Update_Death() override;
	void	Update_Set() override;
	void	Update_Sit();
	void	Update_Animation();
	virtual void	Update_Skill();

	void	Default() override;
	void	Dash(bool _bPlayer = false);
	void	Jump() override;
	void	Attack() override;
	void	Hang() override;
	void	AirDash() override;
	void	Death() override;
	void	Sit();
	void	ThrowSubWeapon() override;
	void	ThrowSub(SUB_TYPE eType);
	void	Set();
	void	Skill();
	void	Parring(CObj* pOther);
	void	Run();


private: //Create Object
	void CreateAfterImage();
	void SkillEffects(Vec2 vNextPos);

	void CreateDust3();
	void CreateDust(float _f);

	void CreateSlash(Vec2 _vDir);


private:
	bool		m_bLaser = false;

	float		m_fSkillCool;
	float		m_fMaxCool;

	float		m_fAfterColor[3];
	bool		m_baftercolorplus;
	float		m_fAfterCount;
	float		m_fAfterSpeed;
	float		m_fAfterDuration;
	int			m_iAfterCount = 0;

	bool		m_bAfter;
	int			m_iDashCount;		//먼지 체크용
	float		m_fDashTime;

	float			m_fSlowTime;
	float			m_fSlowMaxTime;


};


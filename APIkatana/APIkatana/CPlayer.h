#pragma once
#include "CAlive.h"
#include "CState.h"

enum class KEY_SLOT
{
	Q, W, E, R, T, A, S, D, F, G, NUM3, NUM4
	, END


};

enum class STATE_TYPE
{
	IDLE,
	RUN,
	JUMP,
	HIT,
	DOWN,
	DEATH,
	STANDING,
	DASH,
	BACKSTEP,
	ATTACK,
	SKILL,
	END
};

enum class SWORDMAN_ATTACK_TYPE
{
	단공참,
	열파참,
	맹룡단공참,

	END,
};

class CHitBox;
class CKeySlot;

class CPlayer :
	public CAlive
{
public:
	CPlayer();
	~CPlayer() override;

	CLONE(CPlayer);


private:
	CState* m_pState;

	CKeySlot* m_arrKey[(UINT)KET_SLOT::END];
	










public:
	void			SetColorMatrix(bool _b);
	void			SetPlayMusic(bool _b = false) { m_bPlayMusic = true; m_bEnd = _b; }
	void			SetSmoke(bool _b = true) { m_bSmoke = _b; }
	void			SetAfter() { m_bAfter = false; }

	bool			IsSmoke() { return m_bSmoke; }
	SUB_TYPE		Get_SubType() { return m_eSubType; }

	void			TimeSlow(bool _b);

public:
	void			Initialize()	final;
	void			Update()		final;
	void			Render(HDC _dc);

	void			OnCollision(CCollider* _pOther) override;
	void			OnCollisionEnter(CCollider* _pOther) override;
	void			OnCollisionExit(CCollider* _pOther) override;

	virtual void			Hit(Vec2 _vDir) override;
	void					LaserHit() override;
	void					Animation();

private:
	void	Update_Default() override;
	void	Update_Dash() override;
	void	Update_Air() override;
	void	Update_Run() override;
	void	Update_Attack() override;
	void	Update_Crouch() override;
	void	Update_Hang() override;
	void	Update_Airdash() override;
	void	Update_Hit() override;
	void	Update_Death() override;
	void	Update_Set() override;
	void	Update_Sit() override;
	void	Update_PlayMusic();
	void	Update_Animation();
	void	Update_Skill();

	void	Default() override;
	void	Crouch() override;
	void	Dash() override;
	void	Jump() override;
	void	Attack() override;
	void	Hang() override;
	void	AirDash() override;
	void	Death() override;
	void	Set() override;
	void	Sit() override;
	void	ThrowSubWeapon() override;
	void	PlayMusic();
	void	Parring(CObj* pOther);
	void	Skill();
	void	SkillAttack();
	

private:
	void		Key_Input();
	void		TimeSlow_Update();

private: //Create Object
	void CreateAfterImage();
	void CreateDust3();
	void CreateDust(float _f);

	void CreateSlash(Vec2 _vDir);
	void SkillEffects(Vec2 vNextPos);

private:
	Vec2		m_vTargetPos;

	bool		m_bSmoke = false;

	bool		m_bPlayMusic;
	bool		m_bEnd;
	bool		m_bSubWeapon;
	SUB_TYPE	m_eSubType;

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
	float			m_fGhostTime = 0.f;
};


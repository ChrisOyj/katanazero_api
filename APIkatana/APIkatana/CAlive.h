#pragma once
#include "CObj.h"

struct PhysicsInfo
{
	float fOffsetY		= 0.f;
	float fFriction		= 1200.f;		//����
	float fXSpeed		= 0.f;		//�ӵ�
	float fYSpeed		= 0.f;		//�߷� ���� �ӵ�
	float fMaxXSpeed	= 200.f;		//�ӵ� ����
	float fMaxYSpeed	= 500.f;		//�߶� �ӵ� ����
	float fAccel		= 0.f;			//���ӵ�
	float fMaxAccel		= 800.f;		//�ִ밡�ӵ�

	float fAirFric = 50.f;		//��������
	float fOriginY = 0.f;
	float fAcc = 0.f;
	float fAirSpeed = 1200.f;		//���� ���� �ӵ�

	bool bFalling;
};


class CAlive abstract
	: public CObj
{
public:
	CAlive();
	virtual ~CAlive();

	CAlive* Clone() override PURE;

public:
	// ============== GETSET =================

	STATE_TYPE			Get_State() { return m_eState; }
	PhysicsInfo			Get_Physics() { return m_tPhysics; }
	bool				IsAir() { return m_bAir; }
	int					Get_CurFloor() { return m_iCurFloor; }

	void				SetState(STATE_TYPE _eType) { m_eState = _eType; }
	void				SetAir(bool _b) { m_bAir = _b; }
	void				SetOriginY(float _f) { m_tPhysics.fOriginY = _f; }
	void				SetBlocked() { JUMP(0); }
	void				SetXSpeed(float _f) { m_tPhysics.fXSpeed = _f; }

	// =======================================

public:
	void		Initialize()	override;
	void		Update()		override;

public:
	virtual void	Hit(Vec2 _vDir);
	virtual void	LaserHit();
	virtual void	Run() {}
	virtual void	Attack() {}
	virtual void	Parring(CObj* pOther) {}
	virtual void	Death() {}
	virtual void	Animation() { m_eState = STATE_TYPE::ANIMATION; }
	virtual void	Default() {}

protected:
	//Update
	virtual void	Update_Default()	PURE;
	virtual void	Update_Dash()		{}		
	virtual void	Update_Air()		{}		
	virtual void	Update_Run()		{}		
	virtual void	Update_Attack()		{}		
	virtual void	Update_Crouch()		{}		
	virtual void	Update_Hang()		{}		
	virtual void	Update_Airdash()	{}		
	virtual void	Update_Hit()		{}		
	virtual void	Update_Death()		{}		
	virtual void	Update_Set()		{}		
	virtual void	Update_Sit()		{}		
	virtual	void	Update_Walk()		{}
	virtual	void	Update_Parring()	{}
	virtual void	Update_PlayMusic()	{}
	virtual void	Update_Animation() {}
	virtual void	Update_Skill() {}

	//motion
	virtual void	Dash()				{}
	virtual void	Jump()				{}
	virtual void	Crouch()			{}
	virtual void	Hang()				{}
	virtual void	AirDash()			{}
	virtual void	Set()				{}
	virtual void	Sit()				{}
	virtual void	ThrowSubWeapon()	{}
	virtual void	Walk()				{}

protected:
	virtual	void		Physics_Update();
	void				CreateHitBox();

	void				CreateBlood(bool _bUp);

protected:
	CObj*			m_pHitBox;
	STATE_TYPE		m_eState;
	PhysicsInfo		m_tPhysics;

	bool			m_bLand;
	bool			m_bAir;
	bool			m_bHold;
	bool			m_bStair;

	int				m_iCurFloor = 0;
	int				m_iAttackCount;		//���� ���� üũ







};


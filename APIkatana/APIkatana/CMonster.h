#pragma once
#include "CAlive.h"
#include "CPlayer.h"

class CMark;

class CMonster abstract:
	public CAlive
{
public:
	CMonster();
	virtual ~CMonster();

	CMonster* Clone() override PURE;

public:
	MOB_TYPE		Get_MobType() { return m_eMobType; }

public:
	void OnCollision(CCollider* _pOther) override;
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;

	void Question();

public:
	void					Initialize() override;
	void					Update() override;
	void					Render(HDC _dc);

	void					Run() override;
	virtual	void			Parring(CObj* pOther);
	virtual void			Hit(Vec2 _vDir) override;
	void					LaserHit() override;

protected:
	void Update_Default() override;
	virtual void Update_Attack() PURE;
	void Update_Run() override;
	void Update_Walk() override;
	void Update_Hit() override;
	void Update_Death() override;
	void Update_Parring();

protected:
	void Default() override;
	void Attack() override;
	void Walk() override;
	void Death() override;

	void SetMark(MARK_TYPE _eType);

	//void Physics_Update() override;

protected:
	CObj*		m_pSight;
	CObj*		m_pMark;
	float		m_fBloodTime;

	MOB_TYPE	m_eMobType;


};


#pragma once
#include "CObj.h"

class CPlayer;
class CEffects;

class CSubWeapon :
	public CObj
{
public:
	CSubWeapon();
	~CSubWeapon() override;

	CLONE(CSubWeapon);

public:
	void OnCollisionEnter(CCollider * _pOther) override;
	void OnCollisionExit(CCollider * _pOther) override;

public:
	void	SetSubType(SUB_TYPE _eType) { m_eType = _eType; }

	SUB_TYPE	Get_SubType() { return m_eType; }

public:
	void Initialize() override;
	void Update() override;
	void Render(HDC _dc);

private:
	void CreatePickUp();


private:
	SUB_TYPE	m_eType;


};


#pragma once
#include "CObj.h"

class CPlayer;

class CMonster_Slash :
	public CObj
{
public:
	CMonster_Slash();
	~CMonster_Slash() override;

	CLONE(CMonster_Slash);

public:
	void OnCollisionEnter(CCollider* _pOther) override;

public:
	void SetEffectType(EFFECT_TYPE _eType) { m_eType = _eType; }

public:
	void Initialize() override;
	void Update() override;
	void Render(HDC _dc) override;

private:
	void Update_slash();
	void Update_bullet();
	void CreateReflect(Vec2 _vDir);
	void CreateCut();


private:
	EFFECT_TYPE	m_eType;


	float	m_fBulletSpeed;

};



#pragma once
#include "CObj.h"

class CHitBox :
	public CObj
{
public:
	CHitBox();
	virtual ~CHitBox();

	CLONE(CHitBox);

public:

	void OnCollision(CCollider* _pOther) override;
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;
public:
	void Update() override;
	void Render(HDC _dc) override;



private:
	//void CreateEffects(EFFECT_TYPE _eType, Vec2 _vDir, Vec2 _vPos);


};




#pragma once
#include "CObj.h"


class CLand :
	public CObj
{
public:
	CLand();
	virtual ~CLand();

	CLONE(CLand);

public:
	void	SetScale(Vec2 _vScale) override;

public:
	void	Initialize() override;
	void	Update() override;


public:
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollision(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;

};


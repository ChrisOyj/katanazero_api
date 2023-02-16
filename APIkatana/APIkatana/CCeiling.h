#pragma once
#include "CObj.h"


class CCeiling :
	public CObj
{
public:
	CCeiling();
	virtual ~CCeiling();

	CLONE(CCeiling);

public:
	void	SetScale(Vec2 _vScale) override;

public:
	void	Initialize() override;
	void	Update() override;


public:
	void OnCollisionEnter(CCollider* _pOther) override;

};


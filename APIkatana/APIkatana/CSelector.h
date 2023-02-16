#pragma once
#include "CObj.h"

class CSelector
	: public CObj
{
public:
	CSelector();
	~CSelector() override;

	CLONE(CSelector);

public:
	void Update() override;
	void Render(HDC _dc) override;

private:
	void physics_Update();

private:
	bool	m_bSelected;

	float m_fFriction;		//마찰
	float m_fXSpeed;		//속도
	float m_fMaxXSpeed;		//속도 제한
	float m_fAccel;			//가속도
	float m_fMaxAccel;		//최대가속도
	float m_fAcc;

	int	m_iAlpha;


};


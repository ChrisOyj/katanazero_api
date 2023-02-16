#pragma once
#include "CObj.h"

class CSceneChange
	: public CObj
{
public:
	CSceneChange();
	~CSceneChange() override;

	CLONE(CSceneChange);

public:
	void	SetEnter() { m_bEnter = true; }
	void	SetDelayTime(float _f) { m_fDelayTime = _f; }

public:
	void Update() override;
	void Render(HDC _dc) override;

private:
	bool	m_bEnter;
	float	m_fDelayTime;
};


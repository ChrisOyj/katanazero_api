#pragma once
#include "CEffects_Draw.h"


class CEffects_PlayMusic :
	public CEffects_Draw
{
public:
	CEffects_PlayMusic();
	virtual ~CEffects_PlayMusic();

	CLONE(CEffects_PlayMusic);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);

private:
	Vec2		m_vTargetPos;


};




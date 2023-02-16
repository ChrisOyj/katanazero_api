#pragma once
#include "CEffects_Draw.h"
class CEffects_SceneChange :
	public CEffects_Draw
{
public:
	CEffects_SceneChange();
	virtual ~CEffects_SceneChange();

	CLONE(CEffects_SceneChange);


public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);
};


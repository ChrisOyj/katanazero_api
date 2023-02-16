#pragma once
#include "CEffects.h"

class CEffects_Draw
	: public CEffects
{
public:
	CEffects_Draw();
	virtual ~CEffects_Draw();

	virtual CObj* Clone() PURE;

public:
	void			SetColorMatrix(ColorMatrix cm);

public:
	virtual	void	Initialize() PURE;
	virtual void	Update() PURE;
	virtual void	Render(HDC _dc);

protected:
	void			Effects_FadeOut(bool _bReal = false);
	void			Effects_AddSize();
	void			Effects_ChangeColor();

};
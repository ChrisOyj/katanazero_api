#pragma once
#include "CEffects.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"


class CEffects_Tex
	: public CEffects
{
public:
	CEffects_Tex();
	virtual ~CEffects_Tex();

	virtual CObj* Clone() PURE;


public:
	virtual		void	Initialize() PURE;
	virtual		void	Update() PURE;

protected:
	void	Set_Texture(const TCHAR* _strName, UINT _iCount, float _fDuration, EFFECT_TYPE _eType);

	void	Effects_Time(bool _bRealDT = false);
	void	Effects_FadeOut();

};


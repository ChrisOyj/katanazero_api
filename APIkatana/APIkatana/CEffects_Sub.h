#pragma once
#include "CEffects_Tex.h"

class CEffects_Sub
	: public CEffects_Tex
{
public:
	CEffects_Sub();
	virtual ~CEffects_Sub();

	CLONE(CEffects_Sub);

public:
	void		SetSubType(SUB_TYPE eSub) { m_eSubType = eSub; }

public:
	virtual void Initialize();
	virtual void Update();

private:
	SUB_TYPE	m_eSubType;
};


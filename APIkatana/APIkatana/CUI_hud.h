#pragma once
#include "CObj.h"


class CUI_hud
	: public CObj
{
public:
	CUI_hud();
	~CUI_hud() override;

	CLONE(CUI_hud);

public:
	void SetSubType(SUB_TYPE _eType) { m_eSubType = _eType; }
	void SetCurTime() { m_fCurTime = 1.f; }

public:
	void Update() override;
	void Render(HDC _dc) override;

private:
	void Render_Time(HDC _dc, Vec2 vPos);

	void color_Update(int _i, const int& _iRand);
	void CreateElectric();

private:
	SUB_TYPE	m_eSubType;
	CObj*		m_pScreen;

	float	m_fCurTime;
	float	m_fSlowMaxTime;
	float	m_fSlowTime;

	float	m_fTargetTime;

};


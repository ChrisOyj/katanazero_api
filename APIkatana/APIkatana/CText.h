#pragma once
#include "CObj.h"

class CText
	: public CObj
{
public:
	CText();
	~CText() override;

	CLONE(CText);

public:
	void Initialize() override;
	void Update() override;
	void Render(HDC _dc) override;

private:
	void Select();
	void CreateRain();

private:
	UINT	m_iSelected;
	float	m_fAlpha;
	bool	m_bUP;


};


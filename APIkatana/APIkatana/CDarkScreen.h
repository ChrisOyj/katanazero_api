#pragma once
#include "CObj.h"

class CDarkScreen
	: public CObj
{
public:
	CDarkScreen();
	~CDarkScreen() override;

	CLONE(CDarkScreen);

public:
	void SetAlpha(float _f) { m_fAlpha = _f; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
public:
	void Update() override;
	void Render(HDC _dc) override;

	void Delete() { m_bDelete = true; }

private:
	bool		m_bDelete;
	float		m_fAlpha;
	float		m_fSpeed;
};


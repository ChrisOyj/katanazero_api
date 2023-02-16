#pragma once
#include "CObj.h"

class CMansionDark
	: public CObj
{
public:
	CMansionDark();
	virtual ~CMansionDark();

	CLONE(CMansionDark);

public:
	void		OnCollisionEnter(CCollider* _pOther);
	void		OnCollisionExit(CCollider* _pOther);

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);

private:
	void		CreateGlass();

private:
	bool		m_bCol = false;
	int			m_iAlpha = 255;

	Vec2		m_vRectPos[3];
};


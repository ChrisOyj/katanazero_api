#pragma once
#include "CObj.h"

class CMenu
	: public CObj
{
public:
	CMenu();
	~CMenu();

	CLONE(CMenu);

public:
	void	Initialize();
	void	Update();
	void	Render(HDC _dc);

private:
	void Update_Default();
	void Update_Option();
	
	void Render_Default(HDC _dc);
	void Render_Option(HDC _dc);

	void	Render_Select(HDC _dc, Vec2 _vPos);
	void	Render_Select2(HDC _dc, Vec2 _vPos);

private:
	int		m_iPhase;

	int		m_iSelect;
	float	m_fColor;
	bool	m_bColorPlus = false;

	

};


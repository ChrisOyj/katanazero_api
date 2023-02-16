#pragma once

class CLine
{
public:
	CLine();
	CLine(Vec2& tLeft, Vec2& tRight, bool _bStair, bool _bOpen);
	CLine(LINEINFO& tInfo);
	~CLine();

public:
	void			Set_Info(LINEINFO _tInfo) { m_tInfo = _tInfo; }
	void			Set_Col(bool _b) { m_bCol = _b; }

	const LINEINFO& Get_Info(void) const { return m_tInfo; }

public:
	void		Render(HDC hDC);

private:
	bool			m_bCol;
	LINEINFO		m_tInfo;
};


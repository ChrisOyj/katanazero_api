#pragma once

class CMainGame {
	SINGLE(CMainGame);

public:
	HDC		Get_MainDC() { return m_hDC; }
	HBRUSH	Get_Brush(BRUSH_TYPE _etype) { return m_arrBrush[(UINT)_etype]; }
	HPEN	Get_Pen(PEN_TYPE _etype) { return m_arrPen[(UINT)_etype]; }


public:
	int					Initialize();
	void				Progress(); // 계속 실행 될 함수

private:
	void				CreateBrushPen();


private:
	HDC				m_hDC; // 메인 윈도우에 Draw할 DC

	double			m_dDT = 0.;

	//더블버퍼
	HBITMAP			m_hBit;
	HDC				m_memDC;

	HBRUSH			m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN			m_arrPen[(UINT)PEN_TYPE::END];

};


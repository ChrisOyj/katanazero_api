#pragma once
#include "CLine.h"

class CObj;

class CLineMgr
{
	SINGLE(CLineMgr);

#pragma region GET,SET
public:
	const vector<vector<CLine*>>&	Get_vecLine() { return m_arrLine; }
	int				Get_CurFloor() { return m_iCurFloor; }
	float			Get_CurFloorY() { return m_arrLine[m_iCurFloor].front()->Get_Info().vRightPoint.y - 50.f; }
	Vec2			Get_StairPos(int _iCurFloor, int _iTargetFloor);
	bool			Get_Stair() { return m_bStair; }
	float			Get_LineY() { return m_fLineY; }
	bool			Get_Open(Vec2& vPos, float fOffsetY);

	void			Set_Player(CObj*	_pPlayer) { m_pPlayer = _pPlayer; }
#pragma endregion GET,SET

public:
	void		Initialize(void);
	void		Update();
	void		Render(HDC hDC);
	void		Release(void);

public:
	bool			Collision_Line(Vec2& vPos, float fOffsetY, float* pY, bool* pStair, int* iFloor);
	void			Add_Line(CLine* pLine, int iFloor = 0);

private:
	void			Line_ColFalse();

private:
	CObj*							m_pPlayer;
	bool							m_bEditMode;

	//bool							m_bCol;
	bool							m_bStair;

	float							m_fLineY;

	int								m_iCurFloor;

	vector<vector<CLine*>>			m_arrLine;
};


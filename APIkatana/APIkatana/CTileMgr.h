#pragma once

class CTileMgr
{
	SINGLE(CTileMgr)



public:

	void		Initialize();
	void		Update();
	void		Render(HDC _dc);

	void		Picking_Tile(POINT pt, const int& iDrawID, const int& iOption);


private:
	vector<CObj*>			m_arrTile;


};


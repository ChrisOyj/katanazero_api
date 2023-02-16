#include "stdafx.h"
#include "CTileMgr.h"

#include "CTile.h"
#include "CAbstractFactory.h"

CTileMgr::CTileMgr()
{}

CTileMgr::~CTileMgr()
{}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = float((TILECX * j) + (TILECX >> 1));
			float fY = float((TILECY * j) + (TILECY >> 1));

			CObj* pObj = CAbstractFactory<CTile>::Create(fX, fY);
			m_arrTile.push_back(pObj);

		}
	}
}

void CTileMgr::Update()
{
	for (auto& iter : m_arrTile)
		iter->Update();
}

void CTileMgr::Render(HDC _dc)
{
	for (auto& iter : m_arrTile)
		iter->Render(_dc);
}

void CTileMgr::Picking_Tile(POINT pt, const int & iDrawID, const int & iOption)
{
	int iWidthX = pt.x / TILECX;
	int iHeightY = pt.y / TILECY;

	int iIndex = iHeightY * TILEX + iWidthX;

	if (0 > iIndex || m_arrTile.size() <= iIndex)
		return;



}

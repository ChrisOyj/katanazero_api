#include "stdafx.h"
#include "SelectGDI.h"
#include "CMainGame.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr)
{
	HPEN hPen = CMainGame::Get_Instance()->Get_Pen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr)
{
	HBRUSH hBrush = CMainGame::Get_Instance()->Get_Brush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}

#include "stdafx.h"
#include "CLine.h"

#include "CCamera.h"
#include "SelectGDI.h"

CLine::CLine()
	: m_tInfo()
	, m_bCol(false)
{
}


CLine::CLine(Vec2& tLeft, Vec2& tRight, bool _bStair, bool _bOpen)
	: m_tInfo(tLeft, tRight, _bStair, _bOpen)
{

}

CLine::CLine(LINEINFO& tLine)
	: m_tInfo(tLine)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_bCol)
		ePen = PEN_TYPE::RED;

	SelectGDI pen(hDC, ePen);

	Vec2 vLeftPos = CCamera::Get_Instance()->Get_RenderPos(m_tInfo.vLeftPoint);
	Vec2 vRightPos = CCamera::Get_Instance()->Get_RenderPos(m_tInfo.vRightPoint);

	MoveToEx(hDC, (int)vLeftPos.x, (int)vLeftPos.y, nullptr);
	LineTo(hDC, (int)vRightPos.x, (int)vRightPos.y);

	
}

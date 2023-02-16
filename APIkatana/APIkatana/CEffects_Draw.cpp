#include "stdafx.h"
#include "CEffects_Draw.h"

#include "CTimeMgr.h"

CEffects_Draw::CEffects_Draw()
{
}

CEffects_Draw::~CEffects_Draw()
{
}

void CEffects_Draw::SetColorMatrix(ColorMatrix cm)
{
	m_tInfo.RGB[0] = 0;
	m_tInfo.RGB[1] = 0;
	m_tInfo.RGB[2] = 0;
	m_tInfo.iAlpha = 0;
}


void CEffects_Draw::Render(HDC _dc)
{
	Vec2 vPos = Get_Pos();
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	Vec2 vScale = Get_Scale();

	int LTX = (int)(vPos.x - vScale.x * 0.5f);
	int LTY = (int)(vPos.y - vScale.y * 0.5f);
	int RBX = (int)(vPos.x + vScale.x * 0.5f);
	int RBY = (int)(vPos.y + vScale.y * 0.5f);

	Point LTpoint = rotate(vPos, Point(LTX, LTY), m_fTheta);
	Point LBpoint = rotate(vPos, Point(LTX, RBY), m_fTheta);
	Point RTpoint = rotate(vPos, Point(RBX, LTY), m_fTheta);
	Point RBpoint = rotate(vPos, Point(RBX, RBY), m_fTheta);

	Graphics g(_dc);

	Point destinationPoints[] = {
		LTpoint, LBpoint, RBpoint, RTpoint };

	GraphicsPath path;
	path.AddLines(destinationPoints, 4);

	g.FillPath(&SolidBrush(Color(m_tInfo.iAlpha, m_tInfo.RGB[0], m_tInfo.RGB[1], m_tInfo.RGB[2])), &path);
}

void CEffects_Draw::Effects_FadeOut(bool _bReal)
{
	if (0 < m_tInfo.iAlpha)
	{
		if (_bReal)
			m_tInfo.iAlpha -= (int)(m_tInfo.fFadeSpeed * RealfDT);
		else
			m_tInfo.iAlpha -= (int)(m_tInfo.fFadeSpeed * fDT);
	}

	if (7 >= m_tInfo.iAlpha)
	{
		DeleteObject(this);
	}
}

void CEffects_Draw::Effects_AddSize()
{
}

void CEffects_Draw::Effects_ChangeColor()
{
}

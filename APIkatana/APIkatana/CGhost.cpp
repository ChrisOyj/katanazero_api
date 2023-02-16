#include "stdafx.h"
#include "CGhost.h"

#include "CSceneMgr.h"
#include "CEditor.h"
#include "CTimeMgr.h"

#include "CScene.h"
#include "CAnimator.h"
#include "CAnimation.h"

CGhost::CGhost()
{
}

CGhost::~CGhost()
{
}


void CGhost::Initialize()
{
	m_arrGhost = CEditor::Get_Instance()->LoadGhost((UINT)CSceneMgr::Get_Instance()->Get_CurSceneType());

	m_CurGhost = m_arrGhost.begin();

}

void CGhost::Update()
{
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 0.f)
		return;

	m_fAcc += RealfDT;

	if (m_fAcc > 0.016f)
	{
		m_fAcc = 0.f;
		if (m_CurGhost == m_arrGhost.end())
		{
			DeleteObject(this);
			return;
		}

		m_CurGhost++;
	}

	
}

void CGhost::Render(HDC _dc)
{
	if (m_CurGhost == m_arrGhost.end() || !g_bGhost)
	{
		return;
	}

	Vec2 vPos = m_CurGhost->vPos;

	//vPos = CCamera::Get_Instance()->Get_RealPos(vPos);
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	//======================================
	wstring wKey = m_CurGhost->ImageKey;
	Image* pImage = CSceneMgr::Get_Instance()->Get_CurScene()->Get_Player()->Get_Animator()->FindAnimation(wKey)->Get_Image();

	Graphics g(_dc);

	ImageAttributes imgAttr;
	/*ColorMatrix cm = {
		   0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   1.f, 0.2f, 1.f, 0.0f, 1.0f };*/

	ColorMatrix cm = {
		   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.5f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 0.8f, 0.0f,
		   0.3f, 0.0f, 0.3f, 0.0f, 1.0f };

	imgAttr.SetColorMatrix(&cm, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	//2가지 기능
	// 1. SetColorKey

	float fRatio = 1.f;

	int LTX = (int)(vPos.x - m_CurGhost->Slicex * fRatio / 2.f);
	int LTY = (int)(vPos.y - m_CurGhost->Slicey * fRatio / 2.f);
	int RBX = (int)(vPos.x + m_CurGhost->Slicex * fRatio / 2.f);
	int RBY = (int)(vPos.y + m_CurGhost->Slicey * fRatio / 2.f);

	Point LTpoint, RTpoint, LBpoint;


	if (0 <= m_CurGhost->vDir.x)
	{
		LTpoint = Point(LTX, LTY);
		RTpoint = Point(RBX, LTY);
		LBpoint = Point(LTX, RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original


		g.DrawImage(pImage
			, destinationPoints, 3
			, m_CurGhost->LTx
			, m_CurGhost->LTy
			, m_CurGhost->Slicex
			, m_CurGhost->Slicey
			, UnitPixel, &imgAttr, NULL, NULL);
	}
	else
	{
		LTpoint = Point(LTX + int(m_CurGhost->Slicex * fRatio), LTY);
		RTpoint = Point(LTX - (RBX - LTX) + (int)(m_CurGhost->Slicex * fRatio), LTY);
		LBpoint = Point(LTX + (int)(m_CurGhost->Slicex * fRatio), RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(pImage
			, destinationPoints, 3
			, m_CurGhost->LTx
			, m_CurGhost->LTy
			, m_CurGhost->Slicex
			, m_CurGhost->Slicey
			, UnitPixel, &imgAttr, NULL, NULL);
	}

}

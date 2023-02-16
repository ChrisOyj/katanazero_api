#include "stdafx.h"
#include "CAfterImage.h"

#include "CTexture.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

CAfterImage::CAfterImage()
	: m_fAlpha(0.55f)
	, m_fAlphaCount(5.f)
{
	m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.75f, 0.0f, 1.0f };
}

CAfterImage::~CAfterImage()
{
	//delete m_colorMatrix;
	delete m_pAnim;
}

void CAfterImage::SetAnim(CAnimation _pAnim)
{
	m_pAnim = new CAnimation(_pAnim);
}

void CAfterImage::Update()
{

	if (0 < m_fAlpha)
	m_fAlpha -= m_fAlphaCount * fDT;

	//투명도, 색 변환
	/**m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, m_fAlpha, 0.0f,
		1.f-m_fColor + 0.1f, m_fColor + 0.5f, 0.9f, 0.0f, 1.f };*/

	*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, m_fAlpha, 0.0f,
		m_fRGB[0], m_fRGB[1], m_fRGB[2], 0.0f, 1.f };

	/**m_colorMatrix = {
			1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 0.0f, 1.0f     };*/

	if (0.1f >= m_fAlpha)
	{
		DeleteObject(this);
	}

}

void CAfterImage::Render(HDC _dc)
{
	if (m_fTheta)
		m_pAnim->dir_after_Render(_dc, Get_Pos(), m_fTheta, Get_Ratio(), m_colorMatrix);
	else
		m_pAnim->after_Render(_dc, Get_Pos(), Get_Dir().x, Get_Ratio(), m_colorMatrix);

}

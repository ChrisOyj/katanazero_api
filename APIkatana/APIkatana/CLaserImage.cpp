#include "stdafx.h"
#include "CLaserImage.h"


#include "CTimeMgr.h"
#include "CEffects_Particle.h"
#include "CAbstractFactory.h"

CLaserImage::CLaserImage()
	: m_iRow(0)
{
	m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.7f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.7f, 0.5f, 0.0f, 0.0f, 1.0f };
}

CLaserImage::~CLaserImage()
{
	delete m_pBitmap;
}

void CLaserImage::SetAnimFrm(tAnimFrm _tAnimFrm)
{
	m_tAnimFrm = _tAnimFrm;
}

void CLaserImage::SetImage(Image * _Image)
{
	m_Image = _Image;
	m_pBitmap = GdiplusImaGet_oBitmap(_Image, (int)m_tAnimFrm.vSlice.x, (int)m_tAnimFrm.vLT.x, (int)m_tAnimFrm.vLT.y, Color::Transparent);
	m_iRow -= 1;
}

void CLaserImage::Update()
{
	m_fTime += fDT;
	if (0.02f <= m_fTime)
	{
		m_fTime = 0.f;
		INT iSlice = m_pBitmap->GetWidth();
		INT iHeight = m_pBitmap->GetHeight();

		if (iHeight > m_iRow)
			++m_iRow;
		else
			DeleteObject(this);


		Color color, colorTemp;
		for (INT iColumn = 0; iColumn < iSlice; ++iColumn)
		{
			m_pBitmap->GetPixel(iColumn, m_iRow, &color);
			colorTemp.SetValue(color.MakeARGB(
				0,
				color.GetRed(),
				color.GetGreen(),
				color.GetBlue()));
			m_pBitmap->SetPixel(iColumn, m_iRow, colorTemp);

			Vec2 vPos = Get_Pos();

			vPos.x -= float(m_pBitmap->GetWidth() / 2);
			vPos.y -= float(m_pBitmap->GetHeight() / 2);

			vPos.x += float(iColumn);
			vPos.y += float(m_iRow);
			if (0 < colorTemp.GetB() || 0 < colorTemp.GetR() || 0 < colorTemp.GetG())
			{
				if(iColumn % 3 == 0)
					CreateParticle(vPos);
			}

		}
		
	}
	

	
}

void CLaserImage::Render(HDC _dc)
{
	INT iSlice = m_pBitmap->GetWidth();
	INT iHeight = m_pBitmap->GetHeight();
	

	//============vPos 세팅==============
	Vec2 vPos = Get_Pos();

	vPos += m_tAnimFrm.vOffSet; // OffSet만큼 추가로 이동시키고 출력
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);

	//======================================


	Graphics g(_dc);

	/*ImageAttributes imgAttr;
	ColorMatrix* pColorMatrix = m_colorMatrix;

	imgAttr.SetColorKey(Color(0, 0, 0), Color(0, 0, 0), ColorAdjustTypeBitmap);
	imgAttr.SetColorMatrix(pColorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);*/


	float fRatio = Get_Ratio();

	int LTX = (int)(vPos.x - iSlice * fRatio / 2.f);
	int LTY = (int)(vPos.y - iHeight * fRatio / 2.f);
	int RBX = (int)(vPos.x + iSlice * fRatio / 2.f);
	int RBY = (int)(vPos.y + iHeight * fRatio / 2.f);

	Point LTpoint, RTpoint, LBpoint;


	if (0 <= Get_Dir().x)
	{
		LTpoint = Point(LTX, LTY);
		RTpoint = Point(RBX, LTY);
		LBpoint = Point(LTX, RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(m_pBitmap
			, destinationPoints, 3
			, (int)m_tAnimFrm.vLT.x
			, (int)m_tAnimFrm.vLT.y
			, (int)iSlice
			, (int)iHeight
			, UnitPixel, NULL, NULL, NULL);
	}
	else
	{

		LTpoint = Point(LTX + (int)(iSlice * fRatio), LTY);
		RTpoint = Point(LTX - (RBX - LTX) + (int)(iSlice * fRatio), LTY);
		LBpoint = Point(LTX + (int)(iSlice * fRatio), RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(m_pBitmap
			, destinationPoints, 3
			, (int)m_tAnimFrm.vLT.x
			, (int)m_tAnimFrm.vLT.y
			, (int)iSlice
			, (int)iHeight
			, UnitPixel, NULL, NULL, NULL);
	}

}

void CLaserImage::CreateParticle(Vec2 _vPos)
{
	CAbstractFactory<CEffects_Particle>::Create_Effects(_vPos, GROUP_TYPE::EFFECTS);
}

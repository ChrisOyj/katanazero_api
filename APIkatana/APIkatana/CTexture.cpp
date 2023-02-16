#include "stdafx.h"
#include "CTexture.h"

#include "CMainGame.h"

ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;

CTexture::CTexture()
	: m_Image(nullptr)
{
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

}

CTexture::~CTexture()
{
	//DeleteDC(m_dc);

	/*if (nullptr != m_Image)
		delete m_Image;*/
}

void CTexture::Load(const wstring & _strFilePath)
{
	m_Image = Image::FromFile(_strFilePath.c_str());
	assert(m_Image);

	//m_dc = CreateCompatibleDC(CMainGame::Get_Instance()->Get_MainDC());
}
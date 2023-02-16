#pragma once
#include "CRes.h"

class CTexture :
	public CRes
{
private:
	CTexture();
	~CTexture() override;

public:
	void Load(const wstring& _strFilePath);

	float Width() { return (float)m_Image->GetWidth(); }
	float Height() { return (float)m_Image->GetHeight(); }

	//HDC Get_HDC() { return m_dc; }
	Image* Get_Image() { return m_Image; }

private:
//	HDC			m_dc;
	Image*		m_Image;


	friend class CResMgr; // 리소스 매니저에게만 오픈
};


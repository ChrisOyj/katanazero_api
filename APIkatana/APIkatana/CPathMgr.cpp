#include "stdafx.h"
#include "CPathMgr.h"


CPathMgr::CPathMgr()
	:m_szContentPath{}
{}

CPathMgr::~CPathMgr()
{}

void CPathMgr::Initialize()
{
	GetCurrentDirectory(255, m_szContentPath); // 현재 경로가 채워짐

	int iLen = (int)wcslen(m_szContentPath);

	// 상위 폴더로

	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}

	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

}

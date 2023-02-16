#include "stdafx.h"
#include "CResMgr.h"

#include "CPathMgr.h"

#include "CTexture.h"


CResMgr::CResMgr()
{}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

CTexture * CResMgr::LoadTexture(const wstring & _key, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_key);
	if (nullptr != pTex)
	{
		return pTex;
	}

	wstring strFilePath = CPathMgr::Get_Instance()->Get_ContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	pTex->SetKey(_key);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_key, pTex));

	return pTex;
}


CTexture * CResMgr::FindTexture(const wstring & _key)
{
	map <wstring, CRes*>::iterator iter = m_mapTex.find(_key);

	if (m_mapTex.end() == iter)
		return nullptr;
	else
		return (CTexture*)iter->second;


}

#pragma once

class CRes;
class CTexture;

//멤버로 모든 리소스를 가지고 있을 것임
class CResMgr
{
	SINGLE(CResMgr);

public:
	CTexture*			LoadTexture(const wstring& _key, const wstring& _strRelativePath);
	CTexture*			FindTexture(const wstring& _key);


	

private:
	map <wstring, CRes*> m_mapTex;
};


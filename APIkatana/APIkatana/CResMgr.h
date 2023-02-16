#pragma once

class CRes;
class CTexture;

//����� ��� ���ҽ��� ������ ���� ����
class CResMgr
{
	SINGLE(CResMgr);

public:
	CTexture*			LoadTexture(const wstring& _key, const wstring& _strRelativePath);
	CTexture*			FindTexture(const wstring& _key);


	

private:
	map <wstring, CRes*> m_mapTex;
};


#pragma once

class CRes abstract
{
public:
	CRes();
	virtual ~CRes();

private:
	wstring m_strKey;				// 리소스 키
	wstring m_strRelativePath;		// 리소스 상대 경로

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& Get_Key() { return m_strKey; }
	const wstring& Get_RelativePath() { return m_strRelativePath; }



};


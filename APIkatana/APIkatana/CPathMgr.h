#pragma once
class CPathMgr
{
	SINGLE(CPathMgr)

public:
	void			Initialize();
	const wchar_t*	Get_ContentPath() { return m_szContentPath; }

private:
	wchar_t			m_szContentPath[255]; // ��δ� 255���� ����
};


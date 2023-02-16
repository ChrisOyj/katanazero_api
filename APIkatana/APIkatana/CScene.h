#pragma once

class CObj;

class CScene abstract
{
public:
	CScene();
	virtual ~CScene();



public:
	const vector<CObj*>&		Get_GroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	const wstring&				Get_Name() { return m_strName; }
	CObj*						Get_Player() { return m_arrObj[(UINT)GROUP_TYPE::PLAYER].front(); }

	void						SetName(const wstring& _strName) { m_strName = _strName; }

public:
	virtual void				Update();
	void						Final_Update();
	virtual void				Render(HDC _dc);

	virtual void				Enter(bool _bReplay = false) PURE;
	virtual void				Exit() PURE;


public:
	void						AddObject(CObj* _pObj, GROUP_TYPE _eType);
	void						DeleteGroup(GROUP_TYPE _eType);
	void						DeleteAll();
	void						DeleteEventAll();

protected:
	void						Debuger_Render(HDC _dc);



private:
	vector <CObj*>				m_arrObj[(UINT)GROUP_TYPE::END];
	wstring						m_strName;
	bool						m_bColliderVisible;

};


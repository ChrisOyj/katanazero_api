#pragma once
#include "CObj.h"

class CTile
	: public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }

public:
	void		Initialize();
	void		Update();
	void		Render(HDC _dc);

private:
	int		m_iDrawID; // �̰� ���� ����� ���ؼ� Ÿ�� �ѱ�� ���
	int		m_iOption;
};


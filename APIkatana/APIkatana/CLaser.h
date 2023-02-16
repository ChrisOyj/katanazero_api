#pragma once
#include "CObj.h"

class CLaser
	: public CObj
{
public:
	CLaser();
	~CLaser() override;

	CLONE(CLaser);

public:
	void OnCollisionEnter(CCollider* _pOther) override;

	void Update() override;
	void Render(HDC _dc) override;



public:
	void SetLength(int _iLen) { m_iLength = _iLen; }

private:
	int	m_iLength;
	int m_RenderY;


};


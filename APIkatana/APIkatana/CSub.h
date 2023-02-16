#pragma once
#include "CObj.h"

class CSub
	: public CObj
{
public:
	CSub();
	virtual ~CSub();

	CLONE(CSub);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render(HDC _dc);

protected:
	void		CreateAfterImage();


private:
	float	m_fSpeed;
};


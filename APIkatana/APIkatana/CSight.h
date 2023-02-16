#pragma once
#include "CObj.h"

class CSight :
	public CObj
{
public:
	CSight();
	virtual ~CSight();

	CLONE(CSight);

public:
	void		Set_Offset(float f) { m_fOffset = f; }


	void OnCollision(CCollider* _pOther) override;
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;

public:
	void	Initialize();
	void	Update() override;
	void	Render(HDC _dc) override;

private:
	float	m_fOffset;




};




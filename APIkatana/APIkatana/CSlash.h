#pragma once
#include "CObj.h"

class CPlayer;

class CSlash :
	public CObj
{
public:
	CSlash();
	~CSlash() override;
	CLONE(CSlash);

public:
	void OnCollisionEnter(CCollider* _pOther) override;

	void SetSubType(SUB_TYPE _e) { m_eSubType = _e; }


public:
	void	Initialize() override;
	void Update() override;
	void Render(HDC _dc) override;

private:
	void CreateAfterImage();



private:
	SUB_TYPE	m_eSubType;

};


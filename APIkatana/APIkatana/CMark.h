#pragma once
#include "CObj.h"


class CMark :
	public CObj
{
public:
	CMark();
	~CMark() override;

public:
	void SetMarkType(MARK_TYPE _eType) { m_eType = _eType; }

public:
	void		Initialize() override;
	void Update() override;
	void Render(HDC _dc) override;

	CLONE(CMark);
	
private:
	void Update_arm();
	void CreateBullet();

private:

	MARK_TYPE m_eType;



};



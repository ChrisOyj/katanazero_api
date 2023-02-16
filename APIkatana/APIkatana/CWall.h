#pragma once
#include "CObj.h"

class CTexture;

class CWall :
	public CObj
{
public:
	CWall();
	~CWall() override;

public:
	void	SetScale(Vec2 _vScale) override;
	void SetWallRight() { m_bWallLeft = false; }
	void SetClimbTrue() { m_bClimb = true; }
	bool IsClimbTrue() { return m_bClimb; }
	bool IsWallLeft() { return m_bWallLeft; }

public:
	void Update() override;
	void Render(HDC _dc) override;

	CLONE(CWall);

public:
	void OnCollision(CCollider* _pOther) override;

private:
	bool m_bWallLeft;
	bool m_bClimb;

};


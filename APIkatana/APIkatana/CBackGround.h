#pragma once
#include "CObj.h"

class CBackGround :
	public CObj
{
public:
	CBackGround();
	virtual ~CBackGround();

	CLONE(CBackGround);

public:
	void	SetDark()
	{
		*m_colorMatrix = {
		   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}

	void	SetNormal()
	{
		*m_colorMatrix = {
		   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 0.0f, 1.0f };
	}

	void	SetWhite()
	{
		m_bWhite = true;

		*m_colorMatrix = {
		   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		   1.0f, 1.0f, 1.0f, 0.0f, 1.0f };
	}

public:
	void Update() {};
	void Initialize() override;

protected:
	bool		m_bWhite = false;
	float		m_fWhite = 1.f;
};



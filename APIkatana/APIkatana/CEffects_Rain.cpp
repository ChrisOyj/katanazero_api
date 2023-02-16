#include "stdafx.h"
#include "CEffects_Rain.h"

CEffects_Rain::CEffects_Rain()
{
}

CEffects_Rain::~CEffects_Rain()
{
}

void CEffects_Rain::Initialize()
{
	int iRand = random(20, 40);
	SetDir(Vec2(0.f, 1.f));
	SetScale(Vec2((float)iRand, 2.f));
	m_tInfo.iAlpha = 190;
	m_fSpeed = 3000.f;
	m_tInfo.RGB[0] = 0;
	m_tInfo.RGB[1] = 0;
	m_tInfo.RGB[2] = 0;
	m_fTheta = PI*0.5f;
}

void CEffects_Rain::Update()
{
	if (380.f < m_vPos.y)
	{
		DeleteObject(this);
	}

	Effects_Move();
}

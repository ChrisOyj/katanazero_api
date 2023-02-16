#include "stdafx.h"
#include "CEffects_Electric.h"

CEffects_Electric::CEffects_Electric()
{
}

CEffects_Electric::~CEffects_Electric()
{
}

void CEffects_Electric::Initialize()
{
	int iRand = random(10, 15);
	SetScale(Vec2(float(iRand), 1.f));

	m_vDir = randomdir();

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

	m_tInfo.fFadeSpeed = 700.f;
	m_tInfo.iAlpha = 255;
	m_fSpeed = 200.f;
	m_tInfo.RGB[0] = 0;
	m_tInfo.RGB[1] = 200;
	m_tInfo.RGB[2] = 255;
}

void CEffects_Electric::Update()
{
	Effects_FadeOut(true);
	Effects_Move(true);
}

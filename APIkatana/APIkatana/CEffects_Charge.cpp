#include "stdafx.h"
#include "CEffects_Charge.h"

CEffects_Charge::CEffects_Charge()
{
}

CEffects_Charge::~CEffects_Charge()
{
}

void CEffects_Charge::Initialize()
{
	int iRand = random(50, 70);
	int iRand2 = random(1, 3);
	SetScale(Vec2(float(iRand), (float)iRand2));

	m_vDir = randomdir();

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

	m_vPos.x += 150.f * m_vDir.x;
	m_vPos.y += 150.f * m_vDir.y;

	m_vDir.x *= -1.f;
	m_vDir.y *= -1.f;

	m_tInfo.fFadeSpeed = 700.f;
	m_tInfo.iAlpha = 230;
	m_fSpeed = 450.f;

	int iRand3 = random(50, 255);
	m_tInfo.RGB[0] = iRand3;
	m_tInfo.RGB[1] = 10;
	m_tInfo.RGB[2] = 0;
}

void CEffects_Charge::Update()
{
	Effects_FadeOut(false);
	Effects_Move(false);
}

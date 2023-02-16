#include "stdafx.h"
#include "CEffects_Particle.h"

#include "CTimeMgr.h"

CEffects_Particle::CEffects_Particle()
{
}

CEffects_Particle::~CEffects_Particle()
{
}

void CEffects_Particle::Initialize()
{
	float fx = (float)random(-10, 10) * 1.f;
	float fy = (float)random(1, 10) * -1.f;

	Vec2 vDir = { fx, fy };
	SetDir(vDir);

	if (0.f == fx)
		fx = 1.f;

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

	float sizeRand = (float)random(1, 3);
	m_vScale = Vec2(sizeRand, sizeRand);

	float sRand = (float)random(200, 400);
	m_tPhysics.fXSpeed = sRand;

	float fRand = (float)random(300, 1000);
	m_tInfo.fFadeSpeed = fRand;
	m_tInfo.iAlpha = 255;

	int iRand = random(100, 240);
	int iRand2 = random(0, 50);

	m_tInfo.RGB[0] = 250;
	m_tInfo.RGB[1] = iRand;
	m_tInfo.RGB[2] = iRand2;

	float jRand = (float)random(10, 50);
	JUMP(jRand);
}

void CEffects_Particle::Update()
{
	Effects_FadeOut();

	m_vPos.x += m_tPhysics.fXSpeed * m_vDir.x * fDT;
	m_vPos.y += m_tPhysics.fXSpeed * m_vDir.y * fDT;

	float fY = 0.f;
	/*if (m_fTime < 0.5f)
		bLineCol = false;*/

	
	{
		m_tPhysics.fAcc += fDT * 9.5f;

		m_vPos.y = m_tPhysics.fOriginY - ((m_tPhysics.fYSpeed * m_tPhysics.fAcc) - (9.8f * 0.5f * m_tPhysics.fAcc * m_tPhysics.fAcc));
		m_fTheta += 10.f * fDT;

		if (0.f < m_tPhysics.fXSpeed) // 속도가 존재하면
			m_tPhysics.fXSpeed -= m_tPhysics.fAirFric * fDT; // 속도는 m_fAirFric만큼 감소
		else
			m_tPhysics.fXSpeed = 0.f;

	}
}

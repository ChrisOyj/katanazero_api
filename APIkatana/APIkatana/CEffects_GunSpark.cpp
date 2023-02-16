#include "stdafx.h"
#include "CEffects_GunSpark.h"

CEffects_GunSpark::CEffects_GunSpark()
{
}

CEffects_GunSpark::~CEffects_GunSpark()
{
}

void CEffects_GunSpark::Initialize()
{
	Set_Texture(L"Effects_GunSpark", 8, 0.06f, EFFECT_TYPE::GUNSPARK);

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

}

void CEffects_GunSpark::Update()
{
	Effects_Time();

}

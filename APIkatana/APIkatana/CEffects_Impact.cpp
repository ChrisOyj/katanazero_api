#include "stdafx.h"
#include "CEffects_Impact.h"

CEffects_Impact::CEffects_Impact()
{
}

CEffects_Impact::~CEffects_Impact()
{
}

void CEffects_Impact::Initialize()
{
	Set_Texture(L"Effects_Impact", 6, 0.07f, EFFECT_TYPE::IMPACT);

	*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.1f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, 0.9f, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;
}

void CEffects_Impact::Update()
{
	Effects_Time(true);
}

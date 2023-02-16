#include "stdafx.h"
#include "CEffects_Cut.h"

CEffects_Cut::CEffects_Cut()
{
}

CEffects_Cut::~CEffects_Cut()
{
}

void CEffects_Cut::Initialize()
{
	Set_Texture(L"Effects_Cut", 5, 0.07f, EFFECT_TYPE::CUT);

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

void CEffects_Cut::Update()
{
	Effects_Time(true);
}

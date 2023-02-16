#include "stdafx.h"
#include "CEffects_Blood.h"

CEffects_Blood::CEffects_Blood()
{
}

CEffects_Blood::~CEffects_Blood()
{
}
void CEffects_Blood::Initialize()
{
	int iRand = random(0, 1);

	if (iRand == 0)
	{
		Set_Texture(L"Effects_Blood", 6, 0.06f, EFFECT_TYPE::BLOOD);
	}
	else
		Set_Texture(L"Effects_Blood3", 6, 0.06f, EFFECT_TYPE::BLOOD);

	*m_colorMatrix = {
		 0.9f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.1f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.1f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, 0.6f, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

}

void CEffects_Blood::Update()
{
	Effects_Time();
	Effects_Move();
	
}

#include "stdafx.h"
#include "CEffects_Dust.h"

CEffects_Dust::CEffects_Dust()
{
}

CEffects_Dust::~CEffects_Dust()
{
}

void CEffects_Dust::Initialize()
{
	Set_Texture(L"Effects_Dust", 7, 0.06f, EFFECT_TYPE::DUST);

	CAnimation* pAnim = Get_Animator()->FindAnimation(L"Effects_Dust");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 16.f);

	if (m_vDir.y == 0)
	{
		float fy = (float)random(-7, 1);
		m_vDir.x *= -10.f;
		m_vDir.y = fy;
		m_vDir.Normalize();
	}

	m_fSpeed = 100.f;

	*m_colorMatrix = {
		 0.8f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.8f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.9f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		 0.2f, 0.2f, 0.2f, 0.0f, 1.f };
}

void CEffects_Dust::Update()
{
	Effects_Time();
	Effects_Move();
}

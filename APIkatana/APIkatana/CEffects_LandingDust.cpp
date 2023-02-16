#include "stdafx.h"
#include "CEffects_LandingDust.h"

CEffects_LandingDust::CEffects_LandingDust()
{
}

CEffects_LandingDust::~CEffects_LandingDust()
{
}

void CEffects_LandingDust::Initialize()
{
	Set_Texture(L"Effects_LandingDust", 7, 0.05f, EFFECT_TYPE::LANDINGDUST);

	CAnimation* pAnim = Get_Animator()->FindAnimation(L"Effects_LandingDust");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 10.f);

	m_vDir = Vec2(1.f, 0.f);
}

void CEffects_LandingDust::Update()
{
	Effects_Time();

}

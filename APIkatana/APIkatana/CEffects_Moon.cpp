#include "stdafx.h"
#include "CEffects_Moon.h"

CEffects_Moon::CEffects_Moon()
{
}

CEffects_Moon::~CEffects_Moon()
{
}

void CEffects_Moon::Initialize()
{
	Set_Texture(L"Effects_Moon", 1, 0.05f, EFFECT_TYPE::LANDINGDUST);

	m_fTimeLimit = 1.f;
}

void CEffects_Moon::Update()
{
	Effects_Time();
}

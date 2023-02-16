#include "stdafx.h"
#include "CEffects_JumpDust.h"

CEffects_JumpDust::CEffects_JumpDust()
{
}

CEffects_JumpDust::~CEffects_JumpDust()
{
}

void CEffects_JumpDust::Initialize()
{
	Set_Texture(L"Effects_JumpDust", 4, 0.05f, EFFECT_TYPE::JUMPDUST);

	CAnimation* pAnim = Get_Animator()->FindAnimation(L"Effects_JumpDust");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -6.f);
}

void CEffects_JumpDust::Update()
{
	Effects_Time();
}


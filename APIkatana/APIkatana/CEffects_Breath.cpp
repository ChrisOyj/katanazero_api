#include "stdafx.h"
#include "CEffects_Breath.h"

CEffects_Breath::CEffects_Breath()
{
}

CEffects_Breath::~CEffects_Breath()
{
}

void CEffects_Breath::Initialize()
{
	Set_Texture(L"Effects_Breath", 13, 0.05f, EFFECT_TYPE::DUST);

	//CAnimation* pAnim = Get_Animator()->FindAnimation(L"Effects_Breath");
	//for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
	//	pAnim->Get_Frame(i).vOffSet = Vec2(0.f, 16.f);

	m_vDir.x *= -1.f;

	m_fSpeed = 50.f;

	*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		 0.2f, 0.2f, 0.2f, 0.0f, 1.f };
}

void CEffects_Breath::Update()
{
	Effects_Time();
	Effects_Move();
}

void CEffects_Breath::Render(HDC _dc)
{
	m_pAnimator->dir_Render(_dc, Color(255,255,255), Color(255, 255, 255));

}

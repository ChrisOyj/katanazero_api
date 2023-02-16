#include "stdafx.h"
#include "CEffects_Go.h"

#include "CCamera.h"

CEffects_Go::CEffects_Go()
{
}

CEffects_Go::~CEffects_Go()
{
}

void CEffects_Go::Initialize()
{
	Set_Texture(L"UI_Go", 1, 0.05f, EFFECT_TYPE::GO);

	m_fSpeed = 30.f;
	m_tInfo.fAlpha = 0.f;
	m_tInfo.bColorPlus = true;

}

void CEffects_Go::Update()
{
	*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, m_tInfo.fAlpha, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	if (1.f <= m_tInfo.fAlpha)
	{
		m_tInfo.bColorPlus = false;
		m_tInfo.fAlpha = 1.f;
	}
	if (0.f >= m_tInfo.fAlpha)
	{
		m_tInfo.bColorPlus = true;
		m_tInfo.fAlpha = 0.f;
	}

	if (m_tInfo.bColorPlus)
		m_tInfo.fAlpha += 2.f * fDT;
	else
		m_tInfo.fAlpha -= 2.f * fDT;
}

void CEffects_Go::Render(HDC _dc)
{
	Vec2 vTemp = m_vPos;
	Vec2 vRenderPos = CCamera::Get_Instance()->Get_RenderPos(m_vPos);
	
	if (vRenderPos.x > WINCX)
		vRenderPos.x = WINCX - 30;

	if (vRenderPos.x < 0)
		vRenderPos.x = 30.f;

	if (vRenderPos.y > WINCY)
		vRenderPos.y = WINCY - 30;

	if (vRenderPos.y < 0)
		vRenderPos.y = 30.f;

	m_vPos = CCamera::Get_Instance()->Get_RealPos(vRenderPos);
	m_pAnimator->Render(_dc, Color(255, 255, 255), Color(255, 255, 255));
	m_vPos = vTemp;
}

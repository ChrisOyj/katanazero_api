#include "stdafx.h"
#include "CEffects_PickUp.h"

CEffects_PickUp::CEffects_PickUp()
{
}

CEffects_PickUp::~CEffects_PickUp()
{
}

void CEffects_PickUp::Initialize()
{
	Set_Texture(L"Effects_PickUp", 8, 0.05f, EFFECT_TYPE::PICKUP);

	m_fSpeed = 20.f;
	m_tInfo.fAlpha = 0.f;
}

void CEffects_PickUp::Update()
{
	*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, m_tInfo.fAlpha, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	m_fTime += fDT;

	if (0.5f > m_fTime)
		m_vPos.y -= m_fSpeed * fDT;
	else
		m_vPos.y += m_fSpeed * fDT;

	if (1.f < m_fTime)
		m_fTime = 0.f;

	if (!m_tInfo.bDelete)
	{
		if (1.f > m_tInfo.fAlpha)
			m_tInfo.fAlpha += fDT;
		else
			m_tInfo.fAlpha = 1.f;
	}
	else
	{
		m_tInfo.fAlpha -= fDT;
		if (0.15 > m_tInfo.fAlpha)
		{
			DeleteObject(this);
		}
	}
}

#include "stdafx.h"
#include "CEffects_PompSlash.h"

CEffects_PompSlash::CEffects_PompSlash()
{
}

CEffects_PompSlash::~CEffects_PompSlash()
{
}

void CEffects_PompSlash::Initialize()
{
	CreateCollider();
	float fWidth = 50.f;
	float fHeight = 20.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));

	Set_Texture(L"Effects_PompSlash", 5, 0.04f, EFFECT_TYPE::POMP_SLASH);

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;
}

void CEffects_PompSlash::Update()
{
	Vec2 vPos = Get_Owner()->Get_Pos();
	vPos.x += 15.f * Get_Dir().x;
	vPos.y -= 12.f;
	SetPos(vPos);

	Effects_Time();
}

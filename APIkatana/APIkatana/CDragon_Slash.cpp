#include "stdafx.h"
#include "CDragon_Slash.h"

#include "CAfterImage.h"

CDragon_Slash::CDragon_Slash()
{
}

CDragon_Slash::~CDragon_Slash()
{
}

void CDragon_Slash::Initialize()
{
	CreateCollider();
	float fWidth = 90.f;
	float fHeight = 40.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));
	Set_Texture(L"Effects_Slash_dragon", 5, 0.04f, EFFECT_TYPE::SLASH);

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

	*m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,   0.2f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f,  0.2f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}

void CDragon_Slash::Update()
{
	Vec2 vPos = Get_Owner()->Get_Pos();

	SetPos(vPos);

	Effects_Time();
}

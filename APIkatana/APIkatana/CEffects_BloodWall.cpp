#include "stdafx.h"
#include "CEffects_BloodWall.h"

#include "CSceneMgr.h"

CEffects_BloodWall::CEffects_BloodWall()
{
}

CEffects_BloodWall::~CEffects_BloodWall()
{
}

void CEffects_BloodWall::SetColorMatrix(ColorMatrix cm)
{
	m_tInfo.fAlpha = 0.f;
}

void CEffects_BloodWall::Initialize()
{
	m_vPos.x += 100.f * m_vDir.x;
	m_vPos.y += 100.f * m_vDir.y;

	int iRand = random(0, 2);

	switch (iRand)
	{
	case 0:
		Set_Texture(L"Effects_BloodWall5", 1, 0.06f, EFFECT_TYPE::BLOODWALL);
		break;

	default:
		Set_Texture(L"Effects_BloodWall4", 1, 0.06f, EFFECT_TYPE::BLOODWALL);

		break;
	}

	Vec2 vDir = Get_Dir();

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0.f)
		m_fTheta *= -1.f;

	

	//if (-0.9f < vDir.y && -0.2f > vDir.y) // y값이 -0.8 ~ -0.2 일 때만
	if ((fabs(m_fTheta) > 0.3f && fabs(m_fTheta) < 1.3f) || (fabs(m_fTheta) > 2.1f && fabs(m_fTheta) < 2.9f))
	{
		switch (iRand)
		{
		case 0:
			Set_Texture(L"Effects_BloodWall", 1, 0.06f, EFFECT_TYPE::BLOODWALL);

			break;

		case 1:
			Set_Texture(L"Effects_BloodWall2", 1, 0.06f, EFFECT_TYPE::BLOODWALL);

			break;

		default:
			Set_Texture(L"Effects_BloodWall3", 1, 0.06f, EFFECT_TYPE::BLOODWALL);

			break;
		}

		if (0 > vDir.x)
		{
			//vDir.x = -1.f;
			//vDir.y = 0.f;

			m_fTheta = -1.6f;

			if (vDir.y > 0.f)
				m_fTheta = PI;

		}
		else
		{
			//vDir.y = 0.f;
			//vDir.x = 1.f;
			m_fTheta = 0.f;

			if (vDir.y > 0.f)
				m_fTheta = 1.6f;

		}


		//SetDir(vDir);

		/*m_fTheta = acosf(m_vDir.x);

		if (m_vDir.y < 0.f)
			m_fTheta *= -1.f;*/
	}

	m_tInfo.fAlpha = 0.7f;
	m_tInfo.fFadeSpeed = 0.1f;


	*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, 0.7f, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };
}

void CEffects_BloodWall::Update()
{
	/*if (CSceneMgr::Get_Instance()->Get_CurSceneType() == SCENE_TYPE::STAGE_03)
		return;*/

	Effects_FadeOut();
}

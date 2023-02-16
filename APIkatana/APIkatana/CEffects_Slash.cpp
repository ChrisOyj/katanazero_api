#include "stdafx.h"
#include "CEffects_Slash.h"

#include "CAfterImage.h"

CEffects_Slash::CEffects_Slash()
{
}

CEffects_Slash::~CEffects_Slash()
{
}

void CEffects_Slash::Initialize()
{
	CreateCollider();
	float fWidth = 90.f;
	float fHeight = 40.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));
	Set_Texture(L"Effects_Slash", 5, 0.04f, EFFECT_TYPE::SLASH);

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

	//m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,   1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	if (g_bLaser)
		*m_colorMatrix = {
			 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,   1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f,  0.2f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.9f, 0.5f, 0.0f, 0.0f, 1.0f };
}

void CEffects_Slash::Update()
{
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		*m_colorMatrix = {
			 0.8f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,   1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f,  0.7f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		m_fAcc += RealfDT;

		if (m_fAcc > 0.016f)
		{
			CreateAfterImage();
			m_fAcc = 0.f;
		}
	}


	Vec2 vPos = Get_Owner()->Get_Pos();

	SetPos(vPos);

	Effects_Time();
}

void CEffects_Slash::CreateAfterImage()
{
	float fAlphaCount = 5.f;
	float fAfterColor[3];
	fAfterColor[0] = 0.0f;
	fAfterColor[1] = 0.5f;
	fAfterColor[2] = 0.0f;

	CAfterImage* pImage = new CAfterImage;

	pImage->SetAnim(*Get_Animator()->Get_CurAnim());
	pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
	//pImage->SetDir(Get_Dir());
	pImage->SetTheta(m_fTheta);
	pImage->SetColor(0.5f);
	pImage->Set_RGB(fAfterColor);

	pImage->SetAlphaCount(fAlphaCount); // 낮게 설정할 수록 잔상이 오래 남음

	pImage->SetPos(Get_Pos());
	CreateObject(pImage, GROUP_TYPE::EFFECTS);
}

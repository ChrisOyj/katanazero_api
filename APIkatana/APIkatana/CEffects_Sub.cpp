#include "stdafx.h"
#include "CEffects_Sub.h"

CEffects_Sub::CEffects_Sub()
{
}

CEffects_Sub::~CEffects_Sub()
{
}

void CEffects_Sub::Initialize()
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	switch (m_eSubType)
	{
	case SUB_TYPE::KNIFE:
		pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_knife", L"texture\\UI\\UI_knife.png");
		iCount = 1;
		fSize = pTex->Width() / (float)iCount;
		Get_Animator()->CreateAnimation(L"UI_knife", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);
		m_pAnimator->Play(L"UI_knife", false);
		break;

	case SUB_TYPE::BOTTLE:
		pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_Bottle", L"texture\\UI\\UI_Bottle.png");
		iCount = 1;
		fSize = pTex->Width() / (float)iCount;
		Get_Animator()->CreateAnimation(L"UI_Bottle", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);
		m_pAnimator->Play(L"UI_Bottle", false);
		break;

	case SUB_TYPE::BEER:
		pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_Beer", L"texture\\UI\\UI_Beer.png");
		iCount = 1;
		fSize = pTex->Width() / (float)iCount;
		Get_Animator()->CreateAnimation(L"UI_Beer", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);
		m_pAnimator->Play(L"UI_Beer", false);
		break;

	case SUB_TYPE::SMOKE:
		pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_Smoke", L"texture\\UI\\UI_Smoke.png");
		iCount = 1;
		fSize = pTex->Width() / (float)iCount;
		Get_Animator()->CreateAnimation(L"UI_Smoke", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);
		m_pAnimator->Play(L"UI_Smoke", false);
		break;
	}
	
	m_tInfo.fAlpha = 1.f;
	

}

void CEffects_Sub::Update()
{
	m_vPos = m_pOwner->Get_Pos();
	m_vPos.y -= 40.f;

	m_fAcc += RealfDT;

	if (m_fAcc > 0.5f)
	{
		m_fTime += RealfDT;

		if (0.08f < m_fTime)
		{
			m_fTime = 0.f;

			if (m_tInfo.fAlpha == 1.f)
				m_tInfo.fAlpha = 0.f;
			else
				m_tInfo.fAlpha = 1.f;
		}

	}

	if (m_fAcc > 1.1f)
		DeleteObject(this);

	*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, m_tInfo.fAlpha, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };

}

#include "stdafx.h"
#include "CEffects_Tex.h"

#include "CAnimator.h"
#include "CTimeMgr.h"

CEffects_Tex::CEffects_Tex()
{
	CreateAnimator();
	CreateColorMatrix();
}

CEffects_Tex::~CEffects_Tex()
{
}

void CEffects_Tex::Set_Texture(const TCHAR * _strName, UINT _iCount, float _fDuration, EFFECT_TYPE _eType)
{
	wstring strPath = L"texture\\Effects\\";
	strPath += _strName;
	strPath += L".png";
	wstring strKey = _strName;
	CTexture* pTex = nullptr;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(strKey, strPath.c_str());

	fSize = pTex->Width() / (float)_iCount;
	m_pAnimator->CreateAnimation(strKey, pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), _fDuration, _iCount);

	m_eEffectType = _eType;

	m_fSpeed = 10.f;

	m_pAnimator->Play(strKey, false);
	m_fTimeLimit = m_pAnimator->Get_CurAnim()->Get_MaxTime();

}

void CEffects_Tex::Effects_Time(bool _bRealDT)
{
	if (_bRealDT)
		m_fTime += RealfDT;
	else
		m_fTime += fDT;

	if (m_fTimeLimit <= m_fTime)
	{
		DeleteObject(this);
	}

	if (_bRealDT)
		Get_Animator()->speed_Update();
	else
		Get_Animator()->Update();

}


void CEffects_Tex::Effects_FadeOut()
{
	m_tInfo.fAlpha -= m_tInfo.fFadeSpeed * fDT;

	if (0.1f > m_tInfo.fAlpha)
	{
		DeleteObject(this);
	}

	*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f, m_tInfo.fAlpha, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };
}

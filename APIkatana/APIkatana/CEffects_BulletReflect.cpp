#include "stdafx.h"
#include "CEffects_BulletReflect.h"

#include "CAbstractFactory.h"
#include "CEffects_Electric.h"

CEffects_BulletReflect::CEffects_BulletReflect()
{
}

CEffects_BulletReflect::~CEffects_BulletReflect()
{
}

void CEffects_BulletReflect::Initialize()
{
	Set_Texture(L"Effects_BulletReflect", 5, 0.07f, EFFECT_TYPE::BULLETREFLECT);

}

void CEffects_BulletReflect::Update()
{
	Effects_Time();

	if (m_fTimeLimit * 0.2f >= m_fTime)
	{
		CObj* pElectric = CAbstractFactory<CEffects_Electric>::Create();
		dynamic_cast<CEffects*>(pElectric)->Set_RGB(255, 240, 0);
		pElectric->SetPos(m_vPos);
		CreateObject(pElectric, GROUP_TYPE::EFFECTS);
	}
}

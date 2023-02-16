#include "stdafx.h"
#include "CBG_Boss.h"

#include "CTexture.h"
#include "CAnimator.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"

CBG_Boss::CBG_Boss()
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Map_Boss", L"texture\\map\\Map_Garage.bmp");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	m_vScale.x = pTex->Width();
	m_vScale.y = pTex->Height();
	Get_Animator()->CreateAnimation(L"Map_Boss", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	Get_Animator()->Play(L"Map_Boss", false);
}

CBG_Boss::~CBG_Boss()
{
}

void CBG_Boss::Update()
{
	if (m_bWhite)
	{
		m_fTime += RealfDT;

		if (2.f < m_fTime && CCamera::Get_Instance()->Get_Zoom() == 0.5f)
		{
			CCamera::Get_Instance()->SetZoom();
			CTimeMgr::Get_Instance()->SetTimeSpeed(0.4f);

		}


		if (3.f < m_fTime)
		{
			if (m_fWhite == 1.f)
			{
				CTimeMgr::Get_Instance()->SetTimeSpeed(1.f);

			}
			
			
			m_fWhite -= fDT;

			if (m_fWhite < 0.f)
			{
				m_fWhite = 0.f;
				m_bWhite = false;
			}
		}

		*m_colorMatrix = {
		   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		   m_fWhite, m_fWhite, m_fWhite, 0.0f, 1.0f };

		CObj* pPlayer = CSceneMgr::Get_Instance()->Get_CurScene()->Get_Player();
		CObj* pBoss = CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::MONSTER).front();
		vector<CObj*> arrEffects[4] = { CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::EFFECTS)
			, CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::GLASS)
			, CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::SUBWEAPON)
			, CSceneMgr::Get_Instance()->Get_CurScene()->Get_GroupObject(GROUP_TYPE::BLOOD) };

		float fBlack = 1.f - m_fWhite;

		ColorMatrix colorMatrix = {
		   fBlack, 0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f, fBlack, 0.0f, 0.0f, 0.0f,
		   0.0f, 0.0f, fBlack, 0.0f, 0.0f,
		   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		pPlayer->SetColorMatrix(colorMatrix);
		dynamic_cast<CPlayer*>(pPlayer)->SetAfter();
		pBoss->SetColorMatrix(colorMatrix);

		for (int j = 0; j < 4; ++j)
		{
			for (int i = 0; i < arrEffects[j].size(); ++i)
			{
				arrEffects[j][i]->SetColorMatrix(colorMatrix);
			}
		}
		
	}
}

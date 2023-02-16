#include "stdafx.h"
#include "CBG_Mansion_2.h"

#include "CTexture.h"
#include "CAnimator.h"

#include "CResMgr.h"

CBG_Mansion_2::CBG_Mansion_2()
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Map_Mansion2", L"texture\\map\\Map_Mansion2.bmp");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	m_vScale.x = pTex->Width();
	m_vScale.y = pTex->Height();
	Get_Animator()->CreateAnimation(L"Map_Mansion2", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	Get_Animator()->Play(L"Map_Mansion2", false);
}

CBG_Mansion_2::~CBG_Mansion_2()
{
}

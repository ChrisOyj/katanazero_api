#include "stdafx.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"

CTile::CTile()
{
}

CTile::~CTile()
{
}

void CTile::Initialize()
{
	CreateAnimator();

	CTexture* pTex = nullptr;
	float fSize;
	int iCount = 1;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Tile_Mansion", L"texture\\Tile\\Tile_Mansion");

	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Tile_Mansion", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 1.f, iCount);


	Get_Animator()->Play(L"Tile_Mansion", false);

}

void CTile::Update()
{
}

void CTile::Render(HDC _dc)
{


}

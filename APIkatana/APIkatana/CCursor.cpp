#include "stdafx.h"
#include "CCursor.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"

CCursor::CCursor()
{
	ShowCursor(false);

	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_cursor", L"texture\\Effects\\Effects_cursor.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Effects_cursor", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.03f, iCount);

	Get_Animator()->Play(L"Effects_cursor", false);


}

CCursor::~CCursor()
{
	ShowCursor(true);

}

void CCursor::Update()
{
	Vec2 vPos = CCamera::Get_Instance()->Get_RealPos(Get_MousePos());
	SetPos(vPos);
}

#include "stdafx.h"
#include "CSlash.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"
#include "CCollider.h"
#include "CAfterImage.h"

#include "CSubWeapon.h"

CSlash::CSlash()
	: m_eSubType(SUB_TYPE::END)
{
	CreateCollider();

	

	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_Slash", L"texture\\Effects\\Effects_Slash_5.png");
	iCount = 5;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Effects_Slash", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Knife", L"texture\\SubWeapon\\SubWeapon_Knife.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Knife", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	/*m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
		1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.5f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.8f, 0.0f, 0.0f, 1.0f };*/
	

}

CSlash::~CSlash()
{
}

void CSlash::OnCollisionEnter(CCollider * _pOther)
{
	if (m_eSubType == SUB_TYPE::KNIFE)
	{
		DeleteObject(this);

		Vec2 vPos = Get_Pos();
		vPos.y = 340.f;
		CSubWeapon* pSub = new CSubWeapon;
		pSub->SetPos(vPos);
		pSub->SetObjType(GROUP_TYPE::SUBWEAPON);
		pSub->SetSubType(SUB_TYPE::KNIFE);
		pSub->Initialize();
		CreateObject(pSub, GROUP_TYPE::SUBWEAPON);
	}
}

void CSlash::Initialize()
{
	switch (m_eSubType)
	{
	case SUB_TYPE::KNIFE:
	{
		Get_Animator()->Play(L"SubWeapon_Knife", false);
		float fWidth = 5.f;
		float fHeight = 5.f;
		Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜
		Get_Collider()->SetScale(Vec2(fWidth, fHeight));
	}

		break;
		
	default:
	{
		Get_Animator()->Play(L"Effects_Slash", false);
		float fWidth = 90.f;
		float fHeight = 20.f;
		Get_Collider()->SetOffSetPos(Vec2(0.f, 0.f));
		Get_Collider()->SetScale(Vec2(fWidth, fHeight));
	}
		

		break;

	}
}

void CSlash::Update()
{
	if (m_eSubType == SUB_TYPE::END)
	{
		Vec2 vPos = Get_Owner()->Get_Pos();

		SetPos(vPos);

		float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();
		m_fTime += fDT;

		if (TimeLimit <= m_fTime)
		{
			DeleteObject(this);
		}
	}
	else
	{
		CreateAfterImage();
		Vec2 vPos = Get_Pos();
		vPos.x += 1100.f * Get_Dir().x * fDT;
		vPos.y += 1100.f * Get_Dir().y * fDT;
		SetPos(vPos);
	}

	Get_Animator()->Update();
}



void CSlash::Render(HDC _dc)
{
	Get_Animator()->dir_Render(_dc);
	CObj::Component_dir_Render(_dc);
}

void CSlash::CreateAfterImage()
{
	float fAlphaCount = 10.f;

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() != 1.f) // 속도 느린 상태면
		fAlphaCount = 20.f;

	CAfterImage* pImage = new CAfterImage;

	pImage->SetAnim(*Get_Animator()->Get_CurAnim());
	pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
	pImage->SetDir(Get_Dir());
	pImage->SetRatio(0.5f);
	pImage->SetColor(0.5f);

	pImage->SetAlphaCount(fAlphaCount); // 낮게 설정할 수록 잔상이 오래 남음

	pImage->SetPos(Get_Pos());
	CreateObject(pImage, GROUP_TYPE::EFFECTS);
}

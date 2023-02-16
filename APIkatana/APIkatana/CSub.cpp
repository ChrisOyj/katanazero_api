#include "stdafx.h"
#include "CSub.h"

#include "CAnimator.h"
#include "CTimeMgr.h"

#include "CAfterImage.h"

CSub::CSub()
{
}

CSub::~CSub()
{
}

void CSub::OnCollisionEnter(CCollider * _pOther)
{
	DeleteObject(this);
}

void CSub::Initialize()
{
	CreateCollider();
	m_pCollider->SetScale(Vec2(10.f, 10.f));
	m_fTheta = 0.f;
	m_fSpeed = 800.f;
}

void CSub::Update()
{
	m_fTheta += 40.f * fDT;
	m_vPos.x += m_fSpeed * m_vDir.x * fDT;
	m_vPos.y += m_fSpeed * m_vDir.y * fDT;

	m_fTime += fDT;

	if (0.02f < m_fTime)
	{
		m_fTime = 0.f;
		CreateAfterImage();
	}
}

void CSub::Render(HDC _dc)
{
	m_pAnimator->dir_Render(_dc, Color(255, 255, 255), Color(255, 255, 255));
	Component_Render(_dc);
}

void CSub::CreateAfterImage()
{
	float fAlphaCount = 4.f;
	float fAfterColor[3];
	fAfterColor[0] = 0.1f;
	fAfterColor[1] = 0.1f;
	fAfterColor[2] = 0.1f;

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

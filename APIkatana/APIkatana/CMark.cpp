#include "stdafx.h"
#include "CMark.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CSoundMgr.h"
#include "CAbstractFactory.h"

#include "CObj.h"
#include "CMonster.h"

#include "CEffects_Bullet.h"
#include "CEffects_GunSpark.h"

CMark::CMark()
	: m_eType(MARK_TYPE::END)
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Mark_Exclaim2", L"texture\\Effects\\Mark_Exclaim2.png");
	iCount = 2;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Mark_Exclaim2", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Mark_Question", L"texture\\Effects\\Mark_Question.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Mark_Question", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Monster_Gangster_Gun", L"texture\\Monster\\Monster_Gangster_Gun.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Monster_Gangster_Gun", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);
	
	m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	m_fTime = 2.f;

}

CMark::~CMark()
{

}

void CMark::Initialize()
{
	switch (m_eType)
	{
	case MARK_TYPE::EXCLAIM2:
		Get_Animator()->Play(L"Mark_Exclaim2", false);
		Get_Animator()->Get_CurAnim()->SetFrame(0);

		break;

	case MARK_TYPE::QUESTION:
		Get_Animator()->Play(L"Mark_Question", false);

		break;

	case MARK_TYPE::ARM:
		Get_Animator()->Play(L"Monster_Gangster_Gun", false);

		break;

	}
}

void CMark::Update()
{
	if (MARK_TYPE::ARM == m_eType)
	{
		Update_arm();
		return;
	}

	Vec2 vPos = Get_Owner()->Get_Pos();
	vPos.y -= 28.f;
	SetPos(vPos);

	if (MARK_TYPE::END != m_eType)
		Get_Animator()->Update();
}

void CMark::Render(HDC _dc)
{
	if (MARK_TYPE::ARM == m_eType)
	{
		Get_Animator()->dir_Render(_dc, Color(255, 255, 255), Color(255, 255, 255));
		return;
	}

	if (MARK_TYPE::END != m_eType)
		Get_Animator()->Render(_dc);
}

void CMark::Update_arm()
{
	if (!m_pOwner->Get_Owner())
		return;

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == 1.f)
	{
		*m_colorMatrix = {
		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		*m_colorMatrix = {
		 0.2f,  0.0f, 0.0f, 0.0f, 0.0f,
		0.0f,   0.7f, 0.0f, 0.0f, 0.0f,
		0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		//Get_ImageAttr()->SetColorKey(Color(255, 255, 255), Color(255, 255, 255), ColorAdjustTypeBitmap);
		//Get_ImageAttr()->SetColorMatrix(m_colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	}

	Vec2 vPos = Get_Owner()->Get_Pos();
	float fDir = Get_Owner()->Get_RenderDir().x;
	//dvPos.x += 15.f * fDir;

	Vec2 vDir;

	Vec2 vMonsterPos = Get_Owner()->Get_Pos();
	Vec2 vPlayerPos = Get_Owner()->Get_Owner()->Get_Pos();

	vDir = vPlayerPos - vMonsterPos;
	vDir.Normalize();

	SetDir(vDir);

	vPos.x += 13.f * vDir.x;
	vPos.y += 25.f * vDir.y;

	m_vPos = vPos;

	m_fTheta = acosf(m_vDir.x);

	if (m_vDir.y < 0)
		m_fTheta *= -1.f;

	if (0.f == m_fTime)
		CSoundMgr::Get_Instance()->PlaySound(L"Monster_GunReload.wav");

	m_fTime += fDT;

	if (2.5f < m_fTime)
	{
		m_fTime = 0.f;
		CreateBullet();
	}

}

void CMark::CreateBullet()
{
	Vec2 vPos = Get_Pos();
	Vec2 vDir = Get_Dir();

	vPos.x += 30.f * vDir.x;
	vPos.y += 30.f * vDir.y;

	CAbstractFactory<CEffects_Bullet>::Create_Effects(this, vPos, vDir, GROUP_TYPE::MOBSUBATTACK);
	CAbstractFactory<CEffects_GunSpark>::Create_Effects(this, vPos, vDir, GROUP_TYPE::EFFECTS);


	int iRand = random(0, 1);
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Slow_GunShot.wav");
	}
	else
	{
		switch (iRand)
		{
		case 0:
			CSoundMgr::Get_Instance()->PlaySound(L"Monster_GunShot_1.wav");
			break;

		case 1:
			CSoundMgr::Get_Instance()->PlaySound(L"Monster_GunShot_2.wav");
			break;
		}
	}
}

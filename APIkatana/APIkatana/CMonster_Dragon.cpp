#include "stdafx.h"
#include "CMonster_Dragon.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"

#include "CAbstractFactory.h"
#include "CEffects_Dust.h"
#include "CAfterImage.h"

#include "CMark.h"

CMonster_Dragon::CMonster_Dragon()
{
	CreateAnimator();
	CTexture* pTex = nullptr;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Casual_Idle", L"texture\\Monster\\Dragon_Casual_Idle.png");
	UINT iCount = 13;
	float fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Dragon_Casual_Idle", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_CasualtoBattle", L"texture\\Monster\\Dragon_CasualtoBattle.png");
	iCount = 5;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Dragon_CasualtoBattle", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Stance", L"texture\\Monster\\Dragon_Stance.png");
	iCount = 12;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"STANCE", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.09f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Run", L"texture\\Monster\\Dragon_Run.png");
	iCount = 10;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"RUN", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Dragon_Dash", L"texture\\Monster\\Dragon_Dash.png");
	iCount = 7;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"DASH", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);

	CAnimation* pAnim = Get_Animator()->FindAnimation(L"Dragon_Casual_Idle");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(0.f, -3.f);
}

CMonster_Dragon::~CMonster_Dragon()
{
}


void CMonster_Dragon::Initialize()
{
	CreateCollider();

	float fWidth = 20.f;
	float fHeight = 4.f;
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));
	m_tPhysics.fOffsetY = 18.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, m_tPhysics.fOffsetY)); //오프셋 만져주면 충돌체 위치 바뀜

	m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };



	m_vPos = Vec2(550.f, 300.f);
	m_tPhysics.fOriginY = m_vPos.y;

	m_bAir = true;

	m_vDir = Vec2(-1.f, 0.f);
	m_vRenderDir = m_vDir;




	//마크
	m_pMark = new CMark;
	m_pMark->SetOwner(this);
	dynamic_cast<CMark*>(m_pMark)->SetMarkType(MARK_TYPE::END);
	m_pMark->Initialize();
	CreateObject(m_pMark, GROUP_TYPE::EFFECTS);


	Set();
}

void CMonster_Dragon::Update()
{
	*m_colorMatrix = {
   m_fAlpha,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  m_fAlpha, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, m_fAlpha, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	CAlive::Update();
}

void CMonster_Dragon::Render(HDC _dc)
{
	m_pAnimator->Render(_dc, Color(255, 255, 255), Color(255, 255, 255));
}

void CMonster_Dragon::Default()
{
	m_bPeace = false;
	m_pAnimator->Play(L"Dragon_CasualtoBattle", true);
	m_eState = STATE_TYPE::DEFAULT;

	m_fTime = 0.f;

	dynamic_cast<CMark*>(m_pMark)->SetMarkType(MARK_TYPE::EXCLAIM2);
	m_pMark->Initialize();
	
}

void CMonster_Dragon::Run()
{
	m_pAnimator->Play(L"RUN", true);
	m_eState = STATE_TYPE::RUN;
	m_fTime = 0.f;
}

void CMonster_Dragon::Set()
{
	m_pAnimator->Play(L"Dragon_Casual_Idle", true);
	m_eState = STATE_TYPE::SET;
	m_fTime = 0.f;
	m_tPhysics.fAccel = 0.f;
}

void CMonster_Dragon::Sit()
{
	m_pAnimator->Play(L"STANCE", true);
	m_eState = STATE_TYPE::SIT;
	m_fTime = 0.f;
	m_bAfter = true;
}

void CMonster_Dragon::Dash()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Player_Dash.wav");


	m_pAnimator->Play(L"DASH", true);
	m_eState = STATE_TYPE::DASH;

	m_vDir = Vec2(1.f, 0.f);
	m_vRenderDir = m_vDir;
	m_fTime = 0.f;
	m_tPhysics.fXSpeed = m_tPhysics.fMaxXSpeed * 2.5f;
	m_tPhysics.fAccel = 0.f;

}

void CMonster_Dragon::Update_Default()
{
	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	m_fTime += fDT;

	if (TimeLimit <= m_fTime)
	{
		Sit();
	}
	

	
}

void CMonster_Dragon::Update_Sit()
{
	m_fTime += fDT;

	if (0.7f < m_fTime)
		Dash();
}

void CMonster_Dragon::Update_Run()
{
	m_tPhysics.fAccel = m_tPhysics.fMaxAccel;

	if (m_vPos.x > 920.f)
		Set();
}

void CMonster_Dragon::Update_Dash()
{
	float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();

	m_fTime += fDT;
	m_fDashTime += fDT;

	if (0.02f <= m_fDashTime)
	{
		CreateAfterImage();
		CAbstractFactory<CEffects_Dust>::Create_Effects(this, m_vPos, m_vRenderDir, GROUP_TYPE::EFFECTS);
		//CreateDust();
		m_fDashTime = 0.f;
	}
	if (TimeLimit <= m_fTime)
	{
		Run();
	}

}

void CMonster_Dragon::Update_Set()
{
	if (m_bPeace)
	{
		if (m_pOwner->Get_Pos().y + 230.f > m_vPos.y && m_pOwner->Get_Pos().x + 100.f > m_vPos.x)
			Default();

	}
	else
	{
		m_fAlpha -= 2.f*fDT;
		if (m_fAlpha <= 0.05f)
		{
			DeleteObject(this);
			DeleteObject(m_pMark);
		}
	}
}

void CMonster_Dragon::CreateAfterImage()
{
	float m_fAfterColor[3]{};
	float m_fAfterDuration(0.f);

	if (m_bAfter)
	{
		if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW) // 속도 느린 상태면
		{
			m_fAfterColor[0] = 0.4f;
			m_fAfterColor[1] = 0.7f;
			m_fAfterColor[2] = 0.7f;
			m_fAfterDuration = 2.f;

		}
		else
		{
			float fTemp = (float)random(0, 3);
			m_fAfterDuration = 3.f;

			m_fAfterColor[0] = 1.f;
			m_fAfterColor[1] = fTemp * 0.1f;
			m_fAfterColor[2] = fTemp * 0.1f;
		}

		CAfterImage* pImage = new CAfterImage;

		pImage->SetAnim(*Get_Animator()->Get_CurAnim());
		pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
		pImage->SetDir(Get_Dir());
		pImage->Set_RGB(m_fAfterColor);

		pImage->SetAlphaCount(m_fAfterDuration); // 낮게 설정할 수록 잔상이 오래 남음

		pImage->SetPos(Get_Pos());
		CreateObject(pImage, GROUP_TYPE::LASER_ATTACK);


	}
	else if (m_eState == STATE_TYPE::RUN || m_eState == STATE_TYPE::AIR)
	{
		/*m_fAfterColor[0] = 0.1f;
		m_fAfterColor[1] = 0.6f;
		m_fAfterColor[2] = 1.0f;*/
		m_fAfterColor[0] = 0.1f;
		m_fAfterColor[1] = 0.1f;
		m_fAfterColor[2] = 0.1f;
		m_fAfterDuration = 8.f;


		CAfterImage* pImage = new CAfterImage;

		pImage->SetAnim(*Get_Animator()->Get_CurAnim());
		pImage->SetFrame(Get_Animator()->Get_CurAnim()->Get_CurFrame());
		pImage->SetDir(m_vRenderDir);
		pImage->Set_RGB(m_fAfterColor);

		pImage->SetAlphaCount(m_fAfterDuration); // 낮게 설정할 수록 잔상이 오래 남음

		pImage->SetPos(Get_Pos());
		CreateObject(pImage, GROUP_TYPE::LASER_ATTACK);
	}
}

#include "stdafx.h"
#include "CEffects.h"

#include "CTimeMgr.h"
#include "CAnimator.h"


CEffects::CEffects()
	: m_fSpeed (100.f)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
}

CEffects::~CEffects()
{}

void CEffects::Render(HDC _dc)
{
	m_pAnimator->dir_Render(_dc);
	Component_Render(_dc);
}

void CEffects::Effects_Move(bool _bReal)
{
	if (_bReal)
	{
		m_vPos.x += m_fSpeed * RealfDT * m_vDir.x;
		m_vPos.y += m_fSpeed * RealfDT * m_vDir.y;
	}
	else
	{
		m_vPos.x += m_fSpeed * fDT * m_vDir.x;
		m_vPos.y += m_fSpeed * fDT * m_vDir.y;
	}

}



//#include "stdafx.h"
//#include "CEffects.h"
//
//#include "CTexture.h"
//#include "CAnimator.h"
//#include "CAnimation.h"
//
//#include "CResMgr.h"
//#include "CTimeMgr.h"
//#include "CCollider.h"
//
//#include "CAlive.h"
//
//CEffects::CEffects()
//	: m_eEffectType(EFFECT_TYPE::END)
//	, m_fTimeLimit(0.f)
//{
//
//	CreateAnimator();
//	CTexture* pTex = nullptr;
//	UINT iCount;
//	float fSize;
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_Impact", L"texture\\Effects\\Effects_Impact.png");
//	iCount = 6;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_Impact", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);
//
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_JumpDust", L"texture\\Effects\\Effects_JumpDust.png");
//	iCount = 4;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_JumpDust", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_Blood", L"texture\\Effects\\Effects_Blood.png");
//	iCount = 6;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_Blood", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_Blood3", L"texture\\Effects\\Effects_Blood3.png");
//	iCount = 6;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_Blood3", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_GunSpark", L"texture\\Effects\\Effects_GunSpark.png");
//	iCount = 8;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_GunSpark", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_BulletReflect", L"texture\\Effects\\Effects_BulletReflect.png");
//	iCount = 5;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_BulletReflect", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_BloodWall", L"texture\\Effects\\Effects_BloodWall.png");
//	iCount = 1;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_BloodWall", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);
//	
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_BloodWall2", L"texture\\Effects\\Effects_BloodWall2.png");
//	iCount = 1;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_BloodWall2", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);
//	
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_BloodWall3", L"texture\\Effects\\Effects_BloodWall3.png");
//	iCount = 1;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_BloodWall3", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_BloodWall4", L"texture\\Effects\\Effects_BloodWall4.png");
//	iCount = 1;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_BloodWall4", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_BloodWall5", L"texture\\Effects\\Effects_BloodWall5.png");
//	iCount = 1;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_BloodWall5", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_Cut", L"texture\\Effects\\Effects_Cut_5.png");
//	iCount = 5;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_Cut", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.07f, iCount);
//
//	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_PickUp", L"texture\\Effects\\Effects_PickUp.png");
//	iCount = 8;
//	fSize = pTex->Width() / (float)iCount;
//	Get_Animator()->CreateAnimation(L"Effects_PickUp", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.05f, iCount);
//
//
//}
//
//CEffects::~CEffects()
//{
//
//}
//
//void CEffects::OnCollisionEnter(CCollider * _pOther)
//{
//	CObj* pOtherObj = _pOther->Get_Obj();
//
//	switch (pOtherObj->Get_ObjType())
//	{
//	case GROUP_TYPE::PLAYER_HITBOX:
//	case GROUP_TYPE::MONSTER_HITBOX:
//		dynamic_cast<CAlive*>(pOtherObj->Get_Owner())->LaserHit();
//		pOtherObj->SetCollision(false);
//		break;
//
//
//	case GROUP_TYPE::PLAYER:
//	case GROUP_TYPE::MONSTER:
//		if (STATE_TYPE::HIT == dynamic_cast<CAlive*>(pOtherObj)->Get_State() || STATE_TYPE::DEATH == dynamic_cast<CAlive*>(pOtherObj)->Get_State())
//			dynamic_cast<CAlive*>(pOtherObj->Get_Owner())->LaserHit();
//
//		break;
//	}
//
//}
//
//void CEffects::Update()
//{
//
//	switch (m_eEffectType)
//	{
//	case EFFECT_TYPE::SLASH:
//		slash_Update();
//
//		break;
//
//	case EFFECT_TYPE::ELECTRIC:
//	case EFFECT_TYPE::ELECTRIC2:
//	case EFFECT_TYPE::PARTICLE:
//		electric_Update();
//
//		break;
//
//	case EFFECT_TYPE::BLOODWALL:
//		bloodwall_Update();
//		break;
//
//	case EFFECT_TYPE::LASER:
//		laser_Update();
//		break;
//
//	case EFFECT_TYPE::PICKUP:
//		pickup_Update();
//		break;
//
//	case EFFECT_TYPE::RAIN:
//		rain_Update();
//		break;
//
//	default:
//	{
//		Vec2 vPos = Get_Pos();
//
//			if (m_tInfo.bMove)
//			{
//				vPos.x += m_fSpeed * fDT * Get_Dir().x;
//				vPos.y += m_fSpeed * fDT * Get_Dir().y;
//				SetPos(vPos);
//			}
//
//		float TimeLimit = Get_Animator()->Get_CurAnim()->Get_MaxTime();
//
//		if (EFFECT_TYPE::IMPACT == m_eEffectType || EFFECT_TYPE::CUT == m_eEffectType)
//			m_fTime += RealfDT;
//		else
//			m_fTime += fDT;
//
//		if (m_eEffectType == EFFECT_TYPE::BULLETREFLECT && TimeLimit / 6.f >= m_fTime)
//		{
//			CreateElectric();
//		}
//
//			if (TimeLimit <= m_fTime)
//			{
//				DeleteObject(this);
//			}
//
//
//			if (EFFECT_TYPE::IMPACT == m_eEffectType || EFFECT_TYPE::CUT == m_eEffectType)
//			{
//				Get_Animator()->speed_Update();
//			}
//			else
//				Get_Animator()->Update();
//	}
//
//	}
//
//	
//}
//
//void CEffects::Render(HDC _dc)
//{
//	if (EFFECT_TYPE::SLASH == m_eEffectType)
//		slash_Render(_dc);
//	else if (EFFECT_TYPE::ELECTRIC == m_eEffectType || EFFECT_TYPE::ELECTRIC2 == m_eEffectType
//			|| EFFECT_TYPE::PARTICLE == m_eEffectType || EFFECT_TYPE::RAIN == m_eEffectType)
//		electric_Render(_dc);
//	else if (EFFECT_TYPE::LASER == m_eEffectType)
//		laser_Render(_dc);
//	else
//		Get_Animator()->dir_Render(_dc);
//}
//

//
//void CEffects::Initialize()
//{
//	switch (m_eEffectType)
//	{
//	case EFFECT_TYPE::DUST:
//		//CreateImageAttr(Color(0, 0, 0), Color(100, 100, 100));
//		Get_Animator()->Play(L"Effects_Dust", false);
//		//m_tInfo.bMove = true;
//
//		break;
//
//	case EFFECT_TYPE::LANDINGDUST:
//		Get_Animator()->Play(L"Effects_LandingDust", false);
//		//m_tInfo.bMove = false;
//
//		break;
//
//	case EFFECT_TYPE::JUMPDUST:
//		Get_Animator()->Play(L"Effects_JumpDust", false);
//		//m_tInfo.bMove = false;
//
//		break;
//
//	case EFFECT_TYPE::SLASH:
//	{
//		Vec2 vPos = Get_Pos();
//
//		vPos.x += -1000.f * Get_Dir().x;
//		vPos.y += -1000.f * Get_Dir().y;
//
//		SetPos(vPos);
//
//
//		int i = random(0, 1);
//		if (i == 0)
//			m_tInfo.iColor = 50;
//		else
//			m_tInfo.iColor = 200;
//
//		//m_tInfo.iColor = random(100, 200);
//
//	}
//		SetScale(Vec2(600.f, 8.f));
//		//m_tInfo.bMove = false;
//		m_fSpeed = 8500.f;
//
//		break;
//
//	case EFFECT_TYPE::ELECTRIC:
//	{
//		int iRand = random(10, 15);
//		SetScale(Vec2(float(iRand), 1.f));
//		m_tInfo.iColor = 255;
//		m_fSpeed = 200.f;
//		m_tInfo.RGB[0] = 0;
//		m_tInfo.RGB[1] = 200;
//		m_tInfo.RGB[2] = 255;
//
//
//	}
//
//	break;
//
//	case EFFECT_TYPE::ELECTRIC2:
//	{
//		int iRand = random(15, 20);
//		SetScale(Vec2(float(iRand), 2.f));
//		m_tInfo.iColor = 255;
//		m_fSpeed = 200.f;
//		m_tInfo.RGB[0] = 250;
//		m_tInfo.RGB[1] = 240;
//		m_tInfo.RGB[2] = 100;
//	}
//
//	break;
//
//	case EFFECT_TYPE::IMPACT:
//		Get_Animator()->Play(L"Effects_Impact", false);
//
//		*m_colorMatrix = {
//		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.1f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.0f, 0.9f, 0.0f,
//		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };
//
//
//		//m_tInfo.bMove = false;
//
//		break;
//
//	case EFFECT_TYPE::CUT:
//		Get_Animator()->Play(L"Effects_Cut", false);
//
//		*m_colorMatrix = {
//		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.1f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
//		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };
//
//
//		//m_tInfo.bMove = false;
//
//		break;
//
//	case EFFECT_TYPE::BLOOD:
//		Get_Animator()->Play(L"Effects_Blood", false);
//
//		*m_colorMatrix = {
//		 0.9f,  0.0f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.1f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.1f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.0f, 0.6f, 0.0f,
//		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };
//
//
//
//		//m_tInfo.bMove = true;
//
//
//		break;
//
//	case EFFECT_TYPE::BLOOD3:
//		Get_Animator()->Play(L"Effects_Blood3", false);
//
//		*m_colorMatrix = {
//		 0.9f,  0.0f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.1f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.1f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.0f, 0.6f, 0.0f,
//		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };
//
//
//
//		//m_tInfo.bMove = true;
//
//
//		break;
//
//	case EFFECT_TYPE::BULLETREFLECT:
//		Get_Animator()->Play(L"Effects_BulletReflect", false);
//		//m_tInfo.bMove = false;
//
//		break;
//
//	case EFFECT_TYPE::GUNSPARK:
//		Get_Animator()->Play(L"Effects_GunSpark", false);
//		//m_tInfo.bMove = false;
//
//		break;
//
//	case EFFECT_TYPE::BLOODWALL:
//	{
//		int iRand = random(0, 2);
//
//		switch (iRand)
//		{
//		case 0:
//			Get_Animator()->Play(L"Effects_BloodWall5", false);
//			break;
//
//		default:
//			Get_Animator()->Play(L"Effects_BloodWall4", false);
//			break;
//		}
//
//		Vec2 vDir = Get_Dir();
//
//		if (-0.9f < vDir.y && -0.2f > vDir.y) // y값이 -0.8 ~ -0.2 일 때만
//		{
//			switch (iRand)
//			{
//			case 0:
//				Get_Animator()->Play(L"Effects_BloodWall", false);
//				break;
//
//			case 1:
//				Get_Animator()->Play(L"Effects_BloodWall2", false);
//				break;
//
//			default:
//				Get_Animator()->Play(L"Effects_BloodWall3", false);
//				break;
//			}
//
//			if (0 > vDir.x)
//			{
//				vDir.x = 0.f;
//				vDir.y = -1.f;
//
//			}
//			else
//			{
//				vDir.y = 1.f;
//				vDir.x = 1.f;
//
//			}
//
//
//			SetDir(vDir);
//		}
//
//
//	}
//
//	m_tInfo.fAlpha = 0.7f;
//
//
//
//		//m_tInfo.bMove = false;
//
//
//		break;
//
//	case EFFECT_TYPE::LASER:
//	{
//		CreateCollider();
//
//		float fWidth = 10.f;
//		float fHeight = 120.f;
//		Get_Collider()->SetOffSetPos(Vec2(0.f, 60.f)); //오프셋 만져주면 충돌체 위치 바뀜
//		Get_Collider()->SetScale(Vec2(fWidth, fHeight));
//	}
//	SetScale(Vec2(10.f, 100.f));
//		m_tInfo.RGB[0] = 0;
//		m_tInfo.RGB[1] = 255;
//		m_tInfo.RGB[2] = 255;
//
//		break;
//
//	case EFFECT_TYPE::PARTICLE:
//	{
//		float fx = (float)random(-10, 10) * 1.f;
//		float fy = (float)random(1, 10) * -1.f;
//		Vec2 vDir = { fx, fy };
//
//		if (0.f == fx)
//			fx = 1.f;
//
//		SetDir(vDir);
//		SetScale(Vec2(1.f, 1.f));
//		m_tInfo.iColor = 255;
//		m_fSpeed = 300.f;
//		m_tInfo.RGB[0] = 250;
//		m_tInfo.RGB[1] = 240;
//		m_tInfo.RGB[2] = 0;
//	}
//
//	break;
//
//
//	case EFFECT_TYPE::PICKUP:
//		Get_Animator()->Play(L"Effects_PickUp", true);
//		m_fSpeed = 20.f;
//		m_tInfo.fAlpha = 0.f;
//		//m_tInfo.bMove = true;
//		break;
//
//	case EFFECT_TYPE::RAIN:
//	{
//		int iRand = random(20, 40);
//		SetDir(Vec2(0.f, 1.f));
//		SetScale(Vec2((float)iRand, 2.f));
//		m_tInfo.iColor = 190;
//		m_fSpeed = 3000.f;
//		m_tInfo.RGB[0] = 0;
//		m_tInfo.RGB[1] = 0;
//		m_tInfo.RGB[2] = 0;
//	}
//
//	break;
//	}
//
//}
//
//void CEffects::slash_Update()
//{
//	Vec2 vPos = Get_Pos();
//
//	vPos.x += m_fSpeed * RealfDT * Get_Dir().x;
//	vPos.y += m_fSpeed * RealfDT * Get_Dir().y;
//
//	SetPos(vPos);
//
//	//수 늘릴수록 색 빠르게 변화
//	/*if (m_tInfo.iColor >= 100)
//		m_tInfo.bColorPlus = false;
//	else if (m_tInfo.iColor <= 0)
//		m_tInfo.bColorPlus = true;
//
//	if (m_tInfo.bColorPlus)
//		m_tInfo.iColor += 20;
//	else
//		m_tInfo.iColor -= 20;*/
//
//
//	m_fTime += RealfDT;
//
//	if (0.15f < m_fTime)
//	{
//		if (m_tInfo.iColor == 50)
//			m_tInfo.iColor = 200;
//		else
//			m_tInfo.iColor = 50;
//	}
//
//
//	if (3.f <= m_fTime)
//	{
//		DeleteObject(this);
//	}
//
//}
//
//void CEffects::slash_Render(HDC _dc)
//{
//	Vec2 vDir = Get_Dir();
//	float fAngle = acos(vDir.x) * (180.f / PI); // 각도 구하기
//
//	if (0 > vDir.y)
//	{
//		fAngle *= -1.f;
//	}
//
//	Vec2 vPos = Get_Pos();
//	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
//	Vec2 vScale = Get_Scale();
//
//	int LTX = (int)(vPos.x - vScale.x / 2.f);
//	int LTY = (int)(vPos.y - vScale.y / 2.f);
//	int RBX = (int)(vPos.x + vScale.x / 2.f);
//	int RBY = (int)(vPos.y + vScale.y / 2.f);
//
//	Point LTpoint = rotate(vPos, Point(LTX, LTY), fAngle);
//	Point LBpoint = rotate(vPos, Point(LTX, RBY), fAngle);
//	Point RTpoint = rotate(vPos, Point(RBX, LTY), fAngle);
//	Point RBpoint = rotate(vPos, Point(RBX, RBY), fAngle);
//
//	Graphics g(_dc);
//
//	////////////////////////
//	Point destinationPoints[] = {
//		LTpoint, LBpoint, RBpoint, RTpoint };
//
//	// Use the array of points to construct a path.
//	GraphicsPath path;
//	path.AddLines(destinationPoints, 4);
//
//	// Use the path to construct a path gradient brush.
//	PathGradientBrush pthGrBrush(&path);
//
//	// Set the color at the center of the path to red.
//	pthGrBrush.SetCenterColor(Color(250, 30 +m_tInfo.iColor, 285-m_tInfo.iColor, 255));
//
//	// Set the colors of the points in the array.
//	Color colors[] = { Color(50, 30 + m_tInfo.iColor, 285 - m_tInfo.iColor, 255) };
//	int count = 1;
//	pthGrBrush.SetSurroundColors(colors, &count);
//
//	// Fill the path with the path gradient brush.
//	g.FillPath(&pthGrBrush, &path);
//
//}
//
//void CEffects::electric_Update()
//{
//	if (0 < m_tInfo.iColor)
//		m_tInfo.iColor -= (int)(700.f * RealfDT);
//
//	if (10 >= m_tInfo.iColor)
//	{
//		DeleteObject(this);
//	}
//
//	Vec2 vPos = Get_Pos();
//
//	vPos.x += m_fSpeed * RealfDT * Get_Dir().x;
//	vPos.y += m_fSpeed * RealfDT * Get_Dir().y;
//	SetPos(vPos);
//}
//
//void CEffects::electric_Render(HDC _dc)
//{
//	Vec2 vDir = Get_Dir();
//	float fAngle = acos(vDir.x) * (180.f / PI); // 각도 구하기
//
//	if (0 > vDir.y)
//	{
//		fAngle *= -1.f;
//	}
//
//	Vec2 vPos = Get_Pos();
//	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
//	Vec2 vScale = Get_Scale();
//
//	int LTX = (int)(vPos.x - vScale.x / 2.f);
//	int LTY = (int)(vPos.y - vScale.y / 2.f);
//	int RBX = (int)(vPos.x + vScale.x / 2.f);
//	int RBY = (int)(vPos.y + vScale.y / 2.f);
//
//	Point LTpoint = rotate(vPos, Point(LTX, LTY), fAngle);
//	Point LBpoint = rotate(vPos, Point(LTX, RBY), fAngle);
//	Point RTpoint = rotate(vPos, Point(RBX, LTY), fAngle);
//	Point RBpoint = rotate(vPos, Point(RBX, RBY), fAngle);
//
//	Graphics g(_dc);
//
//	////////////////////////
//	Point destinationPoints[] = {
//		LTpoint, LBpoint, RBpoint, RTpoint };
//
//	// Use the array of points to construct a path.
//	GraphicsPath path;
//	path.AddLines(destinationPoints, 4);
//
//	//g.FillPath(&pthGrBrush, &path);
//	g.FillPath(&SolidBrush(Color(m_tInfo.iColor, m_tInfo.RGB[0], m_tInfo.RGB[1], m_tInfo.RGB[2])), &path);
//
//}
//
//void CEffects::rain_Update()
//{
//	Vec2 vPos = Get_Pos();
//
//	if (380.f < vPos.y)
//	{
//		DeleteObject(this);
//	}
//
//
//	vPos.x += m_fSpeed * RealfDT * Get_Dir().x;
//	vPos.y += m_fSpeed * RealfDT * Get_Dir().y;
//	SetPos(vPos);
//}
//
//void CEffects::bloodwall_Update()
//{
//	m_tInfo.fAlpha -= 0.1f * fDT;
//	if (0.1f > m_tInfo.fAlpha)
//	{
//		DeleteObject(this);
//	}
//
//	*m_colorMatrix = {
//		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.0f, m_tInfo.fAlpha, 0.0f,
//		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };
//}
//
//void CEffects::laser_Update()
//{
//	m_fTime += fDT;
//
//	Vec2 vScale = Get_Scale();
//	vScale.x -= 35.f * fDT;
//	SetScale(vScale);
//
//	if (1.f >= vScale.x)
//	{
//		DeleteObject(this);
//	}
//	if (0.03 < m_fTime)
//	{
//		m_fTime = 0.f;
//		if (m_tInfo.RGB[0] == 255)
//		{
//			m_tInfo.RGB[0] = 0;
//			m_tInfo.RGB[1] = 255;
//			m_tInfo.RGB[2] = 255;
//		}
//		else
//		{
//			m_tInfo.RGB[0] = 255;
//			m_tInfo.RGB[1] = 190;
//			m_tInfo.RGB[2] = 30;
//		}
//	}
//}
//
//void CEffects::laser_Render(HDC _dc)
//{
//	Vec2 vPos = Get_Pos();
//	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
//	Vec2 vScale = Get_Scale();
//	vPos.y += 47;
//
//	int LTX = (int)(vPos.x - vScale.x / 2.f);
//	int LTY = (int)(vPos.y - vScale.y / 2.f);
//	int RBX = (int)(vPos.x + vScale.x / 2.f);
//	int RBY = (int)(vPos.y + vScale.y / 2.f);
//
//	Point LTpoint = Point(LTX, LTY);
//	Point LBpoint = Point(LTX, RBY);
//	Point RTpoint = Point(RBX, LTY);
//	Point RBpoint = Point(RBX, RBY);
//
//	Graphics g(_dc);
//
//	////////////////////////
//	Point destinationPoints[] = {
//		LTpoint, LBpoint, RBpoint, RTpoint };
//
//	// Use the array of points to construct a path.
//	GraphicsPath path;
//	path.AddLines(destinationPoints, 4);
//
//	//g.FillPath(&pthGrBrush, &path);
//	g.FillPath(&SolidBrush(Color(255, m_tInfo.RGB[0], m_tInfo.RGB[1], m_tInfo.RGB[2])), &path);
//
//	CObj::Component_Render(_dc);
//}
//
//void CEffects::pickup_Update()
//{
//	Vec2 vPos = Get_Pos();
//
//	*m_colorMatrix = {
//		 1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
//		 0.0f,  0.0f, 0.0f, m_tInfo.fAlpha, 0.0f,
//		 0.0f, 0.0f, 0.0f, 0.0f, 1.f };
//
//	m_fTime += fDT;
//
//	if (0.5f > m_fTime)
//	{
//		vPos.y -= m_fSpeed * fDT;
//	}
//	else
//	{
//		vPos.y += m_fSpeed * fDT;
//	}
//
//	if (1.f < m_fTime)
//		m_fTime = 0.f;
//
//	SetPos(vPos);
//
//	if (m_tInfo.bMove)
//	{
//		if (1.f > m_tInfo.fAlpha)
//			m_tInfo.fAlpha += fDT;
//		else
//			m_tInfo.fAlpha = 1.f;
//	}
//	else
//	{
//		m_tInfo.fAlpha -= fDT;
//		if (0.15 > m_tInfo.fAlpha)
//		{
//			DeleteObject(this);
//		}
//	}
//}
//
//void CEffects::CreateElectric()
//{
//	Vec2 vPos = Get_Pos();
//	float fx = random(-10, 10) * 1.f;
//	float fy = random(-10, 10) * 1.f;
//
//		
//
//	Vec2 vDir = { fx, fy };
//
//	if (0 == fx && 0 == fy)
//		return;
//
//	vDir.Normalize();
//
//	vPos.x += 10.f * vDir.x;
//	vPos.y += 10.f * vDir.y;
//
//	CEffects* pEffects = new CEffects;
//	pEffects->Set_EffectType(EFFECT_TYPE::ELECTRIC2);
//	pEffects->SetDir(vDir);
//	pEffects->SetPos(vPos);
//	pEffects->Initialize();
//	CreateObject(pEffects, GROUP_TYPE::EFFECTS);
//}

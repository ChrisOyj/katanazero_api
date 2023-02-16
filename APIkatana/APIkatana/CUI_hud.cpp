#include "stdafx.h"
#include "CUI_hud.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CEditor.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CEffects_Electric.h"
#include "CAbstractFactory.h"
#include "CEffects_PurpleScreen.h"
#include "CPlayer.h"

CUI_hud::CUI_hud()
	: m_fSlowMaxTime(6.f)
	, m_fSlowTime(m_fSlowMaxTime)
	, m_fCurTime(1.f)
	, m_pScreen(nullptr)

{
	//애니메이터
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_hud", L"texture\\UI\\UI_hud.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"UI_hud", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_battery", L"texture\\UI\\UI_battery.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"UI_battery", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_batterypart", L"texture\\UI\\UI_batterypart.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"UI_batterypart", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);
	
	pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_Weapon", L"texture\\UI\\UI_Weapon.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"UI_Weapon", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_katana", L"texture\\UI\\UI_katana.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"UI_katana", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_hand", L"texture\\UI\\UI_hand.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"UI_hand", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Knife", L"texture\\SubWeapon\\SubWeapon_Knife.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Knife", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Bottle", L"texture\\SubWeapon\\SubWeapon_Bottle.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Bottle", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Beer", L"texture\\SubWeapon\\SubWeapon_Beer.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Beer", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"SubWeapon_Smoke", L"texture\\SubWeapon\\SubWeapon_Smoke.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"SubWeapon_Smoke", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.04f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_Timer", L"texture\\UI\\UI_Timer.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"UI_Timer", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"UI_TimeBar", L"texture\\UI\\UI_TimeBar.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"UI_TimeBar", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);


	m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.9f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };



	m_fTargetTime = CEditor::Get_Instance()->LoadTimeRecord(5);
}

CUI_hud::~CUI_hud()
{

}

void CUI_hud::Update()
{
	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW)
	{
		m_fSlowTime -= RealfDT;

		if (0 >= m_fSlowTime)
		{
			m_fSlowTime = 0.f;
		}
	}
	else
	{
		if (m_fSlowMaxTime > m_fSlowTime)
		{
			m_fSlowTime += fDT * 2.5f;
		}
		else
		{
			m_fSlowTime = m_fSlowMaxTime;
		}
	}

	/*if (KEY(LBUTTON, TAP))
		m_fCurTime -= 0.1f;*/

	if (m_fCurTime < 0.f)
	{
		m_fCurTime = 0.f;
		dynamic_cast<CEffects*>(m_pScreen)->Set_Delete();
	}
	else if (m_fCurTime != 0.f)
		m_fCurTime -= 0.01f * fDT;

	if (0.19f > m_fCurTime && !m_pScreen)
	{
		m_pScreen = CAbstractFactory<CEffects_PurpleScreen>::Create();
		m_pScreen->SetOwner(this);
		CreateObject(m_pScreen, GROUP_TYPE::MONSTER_SIGHT);
	}


	Vec2 vPos = CCamera::Get_Instance()->Get_LookAt();
	vPos.y -= WINCY / 2.f - 12.f;
	SetPos(vPos);

	if (Get_Owner() != nullptr && !Get_Owner()->IsDead())
	{
		if (m_fCurTime < 0.f)
		dynamic_cast<CAlive*>(m_pOwner)->Hit(Vec2(-0.15f, -0.4f));

		m_eSubType = dynamic_cast<CPlayer*>(Get_Owner())->Get_SubType();
	}
	else
	{
		SetOwner(nullptr);
	}
}

void CUI_hud::Render(HDC _dc)
{
	Vec2 vPos = Get_Pos();

	int iRand = random(0, 20);

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.9f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };


	Get_Animator()->Play(L"UI_hud", false);
	Get_Animator()->Render(_dc);

	if (iRand == 1)
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.2f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}



	vPos.x -= WINCX / 2.f - 45.f;
	SetPos(vPos);
	Get_Animator()->Play(L"UI_battery", false);
	Get_Animator()->Render(_dc);

	//================= 배터리 출력 ====================

	if (CTimeMgr::Get_Instance()->Get_TimeSpeed() == TIME_SLOW) // 속도 느린 상태면 전기 이펙트 튀게
	{
		if (iRand > 10)
			CreateElectric();
	}

	vPos.x -= 30.f;
	vPos.y -= 1.f;
	Get_Animator()->Play(L"UI_batterypart", false);

	for (int i = 1; i <= 9; ++i)
	{
		vPos.x += 6.f;
		SetPos(vPos);
		color_Update(i, iRand);
		Get_Animator()->Render(_dc);
	}

	// ================================================

	

	// 서브웨폰 파트

	if (iRand == 2)
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.2f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}

	Get_Animator()->Play(L"UI_Weapon", false);
	vPos.x += WINCX - 110.f;
	SetPos(vPos);
	Get_Animator()->Render(_dc);

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };


	Get_Animator()->Play(L"UI_katana", false);
	vPos.x -= 16.f;
	SetPos(vPos);
	Get_Animator()->Render(_dc);

	switch (m_eSubType)
	{
	case SUB_TYPE::KNIFE:
		Get_Animator()->Play(L"SubWeapon_Knife", false);
		break;

	case SUB_TYPE::SMOKE:
		Get_Animator()->Play(L"SubWeapon_Smoke", false);
		break;

	case SUB_TYPE::BOTTLE:
		Get_Animator()->Play(L"SubWeapon_Bottle", false);
		break;

	case SUB_TYPE::BEER:
		Get_Animator()->Play(L"SubWeapon_Beer", false);
		break;

	default:
		Get_Animator()->Play(L"UI_hand", false);
		break;
	}

	vPos.x += 32.f;
	SetPos(vPos);
	Get_Animator()->Render(_dc, Color(255, 255, 255), Color(255, 255, 255));


	if (iRand == 3)
	{
		*m_colorMatrix = {
   0.3f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.3f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.3f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}

	// 시간 바
	Get_Animator()->Play(L"UI_Timer", false);
	vPos.x -= 300.f;
	SetPos(vPos);
	Get_Animator()->Render(_dc);

	

	Get_Animator()->Play(L"UI_TimeBar", false);
	m_vPos.x += 8.f;
	m_vPos.y -= 2.f;
	Get_Animator()->Render(_dc, Color(255, 0, 255), Color(255, 0, 255), m_fCurTime);

	m_vPos.x += 187.f;
	m_vPos.y -= 4.f;
	Render_Time(_dc, m_vPos);


}

void CUI_hud::Render_Time(HDC _dc, Vec2 vPos)
{
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);

	TCHAR szBuff[64];
	int iRand = random(0, 5);

	HFONT hFont = CreateFont(11, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));

	HFONT hSecFont = CreateFont(8, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0
		, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
	HFONT hDefaultFont = (HFONT)SelectObject(_dc, hFont);

	//텍스트 색상 변환
	SetTextColor(_dc, RGB(0, 0, 0));
	

	if (!g_bEnd && CTimeMgr::Get_Instance()->Get_TimeSpeed() != 0.f)
	{
		g_fTime += RealfDT;

		if (g_fTime >= 1.f)
		{
			g_fTime -= 1.f;
			g_iSec++;
		}

		if (g_iSec >= 60)
		{
			g_iSec -= 60;
			g_iMinute++;
		}
	}
	

	/*swprintf_s(szBuff, L"[%.2d:%.2f]", g_iMinute, g_fTime);
	TextOut(_dc, (int)vPos.x+1, (int)(vPos.y), szBuff, lstrlen(szBuff));*/

	//최고 기록
	vPos.x -= 60.f;
	vPos.y -= 2.f;
	int iMinute = (int)m_fTargetTime / 60;
	int iSec = (int)m_fTargetTime - iMinute * 60;
	int iTime = int(m_fTargetTime - float(iMinute * 60 + iSec));

	//그림자효과

	swprintf_s(szBuff, L"RECORD:");
	TextOut(_dc, (int)vPos.x - 53, (int)(vPos.y) + 1, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"%.2d:", iMinute);
	if (iMinute != 0)
		TextOut(_dc, (int)vPos.x + 3, (int)(vPos.y) + 1, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"%.2d.", iSec);
	TextOut(_dc, (int)vPos.x + 24, (int)(vPos.y) + 1, szBuff, lstrlen(szBuff));

	SelectObject(_dc, hSecFont);
	swprintf_s(szBuff, L"%.2d", iTime);
	TextOut(_dc, (int)vPos.x + 43, (int)(vPos.y) + 3, szBuff, lstrlen(szBuff));

	SelectObject(_dc, hFont);

	//글씨
	SetTextColor(_dc, RGB(200, 50, 200));

	swprintf_s(szBuff, L"RECORD:");
	TextOut(_dc, (int)vPos.x - 55, (int)(vPos.y) + 1, szBuff, lstrlen(szBuff));


	SetTextColor(_dc, RGB(250, 100, 250));

	swprintf_s(szBuff, L"%.2d:", iMinute);
	if (iMinute != 0)
		TextOut(_dc, (int)vPos.x + 1, (int)(vPos.y) + 1, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"%.2d.", iSec);
	TextOut(_dc, (int)vPos.x + 22, (int)(vPos.y) + 1, szBuff, lstrlen(szBuff));

	SelectObject(_dc, hSecFont);
	swprintf_s(szBuff, L"%.2d", iTime);
	TextOut(_dc, (int)vPos.x + 41, (int)(vPos.y) + 3, szBuff, lstrlen(szBuff));

	

	SelectObject(_dc, hFont);

	vPos.x += 60.f;
	vPos.y += 2.f;

	//


	swprintf_s(szBuff, L"%.2d:", g_iMinute);
	if (g_iMinute != 0)
		TextOut(_dc, (int)vPos.x+1, (int)(vPos.y)+1, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"%.2d.", g_iSec);
	TextOut(_dc, (int)vPos.x + 22, (int)(vPos.y)+1, szBuff, lstrlen(szBuff));

	SelectObject(_dc, hSecFont);
	iTime = int(g_fTime * 100.f);
	swprintf_s(szBuff, L"%.2d", iTime);
	TextOut(_dc, (int)vPos.x + 41, (int)(vPos.y) + 3, szBuff, lstrlen(szBuff));

	SelectObject(_dc, hFont);

	SetTextColor(_dc, RGB(50, 255, 255));
	swprintf_s(szBuff, L"%.2d:", g_iMinute);
	if (g_iMinute != 0)
		TextOut(_dc, (int)vPos.x, (int)(vPos.y), szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"%.2d.", g_iSec);
	TextOut(_dc, (int)vPos.x+21, (int)(vPos.y), szBuff, lstrlen(szBuff));

	SelectObject(_dc, hSecFont);
	swprintf_s(szBuff, L"%.2d", iTime);
	TextOut(_dc, (int)vPos.x + 40, (int)(vPos.y)+2, szBuff, lstrlen(szBuff));

	SelectObject(_dc, hDefaultFont);
	DeleteObject(hFont);
	DeleteObject(hSecFont);
}

void CUI_hud::color_Update(int _i, const int& _iRand)
{

	if (m_fSlowTime >= m_fSlowMaxTime / 9.f * (float)_i)
	{
		if (1 == _iRand)
		{
			*m_colorMatrix = {
			   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			   0.0f,  0.0f, 0.0f, 0.2f, 0.0f,
			   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		}
		else
		{
			*m_colorMatrix = {
			   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		}
		

	}
	else
	{
		if (1 == _iRand)
		{
			*m_colorMatrix = {
			   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			   0.0f,  0.2f, 0.0f, 0.0f, 0.0f,
			   0.0f,  0.0f, 0.2f, 0.0f, 0.0f,
			   0.0f,  0.0f, 0.0f, 0.2f, 0.0f,
			   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		}
		else
		{
			*m_colorMatrix = {
			   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			   0.0f,  0.2f, 0.0f, 0.0f, 0.0f,
			   0.0f,  0.0f, 0.2f, 0.0f, 0.0f,
			   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		}

	}
}

void CUI_hud::CreateElectric()
{
	Vec2 vPos = Get_Pos();
	float fx = random(-10, 10) * 1.f;
	float fy = random(-10, 10) * 1.f;

	if (abs(fx) < 5)
		vPos.x += 36.f;
	else
		vPos.x -= 36.f;

	Vec2 vDir = { fx, fy };

	if (0 == fx && 0 == fy)
		return;

	vDir.Normalize();

	CAbstractFactory<CEffects_Electric>::Create_Effects(this, vPos, vDir, GROUP_TYPE::UI);
}

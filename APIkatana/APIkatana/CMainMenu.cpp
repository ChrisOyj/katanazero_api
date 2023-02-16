#include "stdafx.h"
#include "CMainMenu.h"

#include "CResMgr.h"
#include "CMainGame.h"
#include "CSoundMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CEffects.h"

CMainMenu::CMainMenu()
{
	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Title_BG", L"texture\\Title\\Title_BG.bmp");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Title_BG", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Title_Fence", L"texture\\Title\\Title_Fence.bmp");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Title_Fence", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Title_Grass", L"texture\\Title\\Title_Grass.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Title_Grass", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Title_Katana", L"texture\\Title\\Title_Katana.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Title_Katana", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Title_O", L"texture\\Title\\Title_O.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Title_O", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Title_ZER", L"texture\\Title\\Title_ZER.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Title_ZER", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.06f, iCount);

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Title_Plants", L"texture\\Title\\Title_Plants.bmp");
	iCount = 12;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Title_Plants", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.08f, iCount);

	m_colorMatrix = new ColorMatrix;

	*m_colorMatrix = {
		1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	SetScale(Vec2(300.f, 90.f));
}

CMainMenu::~CMainMenu()
{
}

void CMainMenu::Update()
{
	Get_Animator()->Update();
}

void CMainMenu::Render(HDC _dc)
{
	SetPos(Vec2(320.f, 0.f));
	Vec2 vPos = Get_Pos();

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	Get_Animator()->Play(L"Title_BG", false);
	Get_Animator()->Render(_dc, Color(255, 255, 255), Color(255, 255, 255));

	Get_Animator()->Play(L"Title_Fence", false);
	Get_Animator()->Render(_dc, Color(100, 100, 100), Color(255, 255, 255));

	vPos.y += WINCY - 30.f;
	SetPos(vPos);

	Get_Animator()->Play(L"Title_Grass", false);
	Get_Animator()->Render(_dc, Color(20, 20, 20), Color(255, 255, 255));

	vPos.y -= 90.f;
	SetPos(vPos);

	int iRand = random(0, 40);

	if (iRand <= 15)
	{
		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.9f, 0.0f,
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



	vPos.y -= 120.f;
	vPos.x -= 30.f;
	SetPos(vPos);

	Get_Animator()->Play(L"Title_ZER", false);
	Get_Animator()->Render(_dc, Color(255, 255, 255), Color(255, 255, 255));

	if (iRand == 5)
		CSoundMgr::Get_Instance()->PlaySound(L"MainMenu_Text_1.wav");


	if (iRand <= 2)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"MainMenu_Text_2.wav");


		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.2f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}
	else if (iRand <= 6)
	{

		*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 0.9f, 0.0f,
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

	vPos.x += 140.f;
	SetPos(vPos);
	Get_Animator()->Play(L"Title_O", false);
	Get_Animator()->Render(_dc, Color(255, 255, 255), Color(255, 255, 255));

	*m_colorMatrix = {
   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	vPos.y -= 45.f;
	vPos.x -= 100.f;
	SetPos(vPos);
	Get_Animator()->Play(L"Title_Katana", false);
	Get_Animator()->Render(_dc);



	Vec2 vScale = Get_Scale();
	vPos.y += 175.f;
	vPos.x -= 10.f;
	SetPos(vPos);
	//검은 네모
	int LTX = (int)(vPos.x - vScale.x / 2.f);
	int LTY = (int)(vPos.y - vScale.y / 2.f);
	int RBX = (int)(vPos.x + vScale.x / 2.f);
	int RBY = (int)(vPos.y + vScale.y / 2.f);

	Point LTpoint = { LTX, LTY };
	Point LBpoint = { LTX, RBY };
	Point RTpoint = { RBX, LTY };
	Point RBpoint = { RBX, RBY };

	Graphics g(_dc);

	////////////////////////
	Point destinationPoints[] = {
		LTpoint, LBpoint, RBpoint, RTpoint };

	// Use the array of points to construct a path.
	GraphicsPath path;
	path.AddLines(destinationPoints, 4);

	//g.FillPath(&pthGrBrush, &path);
	g.FillPath(&SolidBrush(Color(150, 0, 0, 0)), &path);
	
	Get_Animator()->Play(L"Title_Plants", true);
	Get_Animator()->dir_Render(_dc, Color(50, 50, 50), Color(255, 255, 255));
	
}
#include "stdafx.h"
#include "CLaser.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"
#include "CCollider.h"

#include "CSlash.h"
#include "CEffects_Laser.h"

#include "CAbstractFactory.h"
#include "CSoundMgr.h"

CLaser::CLaser()
	: m_iLength(95)
	, m_RenderY(0)
{
	CreateCollider();

	float fWidth = 5.f;
	float fHeight = 120.f;
	Get_Collider()->SetOffSetPos(Vec2(0.f, 60.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));

	CreateAnimator();
	CTexture* pTex = nullptr;
	UINT iCount;
	float fSize;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_CeilingLaser", L"texture\\Effects\\Effects_CeilingLaser.png");
	iCount = 1;
	fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Effects_CeilingLaser", pTex, Vec2(0.f, 0.f), Vec2(fSize, pTex->Height()), Vec2(fSize, 0.f), 0.03f, iCount);
	
	/*CAnimation* pAnim = Get_Animator()->FindAnimation(L"Effects_CeilingLaser");
	for (int i = 0; i < pAnim->Get_MaxFrame(); ++i)
		pAnim->Get_Frame(i).vOffSet = Vec2(-1.f, 0.f);*/


	Get_Animator()->Play(L"Effects_CeilingLaser", false);
	SetScale(Vec2(2.f, 5.f));
}

CLaser::~CLaser()
{
}

void CLaser::OnCollisionEnter(CCollider * _pOther)
{
	CCamera::Get_Instance()->SetVibrate();

	Vec2 vPos = Get_Pos();
	vPos.y += 50.f;

	CAbstractFactory<CEffects_Laser>::Create_Effects(this, vPos, m_vRenderDir, GROUP_TYPE::LASER_ATTACK);

	CSoundMgr::Get_Instance()->PlaySound(L"Laser_1.wav");

}

void CLaser::Update()
{
	m_fTime += fDT;
	if (0.03 <= m_fTime)
	{
		m_fTime = 0.f;
		++m_RenderY;

		if (10 <= m_RenderY)
			m_RenderY = 0;
	}
	

}

void CLaser::Render(HDC _dc)
{
	CObj::Render(_dc);
	// laser Render

	Vec2 vPos = Get_Pos();
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	Vec2 vScale = Get_Scale();
	vPos.y += 10 + m_RenderY;

	for (int iTemp = 0; iTemp < 100; iTemp += 10)
	{
		int LTX = (int)(vPos.x - vScale.x / 2.f);
		int LTY = (int)(vPos.y - vScale.y / 2.f) + iTemp;
		int RBX = (int)(vPos.x + vScale.x / 2.f);
		int RBY = (int)(vPos.y + vScale.y / 2.f) + iTemp;

		if ((int)vPos.y + m_iLength - m_RenderY <= RBY) // 최대길이 설정한거보다 아래 y값이 크면
			RBY = (int)vPos.y + m_iLength - m_RenderY;

		Point LTpoint = Point(LTX, LTY);
		Point LBpoint = Point(LTX, RBY);
		Point RTpoint = Point(RBX, LTY);
		Point RBpoint = Point(RBX, RBY);

		Graphics g(_dc);

		////////////////////////
		Point destinationPoints[] = {
			LTpoint, LBpoint, RBpoint, RTpoint };

		// Use the array of points to construct a path.
		GraphicsPath path;
		path.AddLines(destinationPoints, 4);

		//g.FillPath(&pthGrBrush, &path);
		g.FillPath(&SolidBrush(Color(255, 255, 0, 0)), &path);
	}
	

}

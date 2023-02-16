#include "stdafx.h"
#include "CMansionDark.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CAnimator.h"

#include "CTimeMgr.h"

#include "CAlive.h"

#include "CAbstractFactory.h"
#include "CEffects_Glass.h"
#include "CEffects_SlashHit.h"

CMansionDark::CMansionDark()
{
	CreateAnimator();
	CTexture* pTex = nullptr;

	pTex = CResMgr::Get_Instance()->LoadTexture(L"Effects_Mansion", L"texture\\Effects\\Effects_Mansion.png");
	UINT iCount = 1;
	float fSize = pTex->Width() / (float)iCount;
	Get_Animator()->CreateAnimation(L"Effects_Mansion", pTex, Vec2(0.f, 0.f), Vec2(fSize - 1.f, pTex->Height()), Vec2(fSize, 0.f), 0.09f, iCount);

	m_pAnimator->Play(L"Effects_Mansion", false);
}

CMansionDark::~CMansionDark()
{
}

void CMansionDark::OnCollisionEnter(CCollider* _pOther)
{
	m_bCol = true;

	if (_pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::SLASH)
	{
		DeleteObject(this);
		Vec2 vPos = _pOther->Get_Obj()->Get_Owner()->Get_Pos();
		vPos.y += 50.f;
		_pOther->Get_Obj()->Get_Owner()->SetPos(vPos);
		dynamic_cast<CAlive*>(_pOther->Get_Obj()->Get_Owner())->SetBlocked();
		CreateGlass();
		CAbstractFactory<CEffects_SlashHit>::Create_Effects(nullptr, vPos, Vec2(0.f,1.f), GROUP_TYPE::EFFECTS);

	}
		
}

void CMansionDark::OnCollisionExit(CCollider* _pOther)
{
	m_bCol = false;
}

void CMansionDark::Initialize()
{
	CreateCollider();
	m_pCollider->SetScale(Vec2(80.f, 50.f));
	m_pCollider->SetOffSetPos(Vec2(0.f, -180.f));

	m_vPos = Vec2(520.f, 290.f);
	float	fWidth = (float)CResMgr::Get_Instance()->FindTexture(L"Effects_Mansion")->Get_Image()->GetWidth();
	float	fHeight = (float)CResMgr::Get_Instance()->FindTexture(L"Effects_Mansion")->Get_Image()->GetHeight();
	m_vScale = Vec2(fWidth, fHeight);

	m_vRectPos[0] = Vec2(m_vPos.x - m_vScale.x, 290.f);
	m_vRectPos[1] = Vec2(m_vPos.x, 290.f);
	m_vRectPos[2] = Vec2(m_vPos.x + m_vScale.x, 290.f);
}

void CMansionDark::Update()
{
	if (m_bCol)
	{
		if (m_iAlpha > 0)
			m_iAlpha -= (int)(350.f * RealfDT);
		
		if (m_iAlpha <= 0)
			m_iAlpha = 0;
	}
	else
	{
		if (m_iAlpha < 255)
			m_iAlpha += (int)(350.f * RealfDT);

		if (m_iAlpha >= 255)
			m_iAlpha = 255;

	}

}

void CMansionDark::Render(HDC _dc)
{
	CObj::Render(_dc);

	Vec2 vPos = CCamera::Get_Instance()->Get_RenderPos(m_vRectPos[0]);
	Vec2 vPos2 = CCamera::Get_Instance()->Get_RenderPos(m_vRectPos[1]);
	Vec2 vPos3 = CCamera::Get_Instance()->Get_RenderPos(m_vRectPos[2]);

	Graphics g(_dc);

	g.FillRectangle(&SolidBrush(Color(255, 0, 0, 0))
		, (int)(vPos.x - m_vScale.x * 0.5f)
		, (int)(vPos.y - m_vScale.y * 0.5f)
		, (int)m_vScale.x+20
		, (int)m_vScale.y);

	g.FillRectangle(&SolidBrush(Color(m_iAlpha, 0, 0, 0))
		, (int)(vPos2.x - m_vScale.x * 0.5f)
		, (int)(vPos2.y - m_vScale.y * 0.5f)
		, (int)m_vScale.x
		, (int)m_vScale.y);

	g.FillRectangle(&SolidBrush(Color(255, 0, 0, 0))
		, (int)(vPos3.x - m_vScale.x * 0.5f) - 20
		, (int)(vPos3.y - m_vScale.y * 0.5f)
		, (int)m_vScale.x + 40
		, (int)m_vScale.y);


}

void CMansionDark::CreateGlass()
{
	CCamera::Get_Instance()->SetVibrate();
	CSoundMgr::Get_Instance()->PlaySound(L"BreakWindow.wav");

	Vec2 vPos = m_vPos;
	vPos.y -= 130.f;
	vPos.x -= 55.f;


	for (int i = 0; i < 16; ++i)
	{
		float fRand = (float)random(-20, 20);
		vPos.x += (float)i;
		Vec2 vvPos = vPos;
		vvPos.y += fRand;
		CObj* pObj = CAbstractFactory<CEffects_Glass>::Create(vvPos, Vec2(0.f, 1.f), GROUP_TYPE::EFFECTS);
		dynamic_cast<CEffects_Glass*>(pObj)->SetOriginY(vvPos.y);
		CreateObject(pObj, GROUP_TYPE::EFFECTS);
	}
}

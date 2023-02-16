#include "stdafx.h"
#include "CDarkScreen.h"

#include "CCamera.h"
#include "CMainGame.h"

#include "CTimeMgr.h"

CDarkScreen::CDarkScreen()
	: m_fAlpha(0.f)
	, m_bDelete(false)
	, m_fSpeed(1500.f)
{
}

CDarkScreen::~CDarkScreen()
{
}

void CDarkScreen::Update()
{
	if (m_bDelete)
	{
		if (40.f < m_fAlpha)
			m_fAlpha -= m_fSpeed * RealfDT;
		else
		{
			m_fAlpha = 0.f;
			m_bDelete = false;
			DeleteObject(this);
		}

		return;
	}

	if (200.f > m_fAlpha)
	{
		m_fAlpha += m_fSpeed * RealfDT;
	}
}

void CDarkScreen::Render(HDC _dc)
{
	Vec2 vPos = CCamera::Get_Instance()->Get_RealPos(Vec2(0.f,0.f));
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);

	Graphics g(_dc);


	g.FillRectangle(&SolidBrush(Color(int(m_fAlpha), 0, 0, 0)), (int)vPos.x, (int)vPos.y, (int)WINCX, (int)WINCY);

}

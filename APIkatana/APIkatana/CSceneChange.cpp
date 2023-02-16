#include "stdafx.h"
#include "CSceneChange.h"

#include "CTimeMgr.h"

CSceneChange::CSceneChange()
	: m_bEnter(false)
	, m_fDelayTime(0.f)
{
}

CSceneChange::~CSceneChange()
{
}

void CSceneChange::Update()
{
	m_fTime += RealfDT;

	if (m_bEnter)
	{
		if (m_fDelayTime < m_fTime)
		{
			Vec2 vScale = Get_Scale();
			vScale.x -= 250.f * RealfDT;
			vScale.y -= 250.f * RealfDT;

			if (2.f > vScale.x)
				DeleteObject(this);

			SetScale(vScale);
		}
	}
	else
	{
		if (m_fDelayTime < m_fTime)
		{
			Vec2 vScale = Get_Scale();

			if (38.f < vScale.x)
			{
				return;
			}

			vScale.x += 250.f * RealfDT;
			vScale.y += 250.f * RealfDT;

			

			SetScale(vScale);
		}
	}
	
}

void CSceneChange::Render(HDC _dc)
{
	Vec2 vPos = Get_Pos();
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	vPos = CCamera::Get_Instance()->Get_RealPos(vPos);

	Vec2 vScale = Get_Scale();

	Graphics g(_dc);

	Point LTpoint = { (int)(vPos.x), (int)(vPos.y - vScale.y / 2.f) };
	Point LBpoint = { (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y) };
	Point RBpoint = { (int)(vPos.x), (int)(vPos.y + vScale.y / 2.f) };
	Point RTpoint = { (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y) };

	////////////////////////
	Point destinationPoints[] = {
		LTpoint, LBpoint, RBpoint, RTpoint };

	// Use the array of points to construct a path.
	GraphicsPath path;
	path.AddLines(destinationPoints, 4);

	//g.FillPath(&pthGrBrush, &path);
	g.FillPath(&SolidBrush(Color(255, 0, 0, 0)), &path);
}

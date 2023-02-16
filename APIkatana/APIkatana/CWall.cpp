#include "stdafx.h"
#include "CWall.h"

#include "CTimeMgr.h"

#include "CCollider.h"
#include "CPlayer.h"

CWall::CWall()
	: m_bWallLeft(true)
	, m_bClimb(false)
{
	CreateCollider();

	float fWidth = 10.f;
	float fHeight = 1000.f;
	//Get_Collider()->SetOffSetPos(Vec2(fWidth / -2.f, 0.f)); //오프셋 만져주면 충돌체 위치 바뀜
	Get_Collider()->SetScale(Vec2(fWidth, fHeight));

}

CWall::~CWall()
{
}

void CWall::SetScale(Vec2 _vScale)
{
	m_vScale = _vScale;
	Get_Collider()->SetScale(m_vScale);
}

void CWall::Update()
{
}

void CWall::Render(HDC _dc)
{
	Vec2 vPos = Get_Pos();
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	float fSize = 1.5f;
	Component_Render(_dc);

	//Rectangle(_dc, (int)(vPos.x - fSize), (int)(vPos.y - fSize), (int)(vPos.x + fSize), (int)(vPos.y + fSize));
}

void CWall::OnCollision(CCollider * _pOther)
{
	CObj* pOtherObj = _pOther->Get_Obj();

	if (pOtherObj->Get_ObjType() == GROUP_TYPE::MONSTER_ATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::SUBATTACK
		|| pOtherObj->Get_ObjType() == GROUP_TYPE::MOBSUBATTACK || pOtherObj->Get_ObjType() == GROUP_TYPE::GLASS)
		return;
	Vec2 vPos = Get_Pos();
	Vec2 vPlayerPos = pOtherObj->Get_Pos();
	

	//switch (pOtherObj->Get_ObjType())
	//{
	//case GROUP_TYPE::PLAYER:
		if (m_bWallLeft)
		{
			if (pOtherObj->Get_Dir().x > 0)
				return;

			if (vPlayerPos.x < vPos.x + 14.f)
				pOtherObj->SetPos(Vec2(vPos.x + 14.f, vPlayerPos.y));
		}
		else
		{
			if (pOtherObj->Get_Dir().x < 0)
				return;

			if (vPlayerPos.x > vPos.x - 14.f)
				pOtherObj->SetPos(Vec2(vPos.x - 14.f, vPlayerPos.y));
		}


		/*break;

	default:
		break;

	}*/
}

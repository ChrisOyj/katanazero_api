#include "stdafx.h"
#include "CEffects_Glass.h"

#include "CLineMgr.h"

#include "CSoundMgr.h"

CEffects_Glass::CEffects_Glass()
{

	


}

CEffects_Glass::~CEffects_Glass()
{
}

void CEffects_Glass::OnCollisionEnter(CCollider * pOther)
{
	if (pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::WALL)
	{
		m_vDir.x *= -1.f;
	}
	else if (pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::CEILING)
	{
		JUMP(0.f);
	}
	else
		m_bLand = true;

	
}

void CEffects_Glass::OnCollisionExit(CCollider * pOther)
{
	if (pOther->Get_Obj()->Get_ObjType() == GROUP_TYPE::LAND)
		m_bLand = false;
}

void CEffects_Glass::SetGreen()
{
	float fRand = (float)random(10, 40);
	fRand *= 0.01f;

	*m_colorMatrix = {
1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
0.0f,  0.0f, fRand, 0.0f, 0.0f,
0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}

void CEffects_Glass::SetOrange()
{
	float fRand = (float)random(50, 90);
	fRand *= 0.01f;

	*m_colorMatrix = {
1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
0.0f,  fRand, 0.0f, 0.0f, 0.0f,
0.0f,  0.0f, 0.1f, 0.0f, 0.0f,
0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
1.f, 0.0f, 0.0f, 0.0f, 1.0f };
}



void CEffects_Glass::Initialize()
{
	int iRand = random(1, 4);
	TCHAR strNum[8];
	_itow_s(iRand, strNum, 10);
	wstring strImage = L"Effects_Glass_";
	strImage += strNum;

	Set_Texture(strImage.c_str() , 1, 0.06f, EFFECT_TYPE::GLASS);
	m_tPhysics.fFriction = 600.f;

	//방향 랜덤

	if (m_vDir.y == 0.f) // 좌, 우
	{
		float fy = (float)random(-10, 3);

		m_vDir.x *= 5.f;
		m_vDir.y = fy;

		//m_vDir.y = -5.f;
		//m_vDir.x = fy;
	}
	else // 상, 하
	{
		float fy = (float)random(-5, 5);

		m_vDir.y *= 5.f;
		m_vDir.x = fy;
	}

	m_vDir.Normalize();

	if (0 < m_vDir.y) // 떨어지는 경우
	{
		m_tPhysics.fYSpeed = 0.f;
	}
	else
	{
		float jRand = (float)random(20, 60);
		m_tPhysics.fYSpeed = jRand * fabs(m_vDir.y);
	}
	
	m_tPhysics.fXSpeed = (float)random(200, 300);

	
}

void CEffects_Glass::Update()
{
	m_vPos.x += m_tPhysics.fXSpeed * m_vDir.x * fDT;
	m_vPos.y += m_tPhysics.fXSpeed * m_vDir.y * fDT;

	float fY = m_vPos.y;
	bool bStair;
	int iFloor;
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_vPos, 0.f, &fY, &bStair, &iFloor);

	/*if (m_fTime < 0.5f)
		bLineCol = false;*/

	if (bLineCol || m_bLand)
	{
		if (m_tPhysics.fAcc != 0.f)
		{
			int iRand = random(0, 10);
			if (iRand == 0)
				CSoundMgr::Get_Instance()->PlaySound(L"Glass_1.wav");
			else if(iRand == 1)
				CSoundMgr::Get_Instance()->PlaySound(L"Glass_2.wav");
			else if (iRand == 2)
				CSoundMgr::Get_Instance()->PlaySound(L"Glass_3.wav");

		}

		m_tPhysics.fOriginY = m_vPos.y;
		m_tPhysics.fAcc = 0.f;
		m_tPhysics.fYSpeed = 0.f;
		m_vPos.y = fY;

		if (0.f < m_tPhysics.fXSpeed) // 속도가 존재r면
			m_tPhysics.fXSpeed -= m_tPhysics.fFriction * fDT; // 속도는 m_fAirFric만큼 감소
		else
			m_tPhysics.fXSpeed = 0.f;
	}
	else
	{
		m_tPhysics.fAcc += fDT * 9.5f;

		m_vPos.y = m_tPhysics.fOriginY - ((m_tPhysics.fYSpeed * m_tPhysics.fAcc) - (9.8f * 0.5f * m_tPhysics.fAcc * m_tPhysics.fAcc));
		m_fTheta += 10.f * fDT;

		if (0.f < m_tPhysics.fXSpeed) // 속도가 존재하면
			m_tPhysics.fXSpeed -= m_tPhysics.fAirFric * fDT; // 속도는 m_fAirFric만큼 감소
		else
			m_tPhysics.fXSpeed = 0.f;

	}



	m_fTime += fDT;

	if (!m_pCollider && 0.5f < m_fTime)
	{
		CreateCollider();
		m_pCollider->SetScale(Vec2(4.f, 4.f));
	}

	if (5.f < m_fTime)
		DeleteObject(this);
}

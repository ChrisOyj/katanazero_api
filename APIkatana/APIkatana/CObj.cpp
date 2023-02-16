#include "stdafx.h"
#include "CObj.h"

#include "CAnimator.h"


CObj::CObj()
	: m_objType(GROUP_TYPE::DEFAULT)
	, m_fTime(0.f)
	, m_fAcc(0.f)
	, m_vPos{}
	, m_vScale{}
	, m_fRatio(1.f)
	, m_fTheta(0.f)
	, m_vDir{ 1.f, 0.f }
	, m_vRenderDir{1.f, 0.f}
	, m_pCollider(nullptr)
	, m_bColliderVisible(false)
	, m_bCollision(true)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
	, m_colorMatrix(nullptr)
	, m_pOwner(nullptr)
{
}

CObj::CObj(const CObj & _origin)
	: m_objType(_origin.m_objType)
	, m_fTime(0.f)
	, m_fAcc(0.f)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_fRatio(_origin.m_fRatio)
	, m_fTheta(_origin.m_fTheta)
	, m_vRenderDir(_origin.m_vRenderDir)
	, m_bColliderVisible(_origin.m_bColliderVisible)
	, m_bCollision(_origin.m_bCollision)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
	, m_colorMatrix(nullptr)
	, m_pOwner(_origin.m_pOwner)
{

	if (_origin.m_pCollider) // �浹ü�� ���� ���� �ֽ�
	{
		m_pCollider = new CCollider(*_origin.m_pCollider); // ���� �ݶ��̴��� �־ �ݶ��̴� ���������
		m_pCollider->m_pOwner = this;
	}
	if (_origin.m_pAnimator) // �ִϸް� ���� ���� �ֽ�
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator); // ���� �ִϸ�
		m_pAnimator->m_pOwner = this;
	}
}

CObj::~CObj()
{
	if (m_pCollider)
		delete m_pCollider;

	if (m_pAnimator)
		delete m_pAnimator;

	if (m_colorMatrix)
		delete m_colorMatrix;
}


void CObj::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this; // �ֹ� ����

}

void CObj::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this; // �ֹ� ����
}

void CObj::Final_Update()
{
	if (m_pCollider)
		m_pCollider->Final_Update();
}

void CObj::Render(HDC _dc)
{
	if (nullptr != m_pCollider && m_bColliderVisible)
		m_pCollider->Render(_dc);

	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);

}

void CObj::Component_Render(HDC _dc)
{
	if (nullptr != m_pCollider && m_bColliderVisible)
		m_pCollider->Render(_dc);
}

void CObj::Component_dir_Render(HDC _dc)
{
	if (nullptr != m_pCollider && m_bColliderVisible)
		m_pCollider->dir_Render(_dc);
}

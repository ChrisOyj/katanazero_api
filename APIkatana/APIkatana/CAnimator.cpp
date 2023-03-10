#include "stdafx.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::Update()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Update();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
		if (false == m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(m_pCurAnim->Get_MaxFrame() - 1);
		}
	}
}

void CAnimator::speed_Update()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->speed_Update();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
		if (false == m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(m_pCurAnim->Get_MaxFrame() - 1);
		}
	}
}

void CAnimator::Render(HDC _dc, Color _ColorKey, Color _ColorKey2, float _fXRatio)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->Render(_dc,_ColorKey, _ColorKey2, _fXRatio);
}

//void CAnimator::dir_Render(HDC _dc)
//{
//	if (nullptr != m_pCurAnim)
//		m_pCurAnim->dir_Render(_dc);
//}

void CAnimator::dir_Render(HDC _dc, Color _ColorKey, Color _ColorKey2)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->dir_Render(_dc, _ColorKey, _ColorKey2);
}



void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex
	, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new CAnimation;


	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.emplace(_strName, pAnim);
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_strCurAnim = _strName;
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

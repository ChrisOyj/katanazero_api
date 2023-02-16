#include "stdafx.h"
#include "CAnimation.h"

#include "CCamera.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CObj.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

	}
}

void CAnimation::speed_Update()
{
	if (m_bFinish)
		return;

	m_fAccTime += RealfDT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

	}
}

void CAnimation::Render(HDC _dc, Color _ColorKey, Color _ColorKey2, float _fXRatio)
{
	if (m_bFinish)
		return;

	//============vPos 세팅==============
	CObj* pObj = m_pAnimator->Get_Owner();

	Vec2 vPos = pObj->Get_Pos();
	vPos += m_vecFrm[m_iCurFrm].vOffSet; // OffSet만큼 추가로 이동시키고 출력

	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	//======================================
	

	Graphics g(_dc);

	ImageAttributes imgAttr; 
	ColorMatrix* pColorMatrix = pObj->Get_ColorMatrix();
	imgAttr.SetColorKey(_ColorKey, _ColorKey2, ColorAdjustTypeBitmap);
	imgAttr.SetColorMatrix(pColorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	
	//2가지 기능
	// 1. SetColorKey

	float fRatio = pObj->Get_Ratio();

	int LTX = (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
	int LTY = (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);
	int RBX = (int)(vPos.x + m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f) - (int)(m_vecFrm[m_iCurFrm].vSlice.x * (1.f-_fXRatio));
	int RBY = (int)(vPos.y + m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);

	Point LTpoint, RTpoint, LBpoint;


	if (0 <= pObj->Get_RenderDir().x)
	{
		LTpoint = Point(LTX, LTY);
		RTpoint = Point(RBX, LTY);
		LBpoint = Point(LTX, RBY);
		
		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(m_pTex->Get_Image()  // 출력할 이미지 (Image*)
			, destinationPoints			// 포인트 배열
			, 3							// 포인트 배열의 크기
			, (int)m_vecFrm[m_iCurFrm].vLT.x	// 이미지의 LT 좌표
			, (int)m_vecFrm[m_iCurFrm].vLT.y
			, (int)m_vecFrm[m_iCurFrm].vSlice.x // 얼마만큼 불러올지
			, (int)m_vecFrm[m_iCurFrm].vSlice.y
			, UnitPixel, &imgAttr, NULL, NULL); // 몰라도댐
	}
	else
	{

		//Point destinationPoints[] = {
		//Point(LTX + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio), LTY),   // destination for upper-left point of original
		//Point(LTX - (RBX - LTX) + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio) , LTY),  // destination for upper-right point of original
		//Point(LTX + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio), RBY) };  // destination for lower-left point of original

		LTpoint = Point(LTX + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio), LTY);
		RTpoint = Point(LTX - (RBX - LTX) + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio), LTY);
		LBpoint = Point(LTX + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio), RBY);

		Point destinationPoints[] = {
		LTpoint,   // destination for upper-left point of original
		RTpoint,  // destination for upper-right point of original
		LBpoint };  // destination for lower-left point of original

		g.DrawImage(m_pTex->Get_Image()
			, destinationPoints, 3
			, (int)m_vecFrm[m_iCurFrm].vLT.x
			, (int)m_vecFrm[m_iCurFrm].vLT.y
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y
			, UnitPixel, &imgAttr, NULL, NULL);
	}

	if (CSceneMgr::Get_Instance()->IsSave())
	{
		ReplayInfo* replay = new ReplayInfo(m_pTex->Get_Image(), vPos, pObj->Get_RenderDir(), CCamera::Get_Instance()->Get_LookAt(), fRatio
			, (int)m_vecFrm[m_iCurFrm].vLT.x
			, (int)m_vecFrm[m_iCurFrm].vLT.y
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y, nullptr);

		CSceneMgr::Get_Instance()->AddReplay(replay);
	}

	


}

void CAnimation::dir_Render(HDC _dc, Color _ColorKey, Color _ColorKey2)
{
	if (m_bFinish)
		return;

	CObj* pObj = m_pAnimator->Get_Owner();
	Vec2 vDir = pObj->Get_Dir();
	Vec2 vPos = pObj->Get_Pos();
	vPos += m_vecFrm[m_iCurFrm].vOffSet; // OffSet만큼 추가로 이동시키고 출력
	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
	float fTheta = pObj->Get_Theta();

	Graphics g(_dc);

	ImageAttributes imgAttr;
	ColorMatrix* pColorMatrix = pObj->Get_ColorMatrix();
	imgAttr.SetColorKey(_ColorKey, _ColorKey2, ColorAdjustTypeBitmap);
	imgAttr.SetColorMatrix(pColorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	float fRatio = pObj->Get_Ratio();

	int LTX = (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
	int LTY = (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);
	int RBX = (int)(vPos.x + m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
	int RBY = (int)(vPos.y + m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);

	Point LTpoint = rotate(vPos, Point(LTX, LTY), fTheta);
	Point RTpoint = rotate(vPos, Point(RBX, LTY), fTheta);
	Point LBpoint = rotate(vPos, Point(LTX, RBY), fTheta);

	Point destinationPoints[] = {
	LTpoint,   // destination for upper-left point of original
	RTpoint,  // destination for upper-right point of original
	LBpoint };  // destination for lower-left point of original

	g.DrawImage(m_pTex->Get_Image()
		, destinationPoints, 3
		, (int)m_vecFrm[m_iCurFrm].vLT.x
		, (int)m_vecFrm[m_iCurFrm].vLT.y
		, (int)m_vecFrm[m_iCurFrm].vSlice.x
		, (int)m_vecFrm[m_iCurFrm].vSlice.y
		, UnitPixel, &imgAttr, NULL, NULL);

	if (CSceneMgr::Get_Instance()->IsSave())
	{
		ReplayInfo* replay = new ReplayInfo(m_pTex->Get_Image(), vPos, vDir, CCamera::Get_Instance()->Get_LookAt(), fRatio
			, (int)m_vecFrm[m_iCurFrm].vLT.x
			, (int)m_vecFrm[m_iCurFrm].vLT.y
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y, pColorMatrix);

		CSceneMgr::Get_Instance()->AddReplay(replay);
	}

}

//void CAnimation::dir_Render(HDC _dc, Color _ColorKey, Color _ColorKey2)
//{
//	if (m_bFinish)
//		return;
//
//	CObj* pObj = m_pAnimator->Get_Owner();
//	Vec2 vDir = pObj->Get_Dir();
//	Vec2 vPos = pObj->Get_Pos();
//	vPos += m_vecFrm[m_iCurFrm].vOffSet; // OffSet만큼 추가로 이동시키고 출력
//
//	vPos = CCamera::Get_Instance()->Get_RenderPos(vPos);
//
//	Graphics g(_dc);
//
//	ImageAttributes imgAttr;
//	ColorMatrix* pColorMatrix = pObj->Get_ColorMatrix();
//
//	imgAttr.SetColorKey(_ColorKey, _ColorKey2, ColorAdjustTypeBitmap);
//	imgAttr.SetColorMatrix(pColorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
//
//	float fRatio = pObj->Get_Ratio();
//
//	int LTX = (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
//	int LTY = (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);
//	int RBX = (int)(vPos.x + m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
//	int RBY = (int)(vPos.y + m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);
//
//	float fAngle = acos(vDir.x); // 각도 구하기
//
//	if (0 > vDir.y)
//	{
//		fAngle *= -1.f;
//	}
//
//
//	Point LTpoint = rotate(vPos, Point(LTX, LTY), fAngle);
//	Point RTpoint = rotate(vPos, Point(RBX, LTY), fAngle);
//	Point LBpoint = rotate(vPos, Point(LTX, RBY), fAngle);
//
//	Point destinationPoints[] = {
//	LTpoint,   // destination for upper-left point of original
//	RTpoint,  // destination for upper-right point of original
//	LBpoint };  // destination for lower-left point of original
//
//	g.DrawImage(m_pTex->Get_Image()
//		, destinationPoints, 3
//		, (int)m_vecFrm[m_iCurFrm].vLT.x
//		, (int)m_vecFrm[m_iCurFrm].vLT.y
//		, (int)m_vecFrm[m_iCurFrm].vSlice.x
//		, (int)m_vecFrm[m_iCurFrm].vSlice.y
//		, UnitPixel, &imgAttr, NULL, NULL);
//	
//	if (CSceneMgr::Get_Instance()->IsSave())
//		{
//			ReplayInfo* replay = new ReplayInfo(m_pTex->Get_Image(), vPos, vDir, CCamera::Get_Instance()->Get_LookAt(), fRatio
//			, (int)m_vecFrm[m_iCurFrm].vLT.x
//			, (int)m_vecFrm[m_iCurFrm].vLT.y
//			, (int)m_vecFrm[m_iCurFrm].vSlice.x
//			, (int)m_vecFrm[m_iCurFrm].vSlice.y, nullptr);
//
//			CSceneMgr::Get_Instance()->AddReplay(replay);
//		}
//	
//}


void CAnimation::after_Render(HDC _dc, Vec2 _vPos, float _dir, float _fRatio, ColorMatrix* _colormatrix)
{
	if (m_bFinish)
		return;

	_vPos += m_vecFrm[m_iCurFrm].vOffSet; // OffSet만큼 추가로 이동시키고 출력

	_vPos = CCamera::Get_Instance()->Get_RenderPos(_vPos);

	Graphics g(_dc);

	ImageAttributes imgAttr;
	imgAttr.SetColorMatrix(_colormatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	float fRatio = _fRatio;


	if (0 <= _dir)
	{
		g.DrawImage(m_pTex->Get_Image()
			, Rect((int)(_vPos.x - m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f)
				, (int)(_vPos.y - m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f)
				, (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio)
				, (int)(m_vecFrm[m_iCurFrm].vSlice.y * fRatio))
			, (int)m_vecFrm[m_iCurFrm].vLT.x
			, (int)m_vecFrm[m_iCurFrm].vLT.y
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y
			, UnitPixel, &imgAttr, NULL, NULL);
	}
	else
	{
		int LTX = (int)(_vPos.x - m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
		int LTY = (int)(_vPos.y - m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);
		int RBX = (int)(_vPos.x + m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
		int RBY = (int)(_vPos.y + m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);

		Point destinationPoints[] = {
		Point(LTX + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio), LTY),   // destination for upper-left point of original
		Point(LTX - (RBX - LTX) + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio) , LTY),  // destination for upper-right point of original
		Point(LTX + (int)(m_vecFrm[m_iCurFrm].vSlice.x * fRatio), RBY) };  // destination for lower-left point of original


		g.DrawImage(m_pTex->Get_Image()
			, destinationPoints, 3
			, (int)m_vecFrm[m_iCurFrm].vLT.x
			, (int)m_vecFrm[m_iCurFrm].vLT.y
			, (int)m_vecFrm[m_iCurFrm].vSlice.x
			, (int)m_vecFrm[m_iCurFrm].vSlice.y
			, UnitPixel, &imgAttr, NULL, NULL);
	}
}

void CAnimation::dir_after_Render(HDC _dc, Vec2 _vPos, float _fTheta, float _fRatio, ColorMatrix * _colormatrix)
{
	if (m_bFinish)
		return;

	_vPos += m_vecFrm[m_iCurFrm].vOffSet; // OffSet만큼 추가로 이동시키고 출력

	_vPos = CCamera::Get_Instance()->Get_RenderPos(_vPos);

	Graphics g(_dc);

	ImageAttributes imgAttr;
	imgAttr.SetColorKey(Color(255, 255, 255), Color(255, 255, 255), ColorAdjustTypeBitmap);
	imgAttr.SetColorMatrix(_colormatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	float fRatio = _fRatio;

	int LTX = (int)(_vPos.x - m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
	int LTY = (int)(_vPos.y - m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);
	int RBX = (int)(_vPos.x + m_vecFrm[m_iCurFrm].vSlice.x * fRatio / 2.f);
	int RBY = (int)(_vPos.y + m_vecFrm[m_iCurFrm].vSlice.y * fRatio / 2.f);

	Point LTpoint = rotate(_vPos, Point(LTX, LTY), _fTheta);
	Point RTpoint = rotate(_vPos, Point(RBX, LTY), _fTheta);
	Point LBpoint = rotate(_vPos, Point(LTX, RBY), _fTheta);

	Point destinationPoints[] = {
	LTpoint,   // destination for upper-left point of original
	RTpoint,  // destination for upper-right point of original
	LBpoint };  // destination for lower-left point of original

	g.DrawImage(m_pTex->Get_Image()
		, destinationPoints, 3
		, (int)m_vecFrm[m_iCurFrm].vLT.x
		, (int)m_vecFrm[m_iCurFrm].vLT.y
		, (int)m_vecFrm[m_iCurFrm].vSlice.x
		, (int)m_vecFrm[m_iCurFrm].vSlice.y
		, UnitPixel, &imgAttr, NULL, NULL);
}

void CAnimation::Create(CTexture * _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (int)i;

		m_vecFrm.push_back(frm);
	}
}

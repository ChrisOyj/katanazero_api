#pragma once
#include "CSoundMgr.h"

class CObj;

class CCamera
{
	SINGLE(CCamera)

public:
	float		Get_Vibrate() { return m_fMaxVibSpeed; }
	Vec2		Get_LookAt() { return m_vLookAt; }
	Vec2		Get_RenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	POINT		Get_RenderPos(POINT _pObjPos) {
		POINT pt = { _pObjPos.x - (LONG)m_vDiff.x , _pObjPos.y - (LONG)m_vDiff.y };
		return pt;
	}

	Vec2		Get_RealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	POINT		Get_RealPos(POINT _pObjPos) {
		POINT pt = { _pObjPos.x + (LONG)m_vDiff.x , _pObjPos.y + (LONG)m_vDiff.y };
		return pt;
	}
	float		Get_Zoom() { return m_fCurZoom; }

	void		SetVibSpeed(float _f) { m_fMaxVibSpeed = _f; }
	void		SetVibrate() { m_bVibrate = true; m_vPrevLook = m_vLookAt; m_fVibSpeed = m_fMaxVibSpeed; }
	void		SetLookAt(Vec2 _vLook)	{ m_vLookAt = _vLook; }
	void		SetTarget(CObj* _pTarget) { m_pTargetObj = _pTarget; }
	void		SetEdit(bool _b) { m_bEdit = _b; }
	void		SetZoom() { 
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Jump.wav");

		if (m_fTargetZoom == 1.f)
		{
			m_fTargetZoom = ZOOM;
			m_bZoom = true;
		}
		else
		{
			m_fTargetZoom = 1.f;
			m_bZoom = false;
		}
		 }
	void		SetZoom(float _f) {
		m_fTargetZoom = _f;
		if (m_fTargetZoom == 1.f)
			m_bZoom = false;
		else
			m_bZoom = true;
	}
	
	friend class CUI_hud;

public:
	void Update();
	void ZoomSet(HDC _dc);

private:
	void Update_Edit();

	void Physics_Update();
	void Screen_Update();
	void Vibrate_Update();
	void CalDiff();
	void CreateDarkScreen();

private:
	bool			m_bVibrate;
	int				m_iCount;

	

	Vec2		m_vLookAt;		//카메라가 보는 위치
	Vec2		m_vPrevLook;

	Vec2		m_vDir;			//카메라 이동 방향
	float		m_fTime;
	float		m_fVibSpeed;
	float		m_fMaxVibSpeed;
	float		m_fSpeed;

	bool		m_bZoom;
	float		m_fCurZoom;
	float		m_fTargetZoom;
	float		m_fZoomSpeed;
	float		m_fTheta = 0.f;

	bool		m_bEdit = false;

	CObj*		m_pTargetObj;	//카메라 타겟 오브젝트
	Vec2		m_vDiff;		// 해상도 중심위치와, 카메라 LookAt간의 차이 값


};


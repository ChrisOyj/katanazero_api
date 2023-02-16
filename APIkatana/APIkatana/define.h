#pragma once

#define WINCX		640
#define WINCY		360

#define TILECX		64
#define TILECY		64

#define TILEX		30
#define TILEY		20

#define	PURE		= 0

#define SINGLE(type) public:\
					static type* Get_Instance() {\
						static type mgr;\
						return &mgr;\
					}\
					private:\
					explicit type();\
					~type();

#define KEY(key, state) CKeyMgr::Get_Instance()->Get_KeyState(KEY::key) == KEY_STATE::state

#define fDT CTimeMgr::Get_Instance()->Get_fDT()
#define RealfDT CTimeMgr::Get_Instance()->Get_RealfDT()
#define DT CTimeMgr::Get_Instance()->Get_DT()

#define ZOOM 0.5f

#define PI 3.1415926535f

#define CLONE(type) type* Clone() { return new type(*this); }

#define JUMP(power) m_tPhysics.fOriginY = m_vPos.y;\
					m_tPhysics.fAcc = 0.f;\
					m_tPhysics.fYSpeed = power;

#define		MIN_STR			64
#define		MAX_STR			256

#define		TIME_SLOW		0.2f

#define		REALPOS(pos) CCamera::Get_Instance()->Get_RealPos(pos)

extern		HWND			g_hwnd;
extern		float			g_fSound;
extern		int				g_iSound;
extern		int				g_iVibSpeed;
extern		bool			g_bCinema;
extern		bool			g_bLaser;
extern		float			g_fTime;
extern		int				g_iSec;
extern		int				g_iMinute;
extern		bool			g_bEnd;
extern		bool			g_bGhost;
extern		bool			g_bSuper;
		


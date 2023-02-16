#pragma once
#include "CCamera.h"
#include "CCollider.h"

class CAnimator;

class CObj abstract
{
public:
	CObj();
	CObj(const CObj& _origin);
	virtual ~CObj();

	virtual CObj* Clone() PURE;


public: // Get_Set
	const GROUP_TYPE	Get_ObjType() const { return m_objType; }
	Vec2				Get_Pos() { return m_vPos; }
	Vec2				Get_Scale() { return m_vScale; }
	float				Get_Ratio() { return m_fRatio; }
	float				Get_Theta() { return m_fTheta; }
	Vec2				Get_Dir() { return m_vDir; }
	Vec2				Get_RenderDir() { return m_vRenderDir; }
	ColorMatrix*		Get_ColorMatrix() { return m_colorMatrix; }
	CObj*				Get_Owner() { return m_pOwner; }
	float				Get_Time() { return m_fTime; }

	CCollider*			Get_Collider() { return m_pCollider; }
	CAnimator*			Get_Animator() { return m_pAnimator; }

	bool				IsDead() { return !m_bAlive; }
	bool				Get_Collision() { return m_bCollision; }


	void				SetObjType(GROUP_TYPE _eType) { m_objType = _eType; }
	void				SetPos(Vec2 _vPos) { m_vPos = _vPos; };
	virtual void				SetScale(Vec2 _vScale) { m_vScale = _vScale; };
	void				SetRatio(float _vratio) { m_fRatio = _vratio; }
	void				SetDir(Vec2 _vDir) { m_vDir = _vDir; m_vDir.Normalize(); }
	void				SetRenderDir(Vec2 _vDir) { m_vRenderDir = _vDir; }
	void				SetDirX(float _f) { m_vDir.x = _f; }
	void				SetDirY(float _f) { m_vDir.y = _f; }
	virtual void				SetColorMatrix(ColorMatrix _ImgAttr) { *m_colorMatrix = _ImgAttr; }
	void				SetColliderVisible(bool _bool) { m_bColliderVisible = _bool; }
	void				SetCollision(bool _bool) { m_bCollision = _bool; }
	void				SetOwner(CObj* _pOwner) { m_pOwner = _pOwner; }
	void				SetDead() { m_bAlive = false; } // 오로지 이벤트 처리로만 할거라 프라이빗.
	void				SetAlive() { m_bAlive = true; } // 오로지 이벤트 처리로만 할거라 프라이빗.
	void				SetColSize(Vec2 _vScale) { m_pCollider->SetScale(_vScale); }
	void				SetTheta(float _f) { m_fTheta = _f; }




public://Component
	void			CreateCollider();
	void			CreateAnimator();
	void			CreateColorMatrix() { 
		m_colorMatrix = new ColorMatrix;

		*m_colorMatrix = {
			1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}


public:
	virtual void	OnCollision(CCollider* _pOther) {};
	virtual void	OnCollisionEnter(CCollider* _pOther) {};
	virtual void	OnCollisionExit(CCollider* _pOther) {};

public:
	virtual	void	Initialize() {}
	virtual void	Update() PURE;
	virtual void	Final_Update() final;

	virtual void	Render(HDC _dc);
	void			Component_Render(HDC _dc);
	void			Component_dir_Render(HDC _dc);

	friend class CEventMgr;

protected:
	GROUP_TYPE		m_objType;
	CObj*			m_pOwner;
	ColorMatrix*	m_colorMatrix;

	Vec2			m_vPos;
	Vec2			m_vScale;
	Vec2			m_vDir;
	Vec2			m_vRenderDir;
	float			m_fRatio;
	float			m_fTheta;

	//Component
	CCollider*		m_pCollider; 
	CAnimator*		m_pAnimator;

	bool			m_bColliderVisible;
	bool			m_bAlive;
	bool			m_bCollision;		// 충돌 기능 켜기, 끄기

	float			m_fTime;
	float			m_fAcc;



};


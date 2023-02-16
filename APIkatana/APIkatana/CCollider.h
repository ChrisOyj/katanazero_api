#pragma once

class CObj;

class CCollider
{
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

public:
	void SetOffSetPos(Vec2 _vPos) { m_vOffSetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetDir(Vec2 _vDir) { m_vDir = _vDir; m_vDir.Normalize(); }
	void SetCircle() { m_bCircle = true; }

	Vec2 Get_OffSetPos() { return m_vOffSetPos; }
	Vec2 Get_Scale() { return m_vScale; }
	Vec2 Get_FinalPos() { return m_vFinalPos; }
	Vec2 Get_Dir() { return m_vDir; }
	CObj* Get_Obj() { return m_pOwner; }
	bool IsCircle() { return m_bCircle; }

	UINT Get_ID() { return m_iID; }



	POINT	Get_LTPoint() { return m_LTPoint; }
	POINT	Get_RTPoint() { return m_RTPoint; }
	POINT	Get_LBPoint() { return m_LBPoint; }
	POINT	Get_RBPoint() { return m_RBPoint; }


public:
	void	Initialize();
	void Final_Update();
	void Render(HDC _dc);
	void dir_Render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther); // 충돌중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);


	CCollider& operator = (CCollider& _origin) = delete; // 디폴트 오퍼레이터 함수를 삭제해 버린 것

private:
	static UINT g_iNextID;

	CObj* m_pOwner; // Collider를 소유하고 있는 오브젝트
	Vec2 m_vOffSetPos; // 기준 위치와의 거리 (OffSet)
	Vec2 m_vFinalPos; // 진짜 위치

	Vec2 m_vScale; // 충돌체 크기
	Vec2 m_vDir;

	UINT m_iID; // 충돌체 고유한 ID 값
	int m_iCol;

	bool m_bCircle;

	POINT		m_LTPoint;
	POINT		m_RTPoint;
	POINT		m_LBPoint;
	POINT		m_RBPoint;




	friend class CObj;
};


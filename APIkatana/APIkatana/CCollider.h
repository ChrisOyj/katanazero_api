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
	void OnCollision(CCollider* _pOther); // �浹���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);


	CCollider& operator = (CCollider& _origin) = delete; // ����Ʈ ���۷����� �Լ��� ������ ���� ��

private:
	static UINT g_iNextID;

	CObj* m_pOwner; // Collider�� �����ϰ� �ִ� ������Ʈ
	Vec2 m_vOffSetPos; // ���� ��ġ���� �Ÿ� (OffSet)
	Vec2 m_vFinalPos; // ��¥ ��ġ

	Vec2 m_vScale; // �浹ü ũ��
	Vec2 m_vDir;

	UINT m_iID; // �浹ü ������ ID ��
	int m_iCol;

	bool m_bCircle;

	POINT		m_LTPoint;
	POINT		m_RTPoint;
	POINT		m_LBPoint;
	POINT		m_RBPoint;




	friend class CObj;
};


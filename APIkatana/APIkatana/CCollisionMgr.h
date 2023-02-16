#pragma once

class CCollider;

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;

};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

public:
	void Initialize();
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset();

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void OBB_Update(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);


	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);
	bool IsOBBCollision(CCollider* _pLeft, CCollider* _pRight);


private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];
	map<ULONGLONG, bool> m_mapColInfo;//충돌체 간의 이전 프레임 충돌 정보

};


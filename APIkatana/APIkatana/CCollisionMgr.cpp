#include "stdafx.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"

#include "CScene.h"
#include "CObj.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{
	CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::LAND);


	CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::CEILING);
	CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SUBWEAPON);
	CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MANSION);

	CheckGroup(GROUP_TYPE::MONSTER_HITBOX, GROUP_TYPE::CEILING);
	CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::LAND);
	CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WALL);
	CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MANSION);
	CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::SUBWEAPON);

	CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MONSTER_HITBOX);
	CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MONSTER_ATTACK);
	CheckGroup(GROUP_TYPE::SLASH, GROUP_TYPE::MANSION);

	CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::PLAYER_HITBOX);
	CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::WALL);
	CheckGroup(GROUP_TYPE::MONSTER_ATTACK, GROUP_TYPE::LAND);
	CheckGroup(GROUP_TYPE::MONSTER_SIGHT, GROUP_TYPE::PLAYER_HITBOX);

	CheckGroup(GROUP_TYPE::DRAGON, GROUP_TYPE::DOOR);

	CheckGroup(GROUP_TYPE::LASER, GROUP_TYPE::PLAYER);
	CheckGroup(GROUP_TYPE::LASER, GROUP_TYPE::MONSTER);
	CheckGroup(GROUP_TYPE::LASER_ATTACK, GROUP_TYPE::PLAYER_HITBOX);
	CheckGroup(GROUP_TYPE::LASER_ATTACK, GROUP_TYPE::PLAYER);
	CheckGroup(GROUP_TYPE::LASER_ATTACK, GROUP_TYPE::MONSTER_HITBOX);
	CheckGroup(GROUP_TYPE::LASER_ATTACK, GROUP_TYPE::MONSTER);

	CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::MONSTER_HITBOX);
	CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::WALL);
	CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::CEILING);
	CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::LAND);
	CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::MONSTER_ATTACK);
	CheckGroup(GROUP_TYPE::SUBATTACK, GROUP_TYPE::MOBSUBATTACK);

	CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::PLAYER_HITBOX);
	CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::WALL);
	CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::CEILING);
	CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::LAND);
	CheckGroup(GROUP_TYPE::MOBSUBATTACK, GROUP_TYPE::SLASH);

	CheckGroup(GROUP_TYPE::SMOKE, GROUP_TYPE::SMOKE);
	CheckGroup(GROUP_TYPE::SMOKE, GROUP_TYPE::PLAYER_HITBOX);
	//CheckGroup(GROUP_TYPE::SMOKE, GROUP_TYPE::SLASH);
	CheckGroup(GROUP_TYPE::SMOKE, GROUP_TYPE::MONSTER_HITBOX);

	CheckGroup(GROUP_TYPE::GLASS, GROUP_TYPE::WALL);
	CheckGroup(GROUP_TYPE::GLASS, GROUP_TYPE::CEILING);
	CheckGroup(GROUP_TYPE::GLASS, GROUP_TYPE::LAND);

}

CCollisionMgr::~CCollisionMgr()
{}


void CCollisionMgr::Initialize()
{
}

void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol) // 체크 박스 반만 해야되기 때문에 컬럼은 row부터
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}

void CCollisionMgr::OBB_Update(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::Get_Instance()->Get_CurScene();

	const vector<CObj*>& vecLeft = pCurScene->Get_GroupObject(_eLeft);
	const vector<CObj*>& vecRight = pCurScene->Get_GroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;


	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->Get_Collider()) // 둘중 하나라도 충돌체가 없으면 넘어가기
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->Get_Collider() || vecLeft[i] == vecRight[j]) // 나 자신과 충돌 방지
				continue;


			CCollider* Left_Collider = vecLeft[i]->Get_Collider();
			CCollider* Right_Collider = vecRight[j]->Get_Collider();

			COLLIDER_ID ID;
			ID.Left_id = Left_Collider->Get_ID();		// 4바이트
			ID.Right_id = Right_Collider->Get_ID();		// 4바이트
			//합쳐서 나온 8바이트는 절대 안겹침.

			iter = m_mapColInfo.find(ID.ID);

			//충돌 정보가 아예 미등록 상태인 경우
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false)); // 아예 등록조차 안되있던 상황이므로 맵에 추가
				iter = m_mapColInfo.find(ID.ID); // 넣은 값 다시 이터로 받고
			}

			//진짜 충돌 검사
			if (IsOBBCollision(Left_Collider, Right_Collider))
			{
				//현재 충돌 중
				if (iter->second) // 지금도 충돌중인데 이전에도 충돌중인 상황
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead()) // 둘중 하나가 죽은 오브젝트일 경우.
					{
						Left_Collider->OnCollisionExit(Right_Collider);
						Right_Collider->OnCollisionExit(Left_Collider);
						iter->second = false;
					}

					Left_Collider->OnCollision(Right_Collider);
					Right_Collider->OnCollision(Left_Collider);
				}
				else // 이번에 최초 충돌
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead()
						&& vecLeft[i]->Get_Collision() && vecRight[j]->Get_Collision()) // 둘다 살아있을 때만 실행하도록
					{
						Left_Collider->OnCollisionEnter(Right_Collider);
						Right_Collider->OnCollisionEnter(Left_Collider);
						iter->second = true;
					}
				}
			}
			else // 현재 충돌중이지 않음
			{
				if (iter->second) // 방금까지 충돌중이었음, 충돌이 막 벗어나진 시점
				{
					Left_Collider->OnCollisionExit(Right_Collider);
					Right_Collider->OnCollisionExit(Left_Collider);
					iter->second = false;
				}
			}
		}
	}
}


void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::Get_Instance()->Get_CurScene();

	const vector<CObj*>& vecLeft = pCurScene->Get_GroupObject(_eLeft);
	const vector<CObj*>& vecRight = pCurScene->Get_GroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;


	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->Get_Collider()) // 둘중 하나라도 충돌체가 없으면 넘어가기
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->Get_Collider() || vecLeft[i] == vecRight[j]) // 나 자신과 충돌 방지
				continue;

			CCollider* Left_Collider = vecLeft[i]->Get_Collider();
			CCollider* Right_Collider = vecRight[j]->Get_Collider();

			COLLIDER_ID ID;
			ID.Left_id = Left_Collider->Get_ID();		// 4바이트
			ID.Right_id = Right_Collider->Get_ID();		// 4바이트
			//합쳐서 나온 8바이트는 절대 안겹침.

			iter = m_mapColInfo.find(ID.ID);

			//충돌 정보가 아예 미등록 상태인 경우
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false)); // 아예 등록조차 안되있던 상황이므로 맵에 추가
				iter = m_mapColInfo.find(ID.ID); // 넣은 값 다시 이터로 받고
			}

			//진짜 충돌 검사
			if (IsCollision(Left_Collider, Right_Collider))
			{
				//현재 충돌 중
				if (iter->second) // 지금도 충돌중인데 이전에도 충돌중인 상황
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead()) // 둘중 하나가 죽은 오브젝트일 경우.
					{
						Left_Collider->OnCollisionExit(Right_Collider);
						Right_Collider->OnCollisionExit(Left_Collider);
						iter->second = false;
					}

					Left_Collider->OnCollision(Right_Collider);
					Right_Collider->OnCollision(Left_Collider);
				}
				else // 이번에 최초 충돌
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead()
						&& vecLeft[i]->Get_Collision() && vecRight[j]->Get_Collision()) // 둘다 살아있을 때만 실행하도록
					{
						Left_Collider->OnCollisionEnter(Right_Collider);
						Right_Collider->OnCollisionEnter(Left_Collider);
						iter->second = true;
					}
				}
			}
			else // 현재 충돌중이지 않음
			{
				if (iter->second) // 방금까지 충돌중이었음, 충돌이 막 벗어나진 시점
				{
					Left_Collider->OnCollisionExit(Right_Collider);
					Right_Collider->OnCollisionExit(Left_Collider);
					iter->second = false;
				}
			}
		}
	}

}

bool CCollisionMgr::IsCollision(CCollider * _pLeft, CCollider * _pRight)
{
	Vec2 vLeftPos = _pLeft->Get_FinalPos();
	Vec2 vLeftScale = _pLeft->Get_Scale();

	Vec2 vRightPos = _pRight->Get_FinalPos();
	Vec2 vRightScale = _pRight->Get_Scale();

	if (!_pLeft->IsCircle() && !_pRight->IsCircle())
	{
		if (abs(vRightPos.x - vLeftPos.x) < abs(vLeftScale.x + vRightScale.x) / 2.f
			&& abs(vRightPos.y - vLeftPos.y) < abs(vLeftScale.y + vRightScale.y) / 2.f)
		{
			return true;
		}
	}
	else
	{
		float width = vRightPos.x - vLeftPos.x;
		float height = vRightPos.y - vLeftPos.y;
		float dis = sqrt(width * width + height * height);

		if (dis < vLeftScale.x * 0.5f + vRightScale.x * 0.5f)
			return true;
	}
	

	return false;
}

bool CCollisionMgr::IsOBBCollision(CCollider * _pLeft, CCollider * _pRight)
{
	Vec2 vLeftPos = _pLeft->Get_FinalPos();
	Vec2 vLeftScale = _pLeft->Get_Scale();
	Vec2 vLeftDir = _pLeft->Get_Dir();

	Vec2 vRightPos = _pRight->Get_FinalPos();
	Vec2 vRightScale = _pRight->Get_Scale();
	Vec2 vRightDir = _pRight->Get_Dir();
	Vec2 vUnit;

		Vec2 vDist = Get_DistanceVector(vLeftPos, vLeftScale, vRightPos, vRightScale);
		Vec2 Vec[4] = { GetHeightVector(vLeftScale, vLeftDir), GetHeightVector(vRightScale, vRightDir)
					, GetWidthVector(vLeftScale, vLeftDir), GetWidthVector(vRightScale, vRightDir) };

		for (int i = 0; i < 4; i++) {
			float fSum = 0.f;
			vUnit = Get_UnitVector(Vec[i]);

			for (int j = 0; j < 4; j++) {
				fSum += absDotVector(Vec[j], vUnit);
			}
			if (absDotVector(vDist, vUnit) > fSum) {
				return false;
			}
		}

	return true;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft; // 행
	UINT iCol = (UINT)_eRight; // 열

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // 이미 그 자리가 1이면
		m_arrCheck[iRow] &= ~(1 << iCol); // 빼주고
	else
		m_arrCheck[iRow] |= (1 << iCol); // 1을 컬럼 만큼 밀어서 넣어줌..?


}

void CCollisionMgr::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}


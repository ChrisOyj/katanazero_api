#pragma once
#include "CObj.h"
#include "CSubWeapon.h"
#include "CMonster.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create(void)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(CObj* _pOwner, GROUP_TYPE _eType)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->SetObjType(_eType);
		pObj->SetOwner(_pOwner);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->SetPos(Vec2(_fX, _fY));

		return pObj;
	}

	static CObj*		Create(Vec2 vPos, GROUP_TYPE _eType)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos);
		pObj->SetObjType(_eType);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, GROUP_TYPE _eType)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->SetPos(Vec2(_fX, _fY));
		pObj->SetObjType(_eType);

		return pObj;
	}

	static void		Create_Monster(CObj* _pPlayer, Vec2 vPos, Vec2 vDir)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos);
		dynamic_cast<CAlive*>(pObj)->SetOriginY(vPos.y);
		pObj->SetObjType(GROUP_TYPE::MONSTER);
		pObj->SetOwner(_pPlayer);
		pObj->SetDir(vDir);
		pObj->SetRenderDir(vDir);

		CreateObject(pObj, GROUP_TYPE::MONSTER);
	}

	static void		Create_Effects(Vec2 _vPos, GROUP_TYPE _eType)
	{
		CObj*		pEffects = new T;
		pEffects->SetPos(_vPos);
		pEffects->Initialize();
		pEffects->SetObjType(_eType);

		CreateObject(pEffects, _eType);
	}

	static void		Create_Effects(CObj* _pOwner, Vec2 _vPos, Vec2 _vDir, GROUP_TYPE _eType)
	{
		CObj*		pEffects = new T;
		pEffects->SetDir(_vDir);
		pEffects->SetPos(_vPos);
		pEffects->Initialize();
		pEffects->SetObjType(_eType);
		pEffects->SetOwner(_pOwner);

		CreateObject(pEffects, _eType);
	}

	static void		Create_Sub(Vec2 _vPos, SUB_TYPE _eType)
	{
		CSubWeapon*		pSub = new T;
		pSub->SetSubType(_eType);
		pSub->Initialize();
		pSub->SetObjType(GROUP_TYPE::SUBWEAPON);
		pSub->SetPos(_vPos);

		CreateObject(pSub, GROUP_TYPE::SUBWEAPON);
	}

	static CObj*		Create(Vec2 _vPos, Vec2 _vDir, GROUP_TYPE _eType)
	{
		CObj*		pEffects = new T;
		pEffects->SetDir(_vDir);
		pEffects->SetPos(_vPos);
		pEffects->Initialize();
		pEffects->SetObjType(_eType);

		return pEffects;
	}



	//필요할 시 함수 오버로딩해서 더 만들 것!

public:
	CAbstractFactory() {}
	~CAbstractFactory() {}
};
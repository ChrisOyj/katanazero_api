#pragma once
#include "CScene.h"

class CScene_Tool :
	public CScene
{
public:
	CScene_Tool();
	virtual ~CScene_Tool();

public:
	virtual void Update();
	virtual void Enter(bool _breplay);
	virtual void Exit();
private:
};


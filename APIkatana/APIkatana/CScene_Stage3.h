#pragma once
#include "CScene.h"

class CScene_Stage3 :
	public CScene
{
public:
	CScene_Stage3();
	~CScene_Stage3() override;

public:
	void Enter(bool _replay) override;
	void Exit() override;


};



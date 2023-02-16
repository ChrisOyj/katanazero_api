#pragma once
#include "CScene.h"

class CScene_Stage2 :
	public CScene
{
public:
	CScene_Stage2();
	~CScene_Stage2() override;

public:
	void Enter(bool _replay) override;
	void Exit() override;


};



#pragma once
#include "CScene.h"

class CScene_Start :
	public CScene
{
public:
	CScene_Start();
	~CScene_Start() override;

public:
	void Enter(bool _replay) override;
	void Exit() override;


};


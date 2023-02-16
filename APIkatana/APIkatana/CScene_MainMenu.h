#pragma once
#include "CScene.h"

class CScene_MainMenu :
	public CScene
{
public:
	CScene_MainMenu();
	~CScene_MainMenu() override;


public:
	void Update() override;
	void Enter(bool _replay) override;
	void Exit() override;


};


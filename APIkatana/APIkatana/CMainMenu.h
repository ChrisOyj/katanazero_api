#pragma once
#include "CObj.h"

class CMainMenu
	: public CObj
{
public:
	CMainMenu();
	~CMainMenu() override;

	CLONE(CMainMenu);

public:
	void Update() override;
	void Render(HDC _dc) override;

private:

};


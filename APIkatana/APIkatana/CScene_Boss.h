#pragma once
#include "CScene.h"

class CScene_Boss :
	public CScene
{
public:
	CScene_Boss();
	~CScene_Boss() override;

public:
	int			Get_DragonCount() { return m_iDragonCount; }
	void		Set_DragonCount() { m_iDragonCount--; }

public:
	void Enter(bool _replay) override;
	void Exit() override;

private:
	int m_iDragonCount;
};



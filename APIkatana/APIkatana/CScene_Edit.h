#pragma once
#include "CScene.h"

class CScene_Edit
	: public CScene
{
public:
	CScene_Edit();
	virtual ~CScene_Edit();

public:
	virtual void				Update();
	virtual void				Render(HDC _dc);
	virtual void				Enter(bool _bReplay);
	virtual void				Exit();
};


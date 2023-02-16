#pragma once
#include "CObj.h"

class CTexture;

class CCursor :
	public CObj
{
public:
	CCursor();
	~CCursor() override;

public:
	void Update() override;

	CLONE(CCursor);

};



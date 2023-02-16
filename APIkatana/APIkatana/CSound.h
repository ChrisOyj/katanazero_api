#pragma once
#include "CRes.h"


class CSound
	: public CRes
{
public:
	CSound();
	virtual ~CSound();

public:
	void Load(const wstring& _strFilePath);

};


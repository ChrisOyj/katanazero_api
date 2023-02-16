#include "stdafx.h"
#include "CBackGround.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::Initialize()
{
	m_vPos = m_vScale * 0.5f;
	m_colorMatrix = new ColorMatrix;
	*m_colorMatrix = {
		   1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}



#pragma once
#include "CObj.h"
#include "CAnimation.h"

class CTexture;
class CAnimation;

class CAfterImage :
	public CObj
{
public:
	CAfterImage();
	~CAfterImage() override;

public:
	//void SetAnim(CAnimation* _pAnim) { m_pAnim = _pAnim;  }
	void SetAnim(CAnimation _pAnim);
	void SetFrame(int _frame) { m_iFrame = _frame; }
	void SetColor(float _fcolor) { m_fColor = _fcolor; }
	void Set_RGB(float _fRGB[3]) { m_fRGB[0] = _fRGB[0]; m_fRGB[1] = _fRGB[1]; m_fRGB[2] = _fRGB[2]; }
	void SetAlphaCount(float _count) { m_fAlphaCount = _count; }

public:
	void Update() override;
	void Render(HDC _dc) override;

	CLONE(CAfterImage);

private:
	float m_fRGB[3];
	float m_fTime;
	float m_fColor;
	float m_fAlpha;
	int m_iFrame;
	float m_fAlphaCount;
	CAnimation*	m_pAnim;

};



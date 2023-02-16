#pragma once
#include "CObj.h"
#include "CAnimation.h"


class CTexture;

class CLaserImage :
	public CObj
{
public:
	CLaserImage();
	virtual ~CLaserImage();

public:
	void SetAnimFrm(tAnimFrm _tAnimFrm);
	void SetImage(Image* _Image);
	void SetFrame(int _frame) { m_iFrame = _frame; }

public:
	void Update() override;
	void Render(HDC _dc) override;

	CLONE(CLaserImage);

private:
	void CreateParticle(Vec2 _vPos);

private:
	int m_iRow;
	int m_iFrame;

	Image*		m_Image;
	tAnimFrm	m_tAnimFrm;
	Bitmap*		m_pBitmap;

};





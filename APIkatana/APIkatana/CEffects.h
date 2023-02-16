#pragma once
#include "CObj.h"

typedef struct tag_Effect_Info
{
	float		fFadeSpeed;
	float		fAlpha;
	
	int			iColor;
	int			iAlpha;

	unsigned char		RGB[3];

	bool		bColorPlus;
	bool		bDelete;

}EFFECTINFO;

class CEffects :
	public CObj
{
public:
	CEffects();
	virtual ~CEffects();

	virtual CObj* Clone() PURE;

public:
	// ==================== GET SET ======================
	EFFECT_TYPE Get_EffectType() { return m_eEffectType; }
	

	void	Set_EffectType(EFFECT_TYPE _eType) { m_eEffectType = _eType; }
	void	Set_RGB(unsigned char r, unsigned char g, unsigned char b) { m_tInfo.RGB[0] = r; m_tInfo.RGB[1] = r;  m_tInfo.RGB[2] = r; }
	void	Set_Alpha(int _i) { m_tInfo.iAlpha = _i; }
	void	Set_Delete() { m_tInfo.bDelete = true; }
	void	Set_FadeSpeed(float f) { m_tInfo.fFadeSpeed = f; }
	// ===================================================

public:
	virtual void	Initialize() PURE;
	virtual void	Update() PURE;
	virtual void	Render(HDC _dc);

protected:
	void	Effects_Move(bool _bReal = false);

protected:
	EFFECTINFO		m_tInfo;
	EFFECT_TYPE		m_eEffectType;
	float			m_fTimeLimit;
	float			m_fSpeed;


};


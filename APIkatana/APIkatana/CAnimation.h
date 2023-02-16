#pragma once
#include "CTexture.h"

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;
	Vec2	vSlice;
	Vec2	vOffSet;
	float	fDuration;
};


class CAnimation
{
public:
	CAnimation();
	~CAnimation();

private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;	//Animation이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm; // 모든 프레임 정보
	int					m_iCurFrm; // 현재 프레임
	float				m_fAccTime; //시간 누적
	bool				m_bFinish;


public:
	const wstring& Get_Name() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& Get_Frame(int _iIdx) { return m_vecFrm[_iIdx]; }
	tAnimFrm Get_Frm(int _iIdx) {return m_vecFrm[_iIdx];}
	int Get_MaxFrame() { return (int)m_vecFrm.size(); }
	float Get_MaxTime() { return m_vecFrm[m_iCurFrm].fDuration * (float)m_vecFrm.size(); }
	int Get_CurFrame() { return m_iCurFrm; }
	int GetWidth() { return (int)m_vecFrm[0].vSlice.x; }
	int GetHeight() { return (int)m_pTex->Height(); }
	Image* Get_Image() { return m_pTex->Get_Image(); }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }


public:
	void Update();
	void speed_Update();
	void Render(HDC _dc, Color _ColorKey = Color(255, 0, 255), Color _ColorKey2 = Color(255, 0, 255), float _fXRatio = 1.f);
	void dir_Render(HDC _dc, Color _ColorKey = Color(255, 0, 255), Color _ColorKey2 = Color(255, 0, 255));
	//void dir_Render(HDC _dc, Color _ColorKey, Color _ColorKey2);
	void after_Render(HDC _dc, Vec2 _vPos, float _dir, float _fRatio, ColorMatrix* _colormatrix);
	void dir_after_Render(HDC _dc, Vec2 _vPos, float _fTheta, float _fRatio, ColorMatrix* _colormatrix);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

	friend class CAnimator;
};


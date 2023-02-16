#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);

public:
	double	Get_DT() { return m_dDT; };
	float	Get_fDT() { return (float)m_dDT * m_fTimeSpeed; };
	float	Get_RealfDT() { return (float)m_dDT; }
	float	Get_TimeSpeed() { return m_fTimeSpeed; }

	void	SetTimeSpeed(float _f) { m_fTimeSpeed = _f; }

public:
	void	Initialize();
	void	Update();
	void	Render();


private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double			m_dDT; // 프레임과 프레임 사이에 걸린 시간
	double			m_dAcc; // 1초 체크를 위한 누적 시간
	UINT			m_iCallCount; // 초당 함수 횟수
	UINT			m_iFPS; // 초당 호출 횟수

	float			m_fTimeSpeed;


};


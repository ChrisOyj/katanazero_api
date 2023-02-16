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

	double			m_dDT; // �����Ӱ� ������ ���̿� �ɸ� �ð�
	double			m_dAcc; // 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount; // �ʴ� �Լ� Ƚ��
	UINT			m_iFPS; // �ʴ� ȣ�� Ƚ��

	float			m_fTimeSpeed;


};


#pragma once
#include "CObj.h"

class CSelector
	: public CObj
{
public:
	CSelector();
	~CSelector() override;

	CLONE(CSelector);

public:
	void Update() override;
	void Render(HDC _dc) override;

private:
	void physics_Update();

private:
	bool	m_bSelected;

	float m_fFriction;		//����
	float m_fXSpeed;		//�ӵ�
	float m_fMaxXSpeed;		//�ӵ� ����
	float m_fAccel;			//���ӵ�
	float m_fMaxAccel;		//�ִ밡�ӵ�
	float m_fAcc;

	int	m_iAlpha;


};


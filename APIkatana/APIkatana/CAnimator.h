#pragma once

class CObj;
class CAnimation;
class CTexture;

class CAnimator
{

public:
	CAnimator();
	~CAnimator();

	friend class CObj;

private:
	map<wstring, CAnimation*>	m_mapAnim; // Animation ���
	CAnimation*					m_pCurAnim; // ���� ����� Anim
	wstring						m_strCurAnim;

	CObj*					m_pOwner; // �� ���� ������Ʈ
	bool						m_bRepeat;	//�ݺ��������

public: // Get_Set
	CObj* Get_Owner() { return m_pOwner; }
	CAnimation* Get_CurAnim() { return m_pCurAnim; }
	wstring		Get_CurKey() { return m_strCurAnim; }

	void		Set_CurAnim(CAnimation* pAnim) { m_pCurAnim = pAnim; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex
		, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void Update();
	void speed_Update();
	void Render(HDC _dc, Color _ColorKey = Color(255, 0, 255), Color _ColorKey2 = Color(255, 0, 255), float _fXRatio = 1.f);

	//ȸ��ȿ��
	void dir_Render(HDC _dc, Color _ColorKey = Color(255, 0, 255), Color _ColorKey2 = Color(255, 0, 255));
	//void dir_Render(HDC _dc, Color _ColorKey, Color _ColorKey2);



};


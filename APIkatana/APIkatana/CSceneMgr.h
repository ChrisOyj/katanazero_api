#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)

public:
	void Initialize();
	void Update();
	void Render(HDC _dc);

public:
	CScene*		Get_CurScene() { return m_pCurScene; }
	SCENE_TYPE	Get_CurSceneType() { return m_eCurScene; }
	void		AddReplay(ReplayInfo* _Info);

	bool		IsReplay() { return m_bReplay; }
	bool		IsSave() { return m_bReplaysave; }

	void		DragonReplay();

public:
	void SceneChange(bool _bEnter);

private:
	void ChangeScene(SCENE_TYPE _eNext);

	void SaveGhost();

	void Replay();
	void Replay_over();
	void Replay_Render(HDC _dc);

	void normal_Render(HDC _dc, ReplayInfo* pCurReplay);
	void dir_Render(HDC _dc, ReplayInfo* pCurReplay);


private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // ��� �� ���
	CScene* m_pCurScene; // ���� ��
	SCENE_TYPE m_eCurScene;

	float							m_fTime;
	bool							m_bReplaysave;
	bool							m_bReplay;
	bool							m_bDragonReplay = false;
	vector<ReplayInfo*>				m_vecReplay; // �� ������ ��� ����
	vector<vector<ReplayInfo*>>		m_vecvecReplay; // ��� ������ ��� ����


	friend class CEventMgr;
};


#pragma once

class CTexture;

typedef struct tag_SaveInfo
{
	EDIT_TYPE		eEditType;
	Vec2			vPos;
	Vec2			vScale;
	Vec2			vDir = Vec2(1.f, 0.f);
	MOB_TYPE		eMobType = MOB_TYPE::GRANT;
	SUB_TYPE		eSubType = SUB_TYPE::KNIFE;
	LINEINFO		tLineInfo;
	int				iFloor;
	bool			bClimb;
	bool			bLeft = true;
	CTexture*		pTex = nullptr;

}SAVEINFO;

class CEditor
{
	SINGLE(CEditor);

public:
	void					AddGhost(GhostInfo tInfo) { m_arrGhost.push_back(tInfo); }
	void					ClearGhost() { m_arrGhost.clear(); }
	void					SaveGhost(int _i);
	void					SaveTimeRecord(int _i);
	vector<GhostInfo>		LoadGhost(int _i);
	float					LoadTimeRecord(int _i);

	void		Initialize();
	void		Update();
	void		Render(HDC _dc);
	void		Release();

	void		Set_Stage(int _iStageNum);

private:
	void		Update_Line();
	void		Update_Land();
	void		Update_Wall();
	void		Update_Ceiling();
	void		Update_Player();
	void		Update_Monster();
	void		Update_Laser();
	void		Update_Sub();

	void		Render_Tex(HDC _dc, SAVEINFO _Info);
	void		Render_Line(HDC _dc, SAVEINFO _Info);
	void		Render_Rect(HDC _dc, SAVEINFO _Info);

	void		Render_MousePos(HDC _dc);
	void		Render_Guide(HDC _dc);
	void		Render_Info(HDC _dc);
	void		Render_Object(HDC _dc, SAVEINFO _Info);

private:
	void		Add_Line(SAVEINFO& _Info);
	void		Add_Wall(SAVEINFO& _Info);
	void		Add_Land(SAVEINFO& _Info);
	void		Add_Ceiling(SAVEINFO& _Info);
	void		Add_Player(SAVEINFO& _Info);
	void		Add_Monster(SAVEINFO& _Info);
	void		Add_Laser(SAVEINFO& _Info);
	void		Add_Sub(SAVEINFO& _Info);

	void		EraseObject();
	void		Key_Input();
	void		Save(int _iStageNum);
	void		Load(int _iStageNum);

private:
	SAVEINFO			m_tCurInfo;
	vector<SAVEINFO>	m_arrInfo;

	CObj*				m_pPlayer;
	CObj*				m_pBG;

	int					m_iCurSlot;

	vector<GhostInfo>			m_arrGhost;

	//저장에 필요한 것
	//에딧 타입
	//좌표
	//라인의 경우 불 변수
	//몬스터의 경우 몬스터 타입



};


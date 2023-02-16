#pragma once

struct tEvent
{
	EVENT_TYPE		eEven;
	DWORD_PTR		lParam;		// DWORD_PTR 쓰면 32비트 체제와 64비트에 따라 4바이트 or 8바이트로 알아서 바뀜
	DWORD_PTR		wParam;
};

class CEventMgr
{
	SINGLE(CEventMgr)

public:
	void Update();
	void ClearEvent() {
		m_vecDead.clear();
		m_vecEvent.clear();}

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

private:
	void Excute(const tEvent& _eve);

private:
	vector<tEvent> m_vecEvent;
	vector<CObj*> m_vecDead; // 삭제시킬 아이들


};


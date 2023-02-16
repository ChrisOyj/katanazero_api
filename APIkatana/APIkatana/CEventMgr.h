#pragma once

struct tEvent
{
	EVENT_TYPE		eEven;
	DWORD_PTR		lParam;		// DWORD_PTR ���� 32��Ʈ ü���� 64��Ʈ�� ���� 4����Ʈ or 8����Ʈ�� �˾Ƽ� �ٲ�
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
	vector<CObj*> m_vecDead; // ������ų ���̵�


};


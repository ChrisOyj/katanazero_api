#include "stdafx.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Update()
{
	CScene::Update(); // �ϴ� �θ� ������Ʈ �Լ� ���

	if (KEY(ENTER, TAP))
	{
		ChangeScene(SCENE_TYPE::START); // �����Լ� ȣ���ϸ� �����Լ��� �̺�Ʈ�� ���
	}
}

void CScene_Tool::Enter(bool _breplay)
{
}

void CScene_Tool::Exit()
{
}

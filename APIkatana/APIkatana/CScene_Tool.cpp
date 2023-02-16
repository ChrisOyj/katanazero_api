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
	CScene::Update(); // 일단 부모꺼 업데이트 함수 사용

	if (KEY(ENTER, TAP))
	{
		ChangeScene(SCENE_TYPE::START); // 전역함수 호출하면 전역함수가 이벤트에 등록
	}
}

void CScene_Tool::Enter(bool _breplay)
{
}

void CScene_Tool::Exit()
{
}

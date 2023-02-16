#include "stdafx.h"
#include "CScene_Edit.h"

#include "CSoundMgr.h"


#include "CObj.h"
#include "CLineMgr.h"
#include "CEditor.h"
#include "CCamera.h"


CScene_Edit::CScene_Edit()
{
}

CScene_Edit::~CScene_Edit()
{
}

void CScene_Edit::Update()
{
	CEditor::Get_Instance()->Update();

}

void CScene_Edit::Render(HDC _dc)
{
	CScene::Render(_dc);
	CEditor::Get_Instance()->Render(_dc);

}

void CScene_Edit::Enter(bool _bReplay)
{
	CEditor::Get_Instance()->Initialize();
	CCamera::Get_Instance()->SetEdit(true);
	CLineMgr::Get_Instance()->Set_Player(nullptr);
}

void CScene_Edit::Exit()
{
	DeleteAll();
	CCamera::Get_Instance()->SetEdit(false);
	CEditor::Get_Instance()->Release();

}

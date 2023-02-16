#include "stdafx.h"
#include "func.h"

#include "CEventMgr.h"
#include "CMainGame.h"

#include "CObj.h"



void CreateObject(CObj* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::Get_Instance()->AddEvent(evn);
}

void DeleteObject(CObj * _pObj)
{
	if (_pObj->IsDead())
		return;

	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::Get_Instance()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::Get_Instance()->AddEvent(evn);
}

Vec2 Get_MousePos()
{
	//마우스 위치 계산
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(g_hwnd, &mousePos);

	return Vec2((float)mousePos.x, (float)mousePos.y);
}

int random(int a, int b)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> disx(a, b);

	return disx(gen);
}

Vec2 randomdir()
{
	Vec2 vPos;

	int iRandx = random(-100, 100);
	int iRandy = random(-100, 100);

	if (iRandx == 0 && iRandy == 0)
		iRandy = -1;

	vPos.x = float(iRandx);
	vPos.y = float(iRandy);

	vPos.Normalize();

	return vPos;
}

Point rotate(Vec2 vCenterPos, Point _point, float _fTheta)
{
	double x = cos(_fTheta) * (_point.X- vCenterPos.x) - sin(_fTheta) * (_point.Y - vCenterPos.y) + vCenterPos.x;
	double y = sin(_fTheta) *  (_point.X - vCenterPos.x) + cos(_fTheta) * (_point.Y - vCenterPos.y) + vCenterPos.y;

	return Point((INT)x, (INT)y);
}

POINT rotatept(Vec2 vCenterPos, Point _point, float _fTheta)
{
	double x = cos(_fTheta) * (_point.X - vCenterPos.x) - sin(_fTheta) * (_point.Y - vCenterPos.y) + vCenterPos.x;
	double y = sin(_fTheta) *  (_point.X - vCenterPos.x) + cos(_fTheta) * (_point.Y - vCenterPos.y) + vCenterPos.y;

	POINT pt;
	pt.x = (LONG)x;
	pt.y = (LONG)y;

	return pt;
}

Bitmap * GdiplusImaGet_oBitmap(Image * img, int _Slice, int _LTX, int _LTY, Color bkgd)
{
	Bitmap* bmp = nullptr;
	try {
		int wd = img->GetWidth();
		int hgt = img->GetHeight();
		auto format = img->GetPixelFormat();
		bmp = new Bitmap(_Slice, hgt, format);
		auto g = unique_ptr<Graphics>(Graphics::FromImage(bmp));
		g->Clear(bkgd);
		//g->DrawImage(img, 0, 0, wd, hgt);

		ImageAttributes imgAttr;
		ColorMatrix ColorMatrix = {
		1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.7f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		0.7f, 0.5f, 0.0f, 0.0f, 1.0f };

		imgAttr.SetColorKey(Color(0, 0, 0), Color(0, 0, 0), ColorAdjustTypeBitmap);
		imgAttr.SetColorMatrix(&ColorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

		g->DrawImage(img
			, Rect(0
				, 0
				, _Slice
				, hgt)
			, _LTX
			, _LTY
			, _Slice
			, hgt
			, UnitPixel, &imgAttr, NULL, NULL);
	}
	catch (...) {
		// this might happen if img->GetPixelFormat() is something exotic
		// ... not sure
	}
	return bmp;
}


//OBB 충돌 관련



float Deg2Rad(float deg) { //deg -> rad
	return deg * PI / 180.f;
}

Vec2 Get_DistanceVector(const Vec2& _vLeftPos, const Vec2& _vLeftScale, const Vec2& _vRightPos, const Vec2& _vRightScale) { //distance vector
	Vec2 vec;

	vec.x = _vLeftPos.x - _vRightPos.x;
	vec.y = _vLeftPos.y - _vRightPos.y;

	return vec;
}

Vec2 GetHeightVector(const Vec2& _vScale, const Vec2& _vDir) { //height vector
	Vec2 vec;
	float fAngle = acos(_vDir.x) * 180.f / PI - 90.f;

	/*if (0 > _vDir.y)
	{
		fAngle *= -1.f;
	}*/

	float fRad = (fAngle)*  PI / 180.f;

	vec.x = _vScale.y * cos(fRad) / 2.f;
	vec.y = _vScale.y * sin(fRad) / 2.f;
	return vec;
}

Vec2 GetWidthVector(const Vec2& _vScale, const Vec2& _vDir) { //width vector
	Vec2 vec;


	

	vec.x = _vScale.x * _vDir.x / 2.f;
	vec.y = _vScale.x * _vDir.y / 2.f;

	return vec;
}

Vec2 Get_UnitVector(Vec2 a) { //unit vector
	Vec2 ret;
	double size;
	size = sqrt(pow(a.x, 2) + pow(a.y, 2));
	ret.x = (float)(a.x / size);
	ret.y = (float)(a.y / size);
	return ret;
}

float absDotVector(Vec2 a, Vec2 b) { //vector inner
	return abs(a.x * b.x + a.y * b.y);
}


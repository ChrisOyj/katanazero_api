#pragma once

class CObj;

void CreateObject(CObj* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObj* _pObj);
void ChangeScene(SCENE_TYPE _eNext);

Vec2 Get_MousePos();
int random(int a, int b);
Vec2 randomdir();

Point rotate(Vec2 _vcenterPos, Point _point, float _angle);
POINT rotatept(Vec2 _vcenterPos, Point _point, float _angle);

Bitmap* GdiplusImaGet_oBitmap(Image* img, int _Slice, int _LTX, int _LTY, Color bkgd = Color::Transparent);


float Deg2Rad(float deg);
Vec2 Get_DistanceVector(const Vec2& _vLeftPos, const Vec2& _vLeftScale, const Vec2& _vRightPos, const Vec2& _vRightScale);
Vec2 GetHeightVector(const Vec2& _vScale, const Vec2& _vDir);
Vec2 GetWidthVector(const Vec2& _vScale, const Vec2& _vDir);
Vec2 Get_UnitVector(Vec2 a);
float absDotVector(Vec2 a, Vec2 b);


template<typename T>
inline void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}

template<typename T1, typename T2>
inline void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin(); // 이넘클래스 쓰려면 앞에 타입네임 붙이래

	for (; iter != _map.end(); ++iter)
	{
		delete iter->second;
		iter->second = nullptr;
	}

	_map.clear();
}

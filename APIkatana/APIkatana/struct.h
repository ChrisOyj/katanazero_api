#pragma once


struct Vec2 {

	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x*x + y * y);
	}

	float	Dot(const Vec2& _other)
	{
		return (x * _other.x + y * _other.y);
	}

	Vec2	Up()
	{
		return Vec2(0.f, -1.f * y);
	}

	Vec2& Normalize()
	{
		float fLen = Length();
		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;

		return *this;

	}

public:
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;

	}

	Vec2 operator + (Vec2 _other)
	{
		return Vec2(x + _other.x, y + _other.y);
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec2 operator - (Vec2 _other)
	{
		return Vec2(x - _other.x, y - _other.y);
	}

	Vec2 operator * (Vec2 _other)
	{
		return Vec2(x * _other.x, y * _other.y);
	}

	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	Vec2 operator / (Vec2 _other)
	{
		assert(!(0.f == _other.x || 0.f == _other.y));

		return Vec2(x / _other.x, y / _other.y);
	}

	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));

		return Vec2(x / _f, y / _f);
	}

	bool operator == (Vec2 _other)
	{
		if (x == _other.x && y == _other.y)
			return true;

		return false;
	}

	bool operator != (Vec2 _other)
	{
		if (x == _other.x && y == _other.y)
			return false;

		return true;
	}

public:
	Vec2()
		:x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		:x(_x)
		, y(_y)
	{}
	Vec2(int _x, int _y)
		:x((float)_x)
		, y((float)_y)
	{}
	Vec2(const POINT& _pt)
		:x((float)_pt.x)
		, y((float)_pt.y)
	{}
	~Vec2()
	{}

};

typedef	struct tagLineInfo
{
	Vec2	vLeftPoint;
	Vec2	vRightPoint;
	bool	bStair;
	bool	bOpen;

	tagLineInfo(void) { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(Vec2& vLeft, Vec2& vRight, bool& _bStair, bool& _bOpen)
		: vLeftPoint(vLeft)
		, vRightPoint(vRight)
		, bStair(_bStair)
		, bOpen(_bOpen)
	{}

}LINEINFO;

struct ReplayInfo
{
	Image*	Img;
	Vec2	vPos;
	Vec2	vDir;
	Vec2	vLookAt;
	float	fRatio;
	int		LTx;
	int		LTy;
	int		Slicex;
	int		Slicey;
	ImageAttributes*	ImgAttr;

	ReplayInfo()
	{}

	ReplayInfo(Image* _Img, Vec2 _vPos, Vec2 _vDir, Vec2 _vLookAt
		, float _fRatio, int _LTx, int _LTy, int _Slicex, int _Slicey, ColorMatrix* _matrix)
		: Img(_Img)
		, vPos(_vPos)
		, vDir(_vDir)
		, vLookAt(_vLookAt)
		, fRatio(_fRatio)
		, LTx(_LTx)
		, LTy(_LTy)
		, Slicex(_Slicex)
		, Slicey(_Slicey)
	{
		ImgAttr = new ImageAttributes;
		ImgAttr->SetColorKey(Color(255, 255, 255), Color(255, 255, 255), ColorAdjustTypeBitmap);
		ImgAttr->SetColorMatrix(_matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	}

	~ReplayInfo()
	{
		//delete ImgAttr;
	}

};

struct GhostInfo
{
	TCHAR	ImageKey[32];
	Vec2	vPos;
	Vec2	vDir;
	Vec2	vLookAt;
	float	fRatio;
	int		LTx;
	int		LTy;
	int		Slicex;
	int		Slicey;

	GhostInfo()
	{}

	GhostInfo(wstring _ImgKey, Vec2 _vPos, Vec2 _vDir, Vec2 _vLookAt
		, float _fRatio, int _LTx, int _LTy, int _Slicex, int _Slicey)
		: vPos(_vPos)
		, vDir(_vDir)
		, vLookAt(_vLookAt)
		, fRatio(_fRatio)
		, LTx(_LTx)
		, LTy(_LTy)
		, Slicex(_Slicex)
		, Slicey(_Slicey)
	{
		lstrcpyW(ImageKey, _ImgKey.c_str());
	}

	~GhostInfo()
	{
		//delete ImgAttr;
	}

};
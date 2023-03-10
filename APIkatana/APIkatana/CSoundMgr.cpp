#include "stdafx.h"
#include "CSoundMgr.h"

CSoundMgr::CSoundMgr()
	: m_pSystem(nullptr)
	, m_eCurChannel(CH1)
{}

CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	// 사운드를 담당하는 대표객체를 생성하는 함수
	FMOD_System_Create(&m_pSystem);

	//FMOD_System_SetSoftwareFormat(m_pSystem, 48000, FMOD_SOUND_FORMAT_PCM32, 0, 0, FMOD_DSP_RESAMPLER_NOINTERP);
	//FMOD_System_SetDSPBufferSize(m_pSystem, 512, 4);

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();
}

void CSoundMgr::Update()
{
	/*m_iCount++;
	if (5 < m_iCount)
	{
		m_iCount = 0;
		FMOD_System_Update(m_pSystem);
	}*/
}

void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}


void CSoundMgr::LoadSoundFile()
{
	// _finddata_t : <io.h>에서 제공하며 파일 정보를 저장하는 구조체
	_finddata_t fd;
	// _findfirst : <io.h>에서 제공하며 사용자가 설정한 경로 내에서 가장 첫 번째 파일을 찾는 함수
	INT_PTR handle = _findfirst("../Sound/*.*", &fd);

	if (handle == -1)
		return;

	int iResult = 0;

	char szCurPath[128] = "../Sound/";
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);

		// "../ Sound/Success.wav"
		strcat_s(szFullPath, fd.name);

		//wstring strFilePath = CPathMgr::Get_Instance()->Get_ContentPath();
		//strFilePath += fd.name;

		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = (int)strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			// 아스키 코드 문자열을 유니코드 문자열로 변환시켜주는 함수
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		//_findnext : <io.h>에서 제공하며 다음 위치의 파일을 찾는 함수, 더이상 없다면 -1을 리턴
		iResult = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);

	_findclose(handle);
}

void CSoundMgr::PlaySound(const TCHAR* strSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(),
		[&](auto& iter)->bool
	{
		return !lstrcmp(strSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;

	if (FMOD_Channel_IsPlaying(m_pChannelArr[m_eCurChannel], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[m_eCurChannel++]);
	}
		if (m_eCurChannel >= CH_END)
			m_eCurChannel = CH1;

	//FMOD_Channel_SetVolume(m_pChannelArr[UINT(eType)], fVolume);

	FMOD_System_Update(m_pSystem);
}

//void CSoundMgr::Play_Sound(const string& strPath, CHANNEL_TYPE eType)
//{
//	int iResult = 0;
//
//	string szPath = "../Sound/";
//	szPath += strPath;
//
//	FMOD_SOUND* pSound = nullptr;
//
//	FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szPath.c_str(), FMOD_HARDWARE, 0, &pSound);
//
//	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, pSound, FALSE, &m_pChannelArr[UINT(eType)]);
//
//}

void CSoundMgr::PlayBGM(const TCHAR* strSoundKey, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
	{
		return !lstrcmp(strSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[BGM], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannelArr[BGM], fVolume);
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopSound(CHANNELID eType)
{
	FMOD_Channel_Stop(m_pChannelArr[eType]);

}

void CSoundMgr::StopAll()
{
	for (UINT i = 0; i < CH_END; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::SetVolume(float fVolume)
{
	for (int i = BGM; i < CH_END; ++i)
	{
		FMOD_Channel_SetVolume(m_pChannelArr[i], fVolume);
	}

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::SetChannelVolume(CHANNELID eID, float fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);
	FMOD_System_Update(m_pSystem);

}



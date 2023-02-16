#pragma once
class CSoundMgr
{
	SINGLE(CSoundMgr);

public:
	void		Initialize();
	void		Update();
	void		Release();

public:
	void		LoadSoundFile();

	void		PlaySound(const TCHAR* strSoundKey);
	//void		Play_Sound(const string& strPath, CHANNEL_TYPE eType);
	void		PlayBGM(const TCHAR* strSoundKey, float fVolume);
	void		StopSound(CHANNELID eType);
	void		StopAll();
	void		SetVolume(float fVolume);
	void		SetChannelVolume(CHANNELID eID, float fVolume);

private:
	map <TCHAR*, FMOD_SOUND*> m_mapSound;
	FMOD_CHANNEL* m_pChannelArr[CH_END];
	FMOD_SYSTEM* m_pSystem;
	int m_eCurChannel;
	int m_iCount = 0;
};


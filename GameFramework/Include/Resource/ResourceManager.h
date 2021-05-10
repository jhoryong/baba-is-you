#pragma once

#include "../Game.h"

class CResourceManager
{
	DECLARE_SINGLE(CResourceManager)

private:
	System* m_pSystem;
	ChannelGroup* m_pMasterGroup;

private:
	unordered_map<string, class CTexture*>	m_mapTexture;
	unordered_map<string, class CAnimationSequence*>	m_mapAnimationSequence;
	unordered_map<string, class CSound*>	m_mapSound;
	unordered_map<string, ChannelGroup*>	m_mapChannelGroup;
	// fmod 에서는 사운드를 여러개의 채널로 나눌 수 있다. (배경, 이펙트 등등)

public:
	bool Init();
	void Update(); // FMOD 시스템을 업데이트한다.

public:
	bool LoadTexture(const string& strName, const TCHAR* pFileName,
		const string& strPathName = TEXTURE_PATH);
	bool LoadTexture(const string& strName, const vector<const TCHAR*>& vecFileName,
		const string& strPathName = TEXTURE_PATH);
	bool LoadTexture(const string& strName, const TCHAR* pFileName,
		int iCount, const string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const string& strName,
		const TCHAR* pFullPath);
	void SetColorKey(const string& strName, unsigned char r, unsigned char g, unsigned char b,
		int iIndex = 0);
	void SetColorKeyAll(const string& strName, unsigned char r, unsigned char g, unsigned char b);
	class CTexture* FindTexture(const string& strName);
	void ReleaseTexture(const string& strName);

public:
	bool CreateAnimationSequence(const string& strName, const string& strTexName,
		ANIM_TYPE eType, ANIM_OPTION eOption,
		ANIM_PLAY_TYPE ePlayType, float fLoopTime,
		float fPlayRate = 1.f, float fOptionTimeMax = 1.f);
	bool CreateAnimationSequence(const string& strName, const char* pFileName,
		const string& strPathName = SEQUENCE_PATH);
	bool CreateAnimationSequence(const string& strName, FILE* pFile);
	void AddAnimationFrame(const string& strName, const Vector2& vStart, const Vector2& vEnd);
	void AddAnimationFrame(const string& strName, const AnimationFrameInfo& tFrame);
	class CAnimationSequence* FindAnimationSequence(const string& strName);
	void ReleaseAnimationSequence(const string& strName);
	void ReleaseAnimationSequence();

// Sound 관련 함수
public:
	bool LoadSound(
		const string& strGroup, // 어떤 그룹에 넣을 건지
		bool bLoop, // 무한반복옵션
		const string& strName, // 이름
		const char* pFileName, // 파일이름
		const string& strPathName = SOUND_PATH // 붙일 경로
	);

	class CSound* FindSound(const string& strName);

	bool CreateChannelGroup(const string& strName); // 채널을 만들고 마스터그룹에 추가한다.
	ChannelGroup* FindChannelGroup(const string& strName);

	void ReleaseSound(const string& strName);
	void ReleaseChannelGroup(const string& strName);
	void SetVolume(int iVolume);
	void SetGroupVolume(const string& strGroup, int iVolume);
	bool SoundPlay(const string& strName);
	bool SoundStop(const string& strName);
	bool SoundPause(const string& strName);
	bool SoundResume(const string& strName);

};


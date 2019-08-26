#pragma once
#include "Singleton.h"
#include <fmod.hpp>
#include <map>

struct SoundData final
{
	explicit SoundData(const std::string& file, FMOD_MODE mode = FMOD_DEFAULT)
		: file(file)
		, mode(mode)
	{}
	std::string file;
	FMOD_MODE mode;
};
enum class eSoundMerge
{
	Overlap,
	Replay,
	ContinueElseReplay,
	ContinueElseOverlap
};

class SoundManager final : public Singleton<SoundManager>
{

public:
	SoundManager(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) noexcept = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager& operator=(SoundManager&& other) noexcept = delete;
	SoundManager();
	virtual ~SoundManager();

	static bool ErrorCheck(FMOD_RESULT res);
	FMOD::System* GetSystem() const { return m_pFmodSystem; }

	void LoadSound(const std::map<int, SoundData>& soundFiles);
	void LoadSound(int soundID, const SoundData& soundFile);

	void PlaySoundByID(int soundID, int channelID, float volume = 0.1f, eSoundMerge merge = eSoundMerge::ContinueElseReplay);
	
	void PauseSoundByID(int soundID, int channelID);
	void PauseAll(bool paused);
	void PauseAllExcept(int channelID, bool paused);
	void Pause(int channelID, bool paused);
	void Pause(const std::vector<int>& channelIDs, bool paused);

	void StopAll();
	void StopAllExcept(int channelID);
	void Stop(int channelID);
	void Stop(const std::vector<int>& channelIDs);
	void StopIf(int channelID, int soundID);

	void SetBaseVolume(float volume);
private:
	void Initialize();
	float m_BaseVolume = 1.0f;
	FMOD::System* m_pFmodSystem = nullptr;

	std::map<int, FMOD::Channel*> m_pChannels;
	std::map<int, FMOD::Sound*> m_pSounds;

};


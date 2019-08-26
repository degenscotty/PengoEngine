#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	Initialize();
}

SoundManager::~SoundManager()
{
	//Release Sounds
	for (const std::pair<int, FMOD::Sound*>& pSound : m_pSounds)
	{
		if (pSound.second) pSound.second->release();
	}

	//Release System
	if(m_pFmodSystem)
	{
		m_pFmodSystem->release();
	}
}

void SoundManager::Initialize()
{
	unsigned int version;
	int numdrivers;
	
	/*
	Create a System object and initialize.
	*/
	FMOD_RESULT result = FMOD::System_Create(&m_pFmodSystem);
	ErrorCheck(result);
	result = m_pFmodSystem->getVersion(&version);
	ErrorCheck(result);
	
	if (version < FMOD_VERSION)
	{
		CORE_ERROR("SoundManager Initialization Failed!\n\nYou are using an old version of FMOD {0}. This program requires {1}", version, (unsigned int)FMOD_VERSION);
		return;
	}

	result = m_pFmodSystem->getNumDrivers(&numdrivers);
	ErrorCheck(result);
	if (numdrivers == 0)
	{
		result = m_pFmodSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		ErrorCheck(result);
	}
	else
	{
		result = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr);
		ErrorCheck(result);
	}

}

bool SoundManager::ErrorCheck(FMOD_RESULT res)
{
	if(res != FMOD_OK)
	{
		CORE_ERROR("FMOD error! {0}", std::to_string(res));
		return false;
	}
	return true;
}

void SoundManager::LoadSound(const std::map<int, SoundData>& soundFiles)
{
	for (const std::pair<int, SoundData>& soundFile : soundFiles)
	{
		LoadSound(soundFile.first, soundFile.second);
	}
}

void SoundManager::LoadSound(int soundID, const SoundData& soundFile)
{
	//Already Loaded?
	//***************
	if (m_pSounds.find(soundID) != m_pSounds.end())
	{
		CORE_ERROR("SoundManager::LoadSound >> Sound on ID {0} already exists", std::to_string(soundID));
		return;	
	}

	//Create Sound
	//************
	FMOD::Sound* pSound = nullptr;
	if (!ErrorCheck(m_pFmodSystem->createStream(soundFile.file.c_str(), soundFile.mode, nullptr, &pSound)))
	{
		CORE_ERROR("SoundManager::LoadSound >> Failed to load sound");
		return;
	}

	//Add
	//***
	m_pSounds[soundID] = pSound;
}

void SoundManager::PlaySoundByID(int soundID, int channelID, float volume, eSoundMerge merge)
{
	//Validate
	//********
	auto it = m_pSounds.find(soundID);
#ifdef _DEBUG
	if (it == m_pSounds.cend())
	{
		CORE_ERROR("SoundManager::PlaySoundByID >> Invalid Sound ID {0}", std::to_string(soundID));
		return;
	}
#endif

	FMOD::Channel* pChannel = m_pChannels[channelID];

	//Check MergeType
	//***************
	switch (merge)
	{
	case eSoundMerge::ContinueElseReplay:
		if (pChannel)
		{
			FMOD::Sound* pCurrent = nullptr;
			pChannel->getCurrentSound(&pCurrent);
			if (pCurrent == it->second) return;
			pChannel->stop();
		}
		break;
	case eSoundMerge::ContinueElseOverlap:
		if (pChannel)
		{
			FMOD::Sound* pCurrent = nullptr;
			pChannel->getCurrentSound(&pCurrent);
			if (pCurrent == it->second) return;
		}
		break;
	//case eSoundMerge::Overlap:
	//	//Do Nothing
	//	break;
	case eSoundMerge::Replay:
		//Stop Current so next can play
		if (pChannel) pChannel->stop();
		break;
	}

	//Play
	//****
	ErrorCheck(m_pFmodSystem->playSound(it->second, 0, false, &m_pChannels[channelID]));
	m_pChannels[channelID]->setVolume(volume * m_BaseVolume);
}

void SoundManager::PauseSoundByID(int soundID, int channelID)
{
	//Validate
	//********
	auto it = m_pSounds.find(soundID);
	if (it == m_pSounds.cend())
	{
		CORE_ERROR("SoundManager::PauseSoundByID >> Invalid Sound ID {0}", std::to_string(soundID));
		return;
	}

	//Pause
	//*****
	ErrorCheck(m_pFmodSystem->playSound(it->second, 0, true, &m_pChannels[channelID]));
}

void SoundManager::PauseAll(bool paused)
{
	for (const std::pair<int, FMOD::Channel*>& pChannel : m_pChannels)
	{
		if (pChannel.second) pChannel.second->setPaused(paused);
	}
}

void SoundManager::PauseAllExcept(int channelID, bool paused)
{
	for (const std::pair<int, FMOD::Channel*>& pChannel : m_pChannels)
	{
		if (pChannel.second && pChannel.first != channelID) pChannel.second->setPaused(paused);
	}
}

void SoundManager::Pause(int channelID, bool paused)
{
	FMOD::Channel* pChannel = m_pChannels[channelID];
	if (pChannel) pChannel->setPaused(paused);
}

void SoundManager::Pause(const std::vector<int>& channelIDs, bool paused)
{
	for (int channelID : channelIDs)
	{
		Pause(channelID, paused);
	}
}

void SoundManager::StopAll()
{
	for (const std::pair<int, FMOD::Channel*>& pChannel : m_pChannels)
	{
		if (pChannel.second) pChannel.second->stop();
	}
}

void SoundManager::StopAllExcept(int channelID)
{
	for (const std::pair<int, FMOD::Channel*>& pChannel : m_pChannels)
	{
		if (pChannel.second && pChannel.first != channelID) pChannel.second->stop();
	}
}

void SoundManager::Stop(int channelID)
{
	FMOD::Channel* pChannel = m_pChannels[channelID];
	if (pChannel)
	{
		pChannel->stop();
	}
}

void SoundManager::Stop(const std::vector<int>& channelIDs)
{
	for (int channelID : channelIDs)
	{
		Stop(channelID);
	}
}

void SoundManager::StopIf(int channelID, int soundID)
{
	FMOD::Channel* pChannel = m_pChannels[channelID];
	if (pChannel)
	{
		FMOD::Sound* pSound = nullptr;
		pChannel->getCurrentSound(&pSound);
		if (pSound && pSound == m_pSounds[soundID])
		{
			pChannel->stop();
		}
	}
}

void SoundManager::SetBaseVolume(float volume)
{
	m_BaseVolume = volume;
	for (std::pair<int, FMOD::Channel*> channel : m_pChannels)
	{
		FMOD::Channel* pChannel = channel.second;
		if (pChannel)
		{
			float vol = 0.0f;
			pChannel->getVolume(&vol);
			pChannel->setVolume(vol * m_BaseVolume);
		}
	}
}


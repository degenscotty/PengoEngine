#pragma once
#include "Singleton.h"

#include <chrono>

class GameTime : public Singleton<GameTime>
{
public:
	GameTime();
	~GameTime() = default;

	void Initialize();
	float GetElapsedSec() const;
	unsigned int GetFPS() const;

	void UpdateCurrentTime();
	void UpdateElapsedSec();
	void UpdatePreviousTime();

	void SetCurrentTime(const std::chrono::high_resolution_clock::time_point& timePoint);
	void SetPreviousTime(const std::chrono::high_resolution_clock::time_point& timePoint);

private:

	std::chrono::high_resolution_clock::time_point m_CurrentTime;
	std::chrono::high_resolution_clock::time_point m_PreviousTime;
	float m_ElapsedSec;
};



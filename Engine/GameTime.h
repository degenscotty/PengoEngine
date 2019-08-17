#pragma once
#include "Singleton.h"

#include <chrono>

class GameTime : public Singleton<GameTime>
{
public:
	~GameTime() = default;

	void Update();
	float GetElapsedSec() const;
	unsigned int GetFPS() const;

private:

	std::chrono::high_resolution_clock::time_point m_CurrentTime;
	std::chrono::high_resolution_clock::time_point m_PreviousTime;
	float m_ElapsedSec;
};



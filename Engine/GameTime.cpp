#include "pch.h"
#include "GameTime.h"

GameTime::GameTime()
	: m_ElapsedSec(0.0f)
	, m_CurrentTime()
	, m_PreviousTime()
{}

void GameTime::Initialize()
{
	CORE_INFO("GameTime Initialized!");
}

void GameTime::UpdateCurrentTime()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
}

void GameTime::UpdateElapsedSec()
{
	m_ElapsedSec = std::chrono::duration<float>(m_CurrentTime - m_PreviousTime).count();
}

void GameTime::UpdatePreviousTime()
{
	m_PreviousTime = m_CurrentTime;
}

void GameTime::SetCurrentTime(const std::chrono::high_resolution_clock::time_point& timePoint)
{
	m_CurrentTime = timePoint;
}

void GameTime::SetPreviousTime(const std::chrono::high_resolution_clock::time_point& timePoint)
{
	m_PreviousTime = timePoint;
}

float GameTime::GetElapsedSec() const
{
	return m_ElapsedSec;
}

unsigned int GameTime::GetFPS() const
{
	return static_cast<unsigned int>(1.0f / m_ElapsedSec);
}

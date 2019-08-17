#include "pch.h"
#include "GameTime.h"

void GameTime::Update()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_ElapsedSec = std::chrono::duration<float>(m_CurrentTime - m_PreviousTime).count();
	m_PreviousTime = m_CurrentTime;
}

float GameTime::GetElapsedSec() const
{
	return m_ElapsedSec;
}

unsigned int GameTime::GetFPS() const
{
	return static_cast<unsigned int>(1.0f / m_ElapsedSec);
}

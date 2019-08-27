#include "ScoreManager.h"


ScoreManager::ScoreManager()
	: m_pRenderer(Renderer::GetInstance())
	, m_Score(0)
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::Initialize()
{

}

void ScoreManager::Update()
{

}

void ScoreManager::AddScore(int score)
{
	m_Score += score;
}

int ScoreManager::GetScore()
{
	return m_Score;
}

void ScoreManager::Reset()
{
	m_Score = 0;
}

void ScoreManager::Render()
{
	m_pRenderer->RenderText(std::to_string(m_Score), { 255, 255, 255 }, "RetroGaming.ttf", 20, 224, 528);
}

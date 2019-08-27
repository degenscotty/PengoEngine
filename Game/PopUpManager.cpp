#include "PopUpManager.h"

PopUpManager::PopUpManager()
	: m_pGameTime(GameTime::GetInstance())
	, m_pRenderer(Renderer::GetInstance())
	, m_PopUps()
{
}

PopUpManager::~PopUpManager()
{
}

void PopUpManager::Update()
{
	for (size_t i{ 0 }; i < m_PopUps.size(); ++i)
	{
		m_PopUps[i].timer += m_pGameTime->GetElapsedSec();

		if (m_PopUps[i].timer > 1.5f)
		{
			m_PopUps.erase(m_PopUps.begin() + i);
		}
	}
}

void PopUpManager::AddPopUp(const std::string& string, const glm::vec2& position)
{
	m_PopUps.push_back({ string, position, 0.0f });
}

void PopUpManager::Render()
{
	for (size_t i{ 0 }; i < m_PopUps.size(); ++i)
	{
		m_pRenderer->RenderText(m_PopUps[i].number, { 255, 255, 255 }, "RetroGaming.ttf", 16, (int)m_PopUps[i].position.x, (int)m_PopUps[i].position.y);
	}
}

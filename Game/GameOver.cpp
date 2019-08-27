#include "GameOver.h"

#include "ResourceManager.h"
#include "PengoScene.h"

GameOver::GameOver()
	: Scene(L"GameOver")
	, m_BackButton({ 224, 324 }, "BackS.png", "BackNS.png")
	, m_TryAgainButton({ 224, 300 }, "TryAgainS.png", "TryAgainNS.png")
	, m_pRenderer(Renderer::GetInstance())
	, m_pInputManager(InputManager::GetInstance())
	, m_pGameOverBackGround(nullptr)
	, m_pScoreManager(ScoreManager::GetInstance())
{
}

GameOver::~GameOver()
{
}

void GameOver::Initialize()
{
	m_pGameOverBackGround = ResourceManager::GetInstance()->LoadTexture("GameOverBackGround.png");

	m_BackButton.Initialize();
	m_TryAgainButton.Initialize();
}

void GameOver::Update()
{
	glm::vec2 mousePos = { m_pInputManager->GetMousePos().first, m_pInputManager->GetMousePos().second };

	m_BackButton.Update(mousePos);
	m_TryAgainButton.Update(mousePos);

	if (m_pInputManager->IsMouseButtonPressed(MOUSE_LEFT))
	{
		if (m_BackButton.OnClick())
		{
			CLIENT_INFO("BackButton Clicked");
			SceneManager::GetInstance()->SetActiveScene(L"MainMenu");
		}
		if (m_TryAgainButton.OnClick())
		{
			CLIENT_INFO("TryAgainButton Clicked");
			m_pScoreManager->Reset();
			SceneManager::GetInstance()->AddScene(new PengoScene());
			SceneManager::GetInstance()->SetActiveScene(L"PengoScene");
		}
	}
}

void GameOver::Render()
{
	m_pRenderer->RenderTexture(m_pGameOverBackGround->GetSDLTexture(), 0, 0);

	m_BackButton.Render();
	m_TryAgainButton.Render();

	m_pRenderer->RenderText(std::to_string(m_pScoreManager->GetScore()), { 255, 255, 255 }, "RetroGaming.ttf", 20, 264, 458);
}

#include "WinScene.h"

#include "ResourceManager.h"
#include "PengoScene.h"

WinScene::WinScene()
	: Scene(L"WinScene")
	, m_pInputManager(InputManager::GetInstance())
	, m_pRenderer(Renderer::GetInstance())
	, m_pScoreManager(ScoreManager::GetInstance())
	, m_pWinBackGround(nullptr)
	, m_BackButton({ 224, 324 }, "BackS.png", "BackNS.png")
	, m_TryAgainButton({ 224, 300 }, "TryAgainS.png", "TryAgainNS.png")
{
}

WinScene::~WinScene()
{
}

void WinScene::Initialize()
{
	m_pWinBackGround = ResourceManager::GetInstance()->LoadTexture("WinBackGround.png");

	m_BackButton.Initialize();
	m_TryAgainButton.Initialize();
}

void WinScene::Update()
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

void WinScene::Render()
{
	m_pRenderer->RenderTexture(m_pWinBackGround->GetSDLTexture(), 0, 0);

	m_BackButton.Render();
	m_TryAgainButton.Render();

	m_pRenderer->RenderText(std::to_string(m_pScoreManager->GetScore()), { 255, 255, 255 }, "RetroGaming.ttf", 20, 264, 458);

}

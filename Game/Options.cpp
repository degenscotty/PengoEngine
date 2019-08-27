#include "Options.h"

#include "ResourceManager.h"

Options::Options()
	: Scene(L"Options")
	, m_pRenderer(Renderer::GetInstance())
	, m_pInputManager(InputManager::GetInstance())
	, m_BackButton({ 224, 424 }, "BackS.png", "BackNS.png")
{
}

Options::~Options()
{
}

void Options::Initialize()
{
	m_pOptionsBackGround = ResourceManager::GetInstance()->LoadTexture("OptionsBackGround.png");

	m_BackButton.Initialize();
}

void Options::Update()
{
	glm::vec2 mousePos = { m_pInputManager->GetMousePos().first, m_pInputManager->GetMousePos().second };

	m_BackButton.Update(mousePos);

	if (m_pInputManager->IsMouseButtonPressed(MOUSE_LEFT))
	{
		if (m_BackButton.OnClick())
		{
			CLIENT_INFO("BackButton Clicked");
			SceneManager::GetInstance()->SetActiveScene(L"MainMenu");
		}
	}
}

void Options::Render()
{
	m_pRenderer->RenderTexture(m_pOptionsBackGround->GetSDLTexture(), 0, 0);

	m_BackButton.Render();
}

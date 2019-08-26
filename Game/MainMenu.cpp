#include "MainMenu.h"
#include "ResourceManager.h"
#include "SoundManager.h"

MainMenu::MainMenu()
	: Scene(L"MainMenu")
	, m_PlayButton({ 224, 156 }, "PlayS.png", "PlayNS.png")
	, m_OptionsButton({ 224, 184 }, "OptionsS.png", "OptionsNS.png")
	, m_ExitButton({ 224, 208 }, "ExitS.png", "ExitNS.png")
	, m_pMainMenuBackGround(nullptr)
	, m_pInputManager(InputManager::GetInstance())
	, m_pRenderer(Renderer::GetInstance())
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Initialize()
{
	m_pMainMenuBackGround = ResourceManager::GetInstance()->LoadTexture("MainMenuBackGround.png");
	m_PlayButton.Initialize();
	m_OptionsButton.Initialize();
	m_ExitButton.Initialize();

	// --------------------------- LOAD SOUNDS ----------------------------- //

	auto soundManager = SoundManager::GetInstance();
	soundManager->LoadSound(0, SoundData{ "../Resources/popcorn_slow.mp3", FMOD_LOOP_NORMAL });

	soundManager->PlaySoundByID(0, 0, 0.1f, eSoundMerge::ContinueElseReplay);

}

void MainMenu::Update()
{
	glm::vec2 mousePos = { m_pInputManager->GetMousePos().first, m_pInputManager->GetMousePos().second };

	m_PlayButton.Update(mousePos);
	m_OptionsButton.Update(mousePos);
	m_ExitButton.Update(mousePos);

	if (m_pInputManager->IsMouseButtonPressed(MOUSE_LEFT))
	{
		if (m_PlayButton.OnClick())
		{
			CLIENT_INFO("PlayButton Clicked");
		}
		if (m_OptionsButton.OnClick())
		{
			CLIENT_INFO("OptionsButton Clicked");
		}
		if (m_ExitButton.OnClick())
		{
			CLIENT_INFO("ExitButton Clicked");
		}
	}
}

void MainMenu::Render()
{
	m_pRenderer->RenderTexture(m_pMainMenuBackGround->GetSDLTexture(), 0, 0);

	m_PlayButton.Render();
	m_OptionsButton.Render();
	m_ExitButton.Render();
}

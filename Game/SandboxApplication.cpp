#include "Application.h"
#include "PengoScene.h"
#include "MainMenu.h"
#include "Options.h"
#include "WinScene.h"
#include "GameOver.h"

class SandboxApplication : public Application
{
public:
	SandboxApplication()
	{
		SceneManager::GetInstance()->AddScene(new MainMenu());
		SceneManager::GetInstance()->AddScene(new Options());
		SceneManager::GetInstance()->AddScene(new WinScene());
		SceneManager::GetInstance()->AddScene(new GameOver());
	}

	~SandboxApplication()
	{
	}
};

Application* CreateApplication()
{
	return new SandboxApplication();
}

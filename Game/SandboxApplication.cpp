#include "Application.h"
#include "PengoScene.h"
#include "MainMenu.h"

class SandboxApplication : public Application
{
public:
	SandboxApplication()
	{
		SceneManager::GetInstance()->AddScene(new MainMenu());
		//SceneManager::GetInstance()->AddScene(new PengoScene());
	}

	~SandboxApplication()
	{
	}
};

Application* CreateApplication()
{
	return new SandboxApplication();
}

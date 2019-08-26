#pragma once
#include "Scene.h"
#include "Button.h"
#include "InputManager.h"
#include "Renderer.h"

class MainMenu : public Scene
{
public:
	MainMenu();
	~MainMenu();

	MainMenu(const MainMenu& other) = delete;
	MainMenu(MainMenu&& other) = delete;
	MainMenu& operator=(const MainMenu& other) = delete;
	MainMenu& operator=(MainMenu&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	Renderer* m_pRenderer;
	InputManager* m_pInputManager;

	Texture2D* m_pMainMenuBackGround;

	Button m_PlayButton;
	Button m_OptionsButton;
	Button m_ExitButton;
};


#pragma once
#include "Scene.h"

#include "ScoreManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Button.h"

class WinScene : public Scene
{
public:
	WinScene();
	~WinScene();

	WinScene(const WinScene& other) = delete;
	WinScene(WinScene&& other) = delete;
	WinScene& operator=(const WinScene& other) = delete;
	WinScene& operator=(WinScene&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	Renderer* m_pRenderer;
	InputManager* m_pInputManager;
	ScoreManager* m_pScoreManager;

	Texture2D* m_pWinBackGround;

	Button m_TryAgainButton;
	Button m_BackButton;
};


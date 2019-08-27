#pragma once
#include "Scene.h"

#include "ScoreManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Button.h"

class GameOver : public Scene
{
public:
	GameOver();
	~GameOver();

	GameOver(const GameOver& other) = delete;
	GameOver(GameOver&& other) = delete;
	GameOver& operator=(const GameOver& other) = delete;
	GameOver& operator=(GameOver&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	Renderer* m_pRenderer;
	InputManager* m_pInputManager;
	ScoreManager* m_pScoreManager;

	Texture2D* m_pGameOverBackGround;

	Button m_TryAgainButton;
	Button m_BackButton;
};


#pragma once
#include "Scene.h"

#include "InputManager.h"
#include "Renderer.h"
#include "Button.h"

class Texture2D;

class Options : public Scene
{
public:
	Options();
	~Options();

	Options(const Options& other) = delete;
	Options(Options&& other) = delete;
	Options& operator=(const Options& other) = delete;
	Options& operator=(Options&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	Renderer* m_pRenderer;
	InputManager* m_pInputManager;

	Texture2D* m_pOptionsBackGround;

	Button m_BackButton;
};


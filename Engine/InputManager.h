#pragma once
#include "Singleton.h"
#include "InputDefinitions.h"

class InputManager : public Singleton<InputManager>
{
public:
	void Update();

	bool IsKeyPressed(int keycode);
	bool IsMouseButtonPressed(int button);

	float GetMouseX();
	float GetMouseY();

	std::pair<float, float> GetMousePos();

	bool Quit();

	void QuitGame();

private:
	SDL_Event e;

	bool m_KeyDown[KEYBOARD_SIZE];
	bool m_KeyUp[KEYBOARD_SIZE];

	bool m_MouseDown[MOUSE_MAX];
	bool m_MouseUp[MOUSE_MAX];

	int m_MouseX;
	int m_MouseY;

	bool m_Quit = false;
};



#pragma once
#include "Window.h"

class Application
{
public:
	Application();
	virtual ~Application();

	void Initialize();
	void Run();

	inline static Application& get() { return *s_Instance; }
	inline Window& GetWindow() { return *m_pWindow; }
private:
	Window* m_pWindow;
	bool m_Running;

	static Application* s_Instance;
};

Application* CreateApplication();


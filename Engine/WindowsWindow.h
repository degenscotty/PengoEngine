#pragma once
#include "Window.h"
#include "InputManager.h"

class WindowsWindow final : public Window
{
public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return m_Data.Width; }
	inline unsigned int GetHeight() const override { return m_Data.Height; }

	// Window attributes
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

	inline virtual void* GetNativeWindow() const { return m_pWindow; }
	inline virtual void* GetSDLContext() const { return m_Context; }

	inline SDL_Window* GetSDLWindow() { return m_pWindow; }
private:
	virtual void Init(const WindowProps& props);
	virtual void Shutdown();
private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_Context;
	InputManager* m_pInput;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	WindowData m_Data;
};

#include "pch.h"
#include "WindowsWindow.h"

static bool s_SDLInitialized = false;

Window* Window::Create(const WindowProps& props)
{
	return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
	: m_pInput(InputManager::GetInstance())
{
	Init(props);
}

WindowsWindow::~WindowsWindow()
{
	Shutdown();
}

void WindowsWindow::Init(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

	// TODO: glfwTerminate on system shutdown
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		CORE_ASSERT("Core::Initialize(), error when calling SDL_Init : {0}", SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	m_pWindow = SDL_CreateWindow(
		m_Data.Title.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		(int)props.Width,
		(int)props.Height,
		SDL_WINDOW_OPENGL);

	//// Set the Projection matrix to the identity matrix
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//// Set up a two-dimensional orthographic viewing region.
	//gluOrtho2D(0, m_Data.Width, 0, m_Data.Height); // y from bottom to top

	//// Set the viewport to the client window area
	//// The viewport is the rectangular region of the window where the image is drawn.
	//glViewport(0, 0, int(m_Data.Width), int(m_Data.Height));

	//// Set the Model view matrix to the identity matrix
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//// Enable color blending and use alpha blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (m_pWindow == nullptr)
	{
		CORE_ERROR("WindowsWindow::Initialize( ) > error when calling SDL_CreateWindow : {0}", SDL_GetError());
		return;
	}

	m_Context = SDL_GL_CreateContext(m_pWindow);
	if (m_Context == nullptr)
	{
		CORE_ERROR("WindowsWindow::Initialize( ) > error when calling SDL_GL_CreateContext: {0}", SDL_GetError());
		return;
	}

	SDL_SetWindowInputFocus(m_pWindow);
	SetVSync(true);
}

void WindowsWindow::Shutdown()
{
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void WindowsWindow::OnUpdate()
{
	m_pInput->Update();
}

void WindowsWindow::SetVSync(bool enabled)
{
	if (enabled)
		SDL_GL_SetSwapInterval(1);
	else
		SDL_GL_SetSwapInterval(0);

	m_Data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const
{
	return m_Data.VSync;
}


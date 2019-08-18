#include "pch.h"

#include "Application.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "GameTime.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GarbageCollector.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	if (!s_Instance)
	{
		s_Instance = this;
	}
	Initialize();
}

Application::~Application()
{
	SceneManager::DestroyInstance();
	GameTime::DestroyInstance();
	Renderer::DestroyInstance();
	InputManager::DestroyInstance();
	ResourceManager::DestroyInstance();
	GarbageCollector::DestroyInstance();

	delete m_pWindow;
	m_pWindow = nullptr;
}

void Application::Initialize()
{
	m_pWindow = Window::Create();
	Renderer::GetInstance()->Initialize();
	SceneManager::GetInstance()->Initialize();
}

void Application::Run()
{
	GameTime* gameTime = GameTime::GetInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();
	InputManager* input = InputManager::GetInstance();

	while (!input->Quit())
	{
		gameTime->Update();
		m_pWindow->OnUpdate();
		sceneManager->Update();

		renderer->ClearBuffer();
		sceneManager->Render();
		renderer->Render();
	}
}
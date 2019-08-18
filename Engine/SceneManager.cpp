#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
	: m_pScenes()
	, m_ActiveScene(nullptr)
	, m_NewActiveScene(nullptr)
	, m_IsInitialized(false)
{
}

SceneManager::~SceneManager()
{
	for (Scene* scene : m_pScenes)
		SafeDelete(scene);
}

void SceneManager::Initialize()
{
	for (Scene* scene : m_pScenes)
	{
		scene->RootInitialize();
	}

	m_IsInitialized = true;
}

void SceneManager::Update()
{
	if (m_NewActiveScene)
	{
		m_ActiveScene = m_NewActiveScene;
		m_NewActiveScene = nullptr;
	}

	if (m_ActiveScene)
	{
		m_ActiveScene->RootUpdate();
	}
}

void SceneManager::Render()
{
	if (m_ActiveScene)
		m_ActiveScene->RootRender();
}

void SceneManager::AddScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it == m_pScenes.end())
	{
		m_pScenes.push_back(pScene);

		if (m_ActiveScene == nullptr && m_NewActiveScene == nullptr)
			m_ActiveScene = pScene;

		if (m_IsInitialized)
			pScene->RootInitialize();
	}
}

void SceneManager::RemoveScene(Scene* pScene)
{
	const auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it != m_pScenes.end())
	{
		m_pScenes.erase(it);
	}
}

void SceneManager::SetActiveScene(const std::wstring sceneName)
{
	const auto it = find_if(m_pScenes.begin(), m_pScenes.end(), [sceneName](Scene* scene)
	{
		return wcscmp(scene->m_SceneName.c_str(), sceneName.c_str()) == 0;
	});

	if (it != m_pScenes.end())
	{
		m_NewActiveScene = *it;
	}
}

#include "pch.h"
#include "Scene.h"

unsigned int Scene::s_IdCounter = 0;

Scene::Scene(const std::wstring& name)
	: m_SceneName(name)
	, m_pGameObjects()
	, m_IsInitialized(false)
{
}

Scene::~Scene()
{
	for (GameObject* gameObject : m_pGameObjects)
	{
		SafeDelete(gameObject);
	}
}

void Scene::Add(GameObject* object)
{
	m_pGameObjects.push_back(object);
}

void Scene::RootInitialize()
{
	Initialize();

	for (size_t i{}; i < m_pGameObjects.size(); ++i)
	{
		m_pGameObjects[i]->RootInitialize();
	}

	m_IsInitialized = true;
}

void Scene::RootUpdate()
{
	Update();

	for (size_t i{}; i < m_pGameObjects.size(); ++i)
	{
		m_pGameObjects[i]->RootUpdate();
	}
}

void Scene::RootRender()
{
	Render();

	for (size_t i{}; i < m_pGameObjects.size(); ++i)
	{
		m_pGameObjects[i]->RootRender();
	}
}

const std::wstring& Scene::GetSceneName()
{
	return m_SceneName;
}



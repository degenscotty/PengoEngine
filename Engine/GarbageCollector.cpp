#include "pch.h"
#include "GarbageCollector.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "Scene.h"
#include "SceneManager.h"

GarbageCollector::~GarbageCollector()
{
	//RootDestroy();
}

void GarbageCollector::RootDestroy()
{
	for (size_t i = 0, j = m_pGameObjects.size(); i < j; ++i)
	{
		auto* gameObject = m_pGameObjects[i];
		auto* pScene = gameObject->GetScene();
		if (pScene) pScene->Remove(gameObject);
		delete gameObject;
	}
	m_pGameObjects.clear();
}

void GarbageCollector::RootSceneDestroy()
{
	for (size_t i = 0, j = m_pGameScenes.size(); i < j; ++i)
	{
		auto* pGameScene = m_pGameScenes[i];
		SceneManager::GetInstance()->RemoveScene(pGameScene);
		delete pGameScene;
	}
	m_pGameScenes.clear();
}

void GarbageCollector::Destroy(GameObject* pObject)
{
	auto it = std::find(m_pGameObjects.begin(), m_pGameObjects.end(), pObject);
	if (it == m_pGameObjects.end())
	{
		m_pGameObjects.push_back(pObject);
	}
}

void GarbageCollector::Destroy(Scene* pGameScene)
{
	auto it = std::find(m_pGameScenes.begin(), m_pGameScenes.end(), pGameScene);
	if (it == m_pGameScenes.end())
	{
		m_pGameScenes.push_back(pGameScene);
	}
}

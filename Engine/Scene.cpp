#include "pch.h"
#include "Scene.h"

unsigned int Scene::s_IdCounter = 0;

Scene::Scene(const std::wstring& name)
	: m_SceneName(name)
	, m_pGameObjects()
	, m_pCollisionComponents()
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

void Scene::Add(GameObject* gameObject)
{
	gameObject->m_pScene = this;
	m_pGameObjects.push_back(gameObject);

	if (m_IsInitialized)
	{
		gameObject->RootInitialize();
	}
}

void Scene::Remove(GameObject* gameObject)
{
	const auto it = std::find(m_pGameObjects.begin(), m_pGameObjects.end(), gameObject);

	if (it != m_pGameObjects.end())
	{
		m_pGameObjects.erase(it);
	}
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

		auto collisionComp = m_pGameObjects[i]->GetComponent<CollisionComponent>();

		if (collisionComp)
		{
			m_pCollisionComponents.push_back(collisionComp);
		}
	}

	if (m_pCollisionComponents.size() > 1)
	{
		for (int i{ 0 }; i != m_pCollisionComponents.size() - 1; ++i)
		{
			for (int j{ i + 1 }; j < m_pCollisionComponents.size(); ++j)
			{
				if (m_pCollisionComponents[i]->IsColliding(m_pCollisionComponents[j]->GetRect()))
				{
					GameObject* pGameObject = m_pCollisionComponents[i]->GetGameObject();
					pGameObject->m_CollisionCallBack(m_pCollisionComponents[j]->GetGameObject());

					pGameObject = m_pCollisionComponents[j]->GetGameObject();
					pGameObject->m_CollisionCallBack(m_pCollisionComponents[i]->GetGameObject());
				}
			}
		}
	}

	m_pCollisionComponents.clear();
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



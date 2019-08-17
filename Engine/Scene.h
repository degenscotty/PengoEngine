#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "Components.h"

#include <vector>
#include <string>

class Scene
{
public:
	Scene(const std::wstring& name);
	~Scene();

	void Add(GameObject* object);

	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	const std::wstring& GetSceneName();

protected:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

private:
	friend class SceneManager;

	void RootInitialize();
	void RootUpdate();
	void RootRender();

	bool m_IsInitialized;
	std::wstring m_SceneName{};
	std::vector<GameObject*> m_pGameObjects;
	std::vector<CollisionComponent*> m_CollisionComponents;

	static unsigned int s_IdCounter;
};

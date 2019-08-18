#pragma once
#include "Singleton.h"

class GameObject;
class BaseComponent;
class Scene;

class GarbageCollector final : public Singleton<GarbageCollector>
{
public:
	GarbageCollector() = default;
	virtual ~GarbageCollector();

	void RootDestroy();
	void RootSceneDestroy();

	void Destroy(GameObject* pObject);
	void Destroy(Scene* pGameScene);
private:
	std::vector<GameObject*> m_pGameObjects;
	std::vector<Scene*> m_pGameScenes;
};


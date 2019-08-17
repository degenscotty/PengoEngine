#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) noexcept = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) noexcept = delete;

	void AddScene(Scene* pScene);
	void RemoveScene(Scene* pScene);
	void SetActiveScene(const std::wstring sceneName);

	Scene* GetActiveScene() const { return m_ActiveScene; }

	void Initialize();
	void Update();
	void Render();

private:
	bool m_IsInitialized;
	std::vector<Scene*> m_pScenes;
	Scene* m_ActiveScene;
	Scene* m_NewActiveScene;
};

#pragma once
#include "Singleton.h"
#include "SceneManager.h"
#include <string>

class Pengo;

class LevelManager : public Singleton<LevelManager>
{
public:
	LevelManager();
	~LevelManager();

	LevelManager(const LevelManager& other) = delete;
	LevelManager(LevelManager&& other) = delete;
	LevelManager& operator=(const LevelManager& other) = delete;
	LevelManager& operator=(LevelManager&& other) = delete;

	void Initialize();
	void InitializeLevel();
	void Update();
	void Render();

	wchar_t GetTile(int x, int y);
	void SetTile(int x, int y, wchar_t c);

	void SetPengo(Pengo* pengo);
	Pengo* GetPengo();

private:
	Pengo* m_pPengo;
	SceneManager* m_pSceneManager;

	int m_LevelWidth;
	int m_LevelHeight;

	std::wstring m_LevelString;
};


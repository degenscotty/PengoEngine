#pragma once
#include "Singleton.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include <string>
#include <vector>

class Pengo;
class ArrowBlock;
class Wall;

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

	void CheckArrowBlocks();
	void CheckArrowBlockSides(int x, int y, int index);

	wchar_t GetTile(int x, int y);
	void SetTile(int x, int y, wchar_t c);

	void SetPengo(Pengo* pengo);
	Pengo* GetPengo();

	bool CheckLevel();

private:
	Pengo* m_pPengo;
	ScoreManager* m_pScoreManager;
	SoundManager* m_pSoundManager;
	SceneManager* m_pSceneManager;

	int m_LevelWidth;
	int m_LevelHeight;

	bool m_ArrowBlockBonus;
	bool m_LevelInitialized;

	std::wstring m_LevelString;

	std::vector<ArrowBlock*> m_pArrowBlocks;
	std::vector<glm::vec2> m_ArrowBlockPositions;

	std::vector<Wall*> m_pWalls;
};


#pragma once
#include "Singleton.h"
#include "Renderer.h"

class ScoreManager : public Singleton<ScoreManager>
{
public:
	ScoreManager();
	~ScoreManager();

	ScoreManager(const ScoreManager& other) = delete;
	ScoreManager(ScoreManager&& other) = delete;
	ScoreManager& operator=(const ScoreManager& other) = delete;
	ScoreManager& operator=(ScoreManager&& other) = delete;

	void Initialize();
	void Update();
	void Render();

	void AddScore(int score);

private:
	Renderer* m_pRenderer;

	int m_Score;
};


#pragma once
#include "Scene.h"
#include "Pengo.h"
#include "LevelManager.h"
#include "ScoreManager.h"
#include "PopUpManager.h"

class PengoScene : public Scene
{
public:
	PengoScene();
	~PengoScene();

	PengoScene(const PengoScene& other) = delete;
	PengoScene(PengoScene&& other) = delete;
	PengoScene& operator=(const PengoScene& other) = delete;
	PengoScene& operator=(PengoScene&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	Pengo* m_pPengo;

	LevelManager* m_pLevelManager;
	ScoreManager* m_pScoreManager;
	PopUpManager* m_pPopUpManager;
};


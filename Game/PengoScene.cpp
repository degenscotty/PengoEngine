#include "pch.h"
#include "PengoScene.h"
#include "InputManager.h"
#include "Singleton.h"

PengoScene::PengoScene()
	: Scene(L"PengoScene")
	, m_pPengo(nullptr)
	, m_pLevelManager(LevelManager::GetInstance())
	, m_pScoreManager(ScoreManager::GetInstance())
{
}

PengoScene::~PengoScene()
{
	LevelManager::DestroyInstance();
	ScoreManager::DestroyInstance();
}

void PengoScene::Initialize()
{
	CORE_TRACE("PengoScene was initialized!");

	m_pPengo = new Pengo();

	m_pLevelManager->Initialize();
	m_pLevelManager->SetPengo(m_pPengo);

	Add(m_pPengo);
}

void PengoScene::Update()
{
	m_pScoreManager->Update();
	m_pLevelManager->Update();
}

void PengoScene::Render()
{
	m_pScoreManager->Render();
}

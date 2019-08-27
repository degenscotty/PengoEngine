#include "pch.h"
#include "PengoScene.h"
#include "InputManager.h"
#include "PopUpManager.h"
#include "Singleton.h"

PengoScene::PengoScene()
	: Scene(L"PengoScene")
	, m_pPengo(nullptr)
	, m_pLevelManager(LevelManager::GetInstance())
	, m_pScoreManager(ScoreManager::GetInstance())
	, m_pPopUpManager(PopUpManager::GetInstance())
{
}

PengoScene::~PengoScene()
{
	LevelManager::DestroyInstance();
	PopUpManager::DestroyInstance();
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

	if (!m_pLevelManager->CheckLevel())
		m_pLevelManager->InitializeLevel();

	m_pScoreManager->Update();
	m_pLevelManager->Update();
	m_pPopUpManager->Update();
}

void PengoScene::Render()
{
	m_pScoreManager->Render();
	m_pPopUpManager->Render();
}

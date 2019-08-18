#include "pch.h"
#include "PengoScene.h"
#include "InputManager.h"
#include "Singleton.h"

PengoScene::PengoScene()
	: Scene(L"PengoScene")
	, m_pPengo(nullptr)
	, m_pLevelManager(LevelManager::GetInstance())
{
}

PengoScene::~PengoScene()
{
	LevelManager::DestroyInstance();
}

void PengoScene::Initialize()
{
	CORE_TRACE("PengoScene was initialized!");

	m_pLevelManager->Initialize();

	m_pPengo = new Pengo();

	Add(m_pPengo);
}

void PengoScene::Update()
{
}

void PengoScene::Render()
{
}
#include "pch.h"
#include "PengoScene.h"
#include "InputManager.h"

PengoScene::PengoScene()
	: Scene(L"PengoScene")
	, m_pPengo(nullptr)
{
}

PengoScene::~PengoScene()
{
}

void PengoScene::Initialize()
{
	CORE_TRACE("PengoScene was initialized!");

	m_pPengo = new Pengo();

	Add(m_pPengo);
}

void PengoScene::Update()
{
	if (InputManager::GetInstance()->IsKeyPressed(KEY_A))
	{
		CORE_INFO("A key was pressed!");
	}
}

void PengoScene::Render()
{
}

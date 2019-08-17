#include "Pengo.h"

#include "GameTime.h"

Pengo::Pengo()
	: m_pTransform(GetTransform())
	, m_Sprite(nullptr)
	, m_pInput(InputManager::GetInstance())
	, m_MoveSpeed(25.0f)
	, m_State()
{
}

Pengo::~Pengo()
{
}

void Pengo::Initialize()
{
	m_Sprite = new SpriteComponent("Pengo.jpg", 4, 2);

	m_Sprite->AddClip(2, true);
	m_Sprite->AddClip(2, true);
	m_Sprite->AddClip(2, true);
	m_Sprite->AddClip(2, true);

	AddComponent(m_Sprite);
}

void Pengo::Update()
{
	auto gameTime = GameTime::GetInstance();

	float elapsedSec = gameTime->GetElapsedSec();

	if (m_pInput->IsKeyPressed(KEY_DOWN))
	{
		GetTransform()->MoveWorld(0, m_MoveSpeed * elapsedSec);

		if (m_State != State::DWALK)
		{
			m_Sprite->SetClipIndex(State::DWALK);
			m_State = DWALK;
		}
	}
	if (m_pInput->IsKeyPressed(KEY_UP))
	{
		GetTransform()->MoveWorld(0, -m_MoveSpeed * elapsedSec);

		if (m_State != State::UWALK)
		{
			m_Sprite->SetClipIndex(State::UWALK);
			m_State = UWALK;
		}
	}
	if (m_pInput->IsKeyPressed(KEY_RIGHT))
	{
		GetTransform()->MoveWorld(m_MoveSpeed * elapsedSec, 0);

		if (m_State != State::RWALK)
		{
			m_Sprite->SetClipIndex(State::RWALK);
			m_State = RWALK;
		}
	}
	if (m_pInput->IsKeyPressed(KEY_LEFT))
	{
		GetTransform()->MoveWorld(-m_MoveSpeed * elapsedSec, 0);

		if (m_State != State::LWALK)
		{
			m_Sprite->SetClipIndex(State::LWALK);
			m_State = LWALK;
		}
	}
}

void Pengo::Render()
{
}

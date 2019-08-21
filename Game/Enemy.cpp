#include "Enemy.h"
#include "Components.h"
#include "Block.h"
#include <string>
#include "LevelManager.h"
#include <time.h>

Enemy::Enemy(const glm::vec2& position)
	: m_pLevelManager(LevelManager::GetInstance())
	, m_pSprite(nullptr)
	, m_pGameTime(GameTime::GetInstance())
	, m_pTransform(GetTransform())
	, m_Destination()
	, m_Destroy(false)
	, m_MoveSpeed(60.0f)
	, m_State(State::IDLE)
	, m_Direction(Direction::NONE)
	, m_SpawnPosition(position)
	, m_WanderTimer(0.0f)
	, m_SeekTimer(0.0f)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	srand(unsigned int(time(NULL)));

	// ------------------------------------------- Sprite Component ------------------------------------------ //

	m_pSprite = new SpriteComponent("SnoBee.png", 13, 7, 32);
	m_pSprite->AddClip(7, false);

	m_pSprite->AddClip(2, true);
	m_pSprite->AddClip(2, true);
	m_pSprite->AddClip(2, true);
	m_pSprite->AddClip(2, true);

	m_pSprite->AddClip(2, true);
	m_pSprite->AddClip(2, true);
	m_pSprite->AddClip(2, true);
	m_pSprite->AddClip(2, true);

	m_pSprite->AddClip(2, false);
	m_pSprite->AddClip(2, false);
	m_pSprite->AddClip(2, false);
	m_pSprite->AddClip(2, false);

	AddComponent(m_pSprite);

	// ------------------------------- Collision Component ------------------------------------- //

	auto collisionComp = new CollisionComponent(32.0f, 32.0f);

	AddComponent(collisionComp);

	GetTransform()->Translate(m_SpawnPosition);

	m_Destination = m_SpawnPosition;

	m_State = State::WANDERING;
	m_Direction = Direction(rand() % 4);
}

void Enemy::Update()
{
	srand(unsigned int(time(NULL)));

	float elapsedSec = m_pGameTime->GetElapsedSec();

	m_WanderTimer += elapsedSec;

	if (m_State == State::WANDERING && m_pTransform->GetPosition() == m_Destination)
	{
		CheckNextDirection();
	}

	UpdateMovement();
	UpdateAnimations();
}
void Enemy::CheckNextDirection()
{
	switch (m_Direction)
	{
	case Direction::Down:
	{
		m_Destination.y += 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar == L'.')
			m_Direction = Direction::Down;
		else 
		{
			m_Direction = Direction(rand() % 4);
			m_Destination.y -= 32.0f;
			CheckNextDirection();
		}
		break;
	}
	case Direction::Up:
	{
		m_Destination.y -= 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar == '.')
			m_Direction = Direction::Up;
		else
		{
			m_Direction = Direction(rand() % 4);
			m_Destination.y += 32.0f;
			CheckNextDirection();
		}
		break;
	}
	case Direction::Right:
	{
		m_Destination.x += 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar == '.')
			m_Direction = Direction::Right;
		else
		{
			m_Direction = Direction(rand() % 4);
			m_Destination.x -= 32.0f;
			CheckNextDirection();
		}
		break;
	}
	case Direction::Left:
	{
		m_Destination.x -= 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar == '.')
			m_Direction = Direction::Left;
		else
		{
			m_Direction = Direction(rand() % 4);
			m_Destination.x += 32.0f;
			CheckNextDirection();
		}
		break;
	}
	}
}

void Enemy::UpdateStates()
{

}

void Enemy::UpdateMovement()
{
	switch (m_Direction)
	{
	case Direction::Down:
	{
		m_pTransform->Move(0, m_MoveSpeed * m_pGameTime->GetElapsedSec());

		if (m_pTransform->GetPosition().y > m_Destination.y)
		{
			m_pTransform->Translate(m_Destination);
		}

		break;
	}
	case Direction::Up:
	{
		m_pTransform->Move(0, -(m_MoveSpeed * m_pGameTime->GetElapsedSec()));

		if (m_pTransform->GetPosition().y < m_Destination.y)
		{
			m_pTransform->Translate(m_Destination);
		}
		break;
	}
	case Direction::Right:
	{
		m_pTransform->Move(m_MoveSpeed * m_pGameTime->GetElapsedSec(), 0);

		if (m_pTransform->GetPosition().x > m_Destination.x)
		{
			m_pTransform->Translate(m_Destination);
		}
		break;
	}
	case Direction::Left:
	{
		m_pTransform->Move(-(m_MoveSpeed * m_pGameTime->GetElapsedSec()), 0);

		if (m_pTransform->GetPosition().x < m_Destination.x)
		{
			m_pTransform->Translate(m_Destination);
		}
		break;
	}
	}
}

void Enemy::UpdateAnimations()
{
	if (m_State == State::WANDERING)
	{
		switch (m_Direction)
		{
		case Direction::Down:
		{
			m_pSprite->SetClipIndex(1);
			break;
		}
		case Direction::Up:
		{
			m_pSprite->SetClipIndex(4);
			break;
		}
		case Direction::Right:
		{
			m_pSprite->SetClipIndex(3);
			break;
		}
		case Direction::Left:
		{
			m_pSprite->SetClipIndex(2);
			break;
		}
		case Direction::NONE:
		{
			m_pSprite->SetClipIndex(1);
			break;
		}
		}
	}
}

void Enemy::Render()
{

}

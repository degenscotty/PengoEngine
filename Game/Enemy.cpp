#include "Enemy.h"
#include "Components.h"
#include "Block.h"
#include "Pengo.h"
#include <string>
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
	, m_PunchTimer(0.0f)
	, m_SpawnTimer(0.0f)
	, m_PunchCooldown(float(rand() % 5 + 5))
	, m_WanderCooldown(float(rand() % 10 + 10))
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

	UpdateStates();
	UpdateMovement();
	UpdateAnimations();
}

void Enemy::CheckNextWander(int index)
{
	--index;
	if (index < 1)
		return;

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
			CheckNextWander(index);
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
			CheckNextWander(index);
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
			CheckNextWander(index);
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
			CheckNextWander(index);
		}
		break;
	}
	}
}

void Enemy::CheckNextPunch(int index)
{
	--index;
	if (index < 1)
		return;

	switch (m_Direction)
	{
	case Direction::Down:
	{
		m_Destination.y += 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar != L' ' && wchar != L'#' && wchar != L'A')
			m_Direction = Direction::Down;
		else
		{
			m_Direction = Direction(rand() % 4);
			m_Destination.y -= 32.0f;
			CheckNextPunch(index);
		}
		break;
	}
	case Direction::Up:
	{
		m_Destination.y -= 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar != L' ' && wchar != L'#' && wchar != L'A')
			m_Direction = Direction::Up;
		else
		{
			m_Direction = Direction(rand() % 4);
			m_Destination.y += 32.0f;
			CheckNextPunch(index);
		}
		break;
	}
	case Direction::Right:
	{
		m_Destination.x += 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar != L' ' && wchar != L'#' && wchar != L'A')
			m_Direction = Direction::Right;
		else
		{
			m_Direction = Direction(rand() % 4);
			m_Destination.x -= 32.0f;
			CheckNextPunch(index);
		}
		break;
	}
	case Direction::Left:
	{
		m_Destination.x -= 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar != L' ' && wchar != L'#' && wchar != L'A')
			m_Direction = Direction::Left;
		else
		{
			m_Direction = Direction(rand() % 4);
			m_Destination.x += 32.0f;
			CheckNextPunch(index);
		}
		break;
	}
	}
}

void Enemy::CheckPengoDirection()
{
	auto position = m_pLevelManager->GetPengo()->GetTransform()->GetPosition();

	auto enemyPos = m_pTransform->GetPosition();

	auto distance = sqrt(pow(position.x - enemyPos.x, 2) + pow(position.y - enemyPos.y, 2));

	//CLIENT_INFO("Distance to Pengo: {0}", distance);

	if (distance <= 160.0f)
	{
		auto position = m_pLevelManager->GetPengo()->GetTransform()->GetPosition();

		auto enemyPos = m_pTransform->GetPosition();

		auto horizontalDistance = abs(position.x - enemyPos.x);
		auto verticalDistance = abs(position.y - enemyPos.y);

		if (horizontalDistance >= verticalDistance)
		{
			auto horDistance = position.x - enemyPos.x;

			if (horDistance >= 0)
			{
				m_Direction = Direction::Right;
			}
			else
			{
				m_Direction = Direction::Left;
			}
		}
		else
		{
			auto vertDistance = position.y - enemyPos.y;

			if (vertDistance >= 0)
			{
				m_Direction = Direction::Down;
			}
			else
			{
				m_Direction = Direction::Up;
			}
		}
	}
}

void Enemy::UpdateStates()
{
	float elapsedSec = m_pGameTime->GetElapsedSec();

	if (m_WanderTimer > m_WanderCooldown && m_pTransform->GetPosition() == m_Destination)
	{
		m_WanderTimer = 0.0f;
		m_WanderCooldown = float(rand() % 10 + 10);
		m_State = State::PUNCHING;
	}
	if (m_PunchTimer > m_PunchCooldown && m_pTransform->GetPosition() == m_Destination)
	{
		m_PunchTimer = 0.0f;
		m_PunchCooldown = float(rand() % 5 + 5);
		m_State = State::WANDERING;
	}

	if (m_State == State::WANDERING)
	{
		m_WanderTimer += elapsedSec;
	}
	if (m_State == State::PUNCHING)
	{
		m_PunchTimer += elapsedSec;
	}

	if (m_State == State::WANDERING && m_pTransform->GetPosition() == m_Destination)
	{
		CheckNextWander(4);
	}
	if (m_State == State::PUNCHING && m_pTransform->GetPosition() == m_Destination)
	{
		CheckPengoDirection();
		CheckNextPunch(4);
	}
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
	else if (m_State == State::PUNCHING)
	{
		switch (m_Direction)
		{
		case Direction::Down:
		{
			m_pSprite->SetClipIndex(5);
			break;
		}
		case Direction::Up:
		{
			m_pSprite->SetClipIndex(8);
			break;
		}
		case Direction::Right:
		{
			m_pSprite->SetClipIndex(7);
			break;
		}
		case Direction::Left:
		{
			m_pSprite->SetClipIndex(6);
			break;
		}
		case Direction::NONE:
		{
			m_pSprite->SetClipIndex(5);
			break;
		}
		}
	}
}

void Enemy::Render()
{

}

void Enemy::OnTrigger(GameObject* gameObject)
{
	if (m_State == State::PUNCHING && gameObject->GetTag() == "Block" && m_Direction != Direction::NONE)
	{
		switch (m_Direction)
		{
		case Direction::Down:
		{
			if (gameObject->GetTransform()->GetPosition().y > GetTransform()->GetPosition().y && gameObject->GetTransform()->GetPosition().x == GetTransform()->GetPosition().x)
			{
				auto block = static_cast<Block*>(gameObject);

				if (block)
				{
					block->Break();
				}
			}

			break;
		}
		case Direction::Up:
		{
			if (gameObject->GetTransform()->GetPosition().y < GetTransform()->GetPosition().y && gameObject->GetTransform()->GetPosition().x == GetTransform()->GetPosition().x)
			{
				auto block = static_cast<Block*>(gameObject);

				if (block)
				{
					block->Break();
				}
			}

			break;
		}
		case Direction::Right:
		{
			if (gameObject->GetTransform()->GetPosition().x > GetTransform()->GetPosition().x && gameObject->GetTransform()->GetPosition().y == GetTransform()->GetPosition().y)
			{
				auto block = static_cast<Block*>(gameObject);

				if (block)
				{
					block->Break();
				}
			}

			break;
		}
		case Direction::Left:
		{
			if (gameObject->GetTransform()->GetPosition().x < GetTransform()->GetPosition().x && gameObject->GetTransform()->GetPosition().y == GetTransform()->GetPosition().y)
			{
				auto block = static_cast<Block*>(gameObject);

				if (block)
				{
					block->Break();
				}
			}

			break;
		}
		}
	}
}

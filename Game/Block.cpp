#include "Block.h"
#include "Components.h"
#include "GarbageCollector.h"

Block::Block(const glm::vec2& position)
	: m_SpawnPosition(position)
	, m_Moving(false)
	, m_Direction(Direction::NONE)
	, m_pLevelManager(LevelManager::GetInstance())
	, m_MoveSpeed(150)
	, m_Destination()
	, m_pGameTime(GameTime::GetInstance())
	, m_pTransform(GetTransform())
	, m_pSpriteComponent(nullptr)
	, m_State(State::IDLE)
	, m_Destroy(false)
{
}

Block::~Block()
{
}

void Block::Initialize()
{
	// ------------------------------- Sprite Component ------------------------------------- //

	m_pSpriteComponent = new SpriteComponent("Block.png", 2, 9, 32);

	m_pSpriteComponent->AddClip(9, false);
	m_pSpriteComponent->AddClip(1, false);

	m_pSpriteComponent->SetClipIndex(State::IDLE);

	AddComponent(m_pSpriteComponent);

	// ------------------------------- Collision Component ------------------------------------- //

	auto collisionComp = new CollisionComponent(32, 32);

	AddComponent(collisionComp);

	SetTag("Block");
	GetTransform()->Translate(m_SpawnPosition);

	m_Destination = GetTransform()->GetPosition();
}

void Block::Update()
{
	UpdateMovement();
	UpdateAnimations();

	if (m_pSpriteComponent->CheckEndOfCurrentClip() && m_Destroy == true)
	{
		GarbageCollector::GetInstance()->Destroy(this);
	}
}

void Block::UpdateMovement()
{
	if (m_Moving)
	{
		switch (m_Direction)
		{
		case Direction::Down:
			m_pTransform->Move(0, m_MoveSpeed * m_pGameTime->GetElapsedSec());

			if (m_pTransform->GetPosition().y > m_Destination.y)
			{
				m_Destination.y += 32.0f;

				auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

				if (wchar == L'#' || wchar == L'O' || wchar == L' ')
				{
					m_Destination.y -= 32.0f;
					m_pTransform->Translate(m_Destination);
					m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, 'O');
					m_Moving = false;
					m_Direction = Direction::NONE;
				}
			}
			break;
		case Direction::Up:
			m_pTransform->Move(0, -(m_MoveSpeed * m_pGameTime->GetElapsedSec()));

			if (m_pTransform->GetPosition().y < m_Destination.y)
			{
				m_Destination.y -= 32.0f;

				auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

				if (wchar == L'#' || wchar == L'O' || wchar == L' ')
				{
					m_Destination.y += 32.0f;
					m_pTransform->Translate(m_Destination);
					m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, 'O');
					m_Moving = false;
					m_Direction = Direction::NONE;
				}
			}
			break;
		case Direction::Right:
			m_pTransform->Move(m_MoveSpeed * m_pGameTime->GetElapsedSec(), 0);

			if (m_pTransform->GetPosition().x > m_Destination.x)
			{
				m_Destination.x += 32.0f;

				auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

				if (wchar == L'#' || wchar == L'O' || wchar == L' ')
				{
					m_Destination.x -= 32.0f;
					m_pTransform->Translate(m_Destination);
					m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, 'O');
					m_Moving = false;
					m_Direction = Direction::NONE;
				}
			}
			break;
		case Direction::Left:
			m_pTransform->Move(-(m_MoveSpeed * m_pGameTime->GetElapsedSec()), 0);

			if (m_pTransform->GetPosition().x < m_Destination.x)
			{
				m_Destination.x -= 32.0f;

				auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

				if (wchar == L'#' || wchar == L'O' || wchar == L' ')
				{
					m_Destination.x += 32.0f;
					m_pTransform->Translate(m_Destination);
					m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, 'O');
					m_Moving = false;
					m_Direction = Direction::NONE;
				}
			}
			break;
		}
	}
}

void Block::UpdateAnimations()
{
	switch (m_State)
	{
	case State::BRAKING:
		m_pSpriteComponent->SetClipIndex(State::BRAKING);
		break;
	case State::IDLE:
		m_pSpriteComponent->SetClipIndex(State::IDLE);
		break;
	}
}

void Block::Push(const Direction& direction)
{
	switch (direction)
	{
	case Direction::Down:
	{
		m_Destination.y += 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar == L'#' || wchar == L'O' || wchar == L' ')
		{
			m_Destroy = true;
			m_State = State::BRAKING;
			m_Destination.y -= 32.0f;
			m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, '.');
			return;
		}

		break;
	}
	case Direction::Up:
	{
		m_Destination.y -= 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar == L'#' || wchar == L'O' || wchar == L' ')
		{
			m_Destroy = true;
			m_State = State::BRAKING;
			m_Destination.y += 32.0f;
			m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, '.');
			return;
		}

		break;
	}
	case Direction::Right:
	{
		m_Destination.x += 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar == L'#' || wchar == L'O' || wchar == L' ')
		{
			m_Destroy = true;
			m_State = State::BRAKING;
			m_Destination.x -= 32.0f;
			m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, '.');
			return;
		}

		break;
	}
	case Direction::Left:
	{
		m_Destination.x -= 32.0f;

		auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

		if (wchar == L'#' || wchar == L'O' || wchar == L' ')
		{
			m_Destroy = true;
			m_State = State::BRAKING;
			m_Destination.x += 32.0f;
			m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, '.');
			return;
		}

		break;
	}
	}

	m_Moving = true;
	m_Direction = direction;

	m_pLevelManager->SetTile((int)GetTransform()->GetPosition().x / 16, (int)GetTransform()->GetPosition().y / 16, '.');
}

void Block::Render()
{
}

#include "ArrowBlock.h"

#include "SpriteComponent.h"

ArrowBlock::ArrowBlock(const glm::vec2& position)
	: m_SpawnPosition(position)
	, m_State(State::IDLE)
	, m_Direction(Direction::NONE)
	, m_Destination()
	, m_Moving(false)
	, m_MoveSpeed(150)
	, m_pLevelManager(LevelManager::GetInstance())
	, m_pGameTime(GameTime::GetInstance())
	, m_pTransform(GetTransform())
	, m_pSpriteComponent(nullptr)
{
}

ArrowBlock::~ArrowBlock()
{
}

void ArrowBlock::Initialize()
{
	// ------------------------------- Sprite Component ------------------------------------- //

	m_pSpriteComponent = new SpriteComponent("ArrowBlock.png", 1, 1, 32);

	m_pSpriteComponent->AddClip(1, false);

	m_pSpriteComponent->SetClipIndex(0);

	AddComponent(m_pSpriteComponent);

	// ------------------------------- Collision Component ------------------------------------- //

	auto collisionComp = new CollisionComponent(32, 32);

	AddComponent(collisionComp);

	SetTag("ArrowBlock");
	GetTransform()->Translate(m_SpawnPosition);

	m_Destination = m_SpawnPosition;
}

void ArrowBlock::Update()
{
	UpdateMovement();
}

void ArrowBlock::UpdateMovement()
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

				if (wchar != L'.')
				{
					m_Destination.y -= 32.0f;
					m_pTransform->Translate(m_Destination);
					m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, 'A');
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

				if (wchar != L'.')
				{
					m_Destination.y += 32.0f;
					m_pTransform->Translate(m_Destination);
					m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, 'A');
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

				if (wchar != L'.')
				{
					m_Destination.x -= 32.0f;
					m_pTransform->Translate(m_Destination);
					m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, 'A');
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

				if (wchar != L'.')
				{
					m_Destination.x += 32.0f;
					m_pTransform->Translate(m_Destination);
					m_pLevelManager->SetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16, 'A');
					m_Moving = false;
					m_Direction = Direction::NONE;
				}
			}
			break;
		}
	}
}

void ArrowBlock::Push(const Direction& direction)
{
	m_Moving = true;
	m_Direction = direction;

	m_pLevelManager->SetTile((int)GetTransform()->GetPosition().x / 16, (int)GetTransform()->GetPosition().y / 16, '.');
}

void ArrowBlock::Render()
{
}

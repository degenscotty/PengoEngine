#include "ArrowBlock.h"

#include "SpriteComponent.h"

ArrowBlock::ArrowBlock(const glm::vec2& position)
	: m_SpawnPosition(position)
	, m_State(State::IDLE)
	, m_Direction(Direction::NONE)
	, m_Destination()
	, m_Moving(false)
	, m_MoveSpeed(250)
	, m_pLevelManager(LevelManager::GetInstance())
	, m_pGameTime(GameTime::GetInstance())
	, m_pTransform(GetTransform())
	, m_pSpriteComponent(nullptr)
	, m_pSoundManager(SoundManager::GetInstance())
{
}

ArrowBlock::~ArrowBlock()
{
}

void ArrowBlock::Initialize()
{
	// ------------------------------- Sprite Component ------------------------------------- //

	m_pSpriteComponent = new SpriteComponent("ArrowBlock.png", 2, 2, 32);

	m_pSpriteComponent->AddClip(1, false);
	m_pSpriteComponent->AddClip(2, true);

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
	UpdateAnimations();
}

void ArrowBlock::UpdateAnimations()
{
	switch (m_State)
	{
	case State::FLICKER:
		m_pSpriteComponent->SetClipIndex(1);
		break;
	case State::IDLE:
		m_pSpriteComponent->SetClipIndex(0);
		break;
	}
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
	m_pSoundManager->PlaySoundByID(1, 1, 0.4f, eSoundMerge::Replay);

	m_Moving = true;
	m_Direction = direction;

	m_pLevelManager->SetTile((int)GetTransform()->GetPosition().x / 16, (int)GetTransform()->GetPosition().y / 16, '.');
}

bool ArrowBlock::GetMoving()
{
	return m_Moving;
}

const ArrowBlock::Direction& ArrowBlock::GetDirection()
{
	return m_Direction;
}

const ArrowBlock::State& ArrowBlock::GetState()
{
	return m_State;
}

void ArrowBlock::SetState(const ArrowBlock::State& state)
{
	m_State = state;
}

void ArrowBlock::Render()
{
}

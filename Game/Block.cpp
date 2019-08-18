#include "Block.h"
#include "Components.h"

Block::Block(const glm::vec2& position)
	: m_SpawnPosition(position)
	, m_Moving(false)
	, m_Direction(Direction::NONE)
	, m_pLevelManager(LevelManager::GetInstance())
	, m_MoveSpeed(150)
	, m_Destination()
	, m_pGameTime(GameTime::GetInstance())
	, m_pTransform(GetTransform())
{
}

Block::~Block()
{
}

void Block::Initialize()
{
	// ------------------------------- Sprite Component ------------------------------------- //

	auto spriteComp = new SpriteComponent("Block.png", 2, 9, 32);

	spriteComp->AddClip(9, false);
	spriteComp->AddClip(1, false);

	spriteComp->SetClipIndex(State::IDLE);

	AddComponent(spriteComp);

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

				if (wchar == L'#'|| wchar == L'O' || wchar == L' ')
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

void Block::Push(const Direction& direction)
{
	m_Moving = true;
	m_Direction = direction;

	m_pLevelManager->SetTile((int)GetTransform()->GetPosition().x / 16, (int)GetTransform()->GetPosition().y / 16, '.');
}

void Block::Render()
{
}


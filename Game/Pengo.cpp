#include "Pengo.h"
#include "Components.h"
#include "Block.h"
#include <string>

Pengo::Pengo()
	: m_pTransform(GetTransform())
	, m_Sprite(nullptr)
	, m_pInput(InputManager::GetInstance())
	, m_MoveSpeed(100.0f)
	, m_State(State::Idle)
	, m_Direction(Direction::Right)
	, m_Destination()
	, m_pGameTime(GameTime::GetInstance())
	, m_pLevelManager(LevelManager::GetInstance())
{
}

Pengo::~Pengo()
{
}

void Pengo::Initialize()
{
	// ------------------------------- Sprite Component ------------------------------------- //

	m_Sprite = new SpriteComponent("Pengo.png", 4, 2, 32);

	m_Sprite->AddClip(2, true);
	m_Sprite->AddClip(2, true);
	m_Sprite->AddClip(2, true);
	m_Sprite->AddClip(2, true);

	AddComponent(m_Sprite);

	// ------------------------------- Collision Component ------------------------------------- //

	auto collisionComp = new CollisionComponent(32.0f, 32.0f);

	AddComponent(collisionComp);

	SetTag("Pengo");
	GetTransform()->Translate(16.0f, 16.0f);

	m_Destination = GetTransform()->GetPosition();
}

void Pengo::MoveNext()
{
	switch (m_Direction)
	{
	case Direction::Down:
		if (m_pTransform->GetPosition().y + (m_MoveSpeed * m_pGameTime->GetElapsedSec()) > m_Destination.y)
		{
			m_pTransform->Translate(m_Destination);
		}
		else
		{
			m_pTransform->Move(0, m_MoveSpeed * m_pGameTime->GetElapsedSec());
			m_State = State::MoveDown;
			m_Direction = Direction::Down;
		}
		break;
	case Direction::Up:
		if (m_pTransform->GetPosition().y - (m_MoveSpeed * m_pGameTime->GetElapsedSec()) < m_Destination.y)
		{
			m_pTransform->Translate(m_Destination);
		}
		else
		{
			m_pTransform->Move(0, -(m_MoveSpeed * m_pGameTime->GetElapsedSec()));
			m_State = State::MoveUp;
			m_Direction = Direction::Up;
		}
		break;
	case Direction::Right:
		if (m_pTransform->GetPosition().x + (m_MoveSpeed * m_pGameTime->GetElapsedSec()) > m_Destination.x)
		{
			m_pTransform->Translate(m_Destination);
		}
		else
		{
			m_pTransform->Move(m_MoveSpeed * m_pGameTime->GetElapsedSec(), 0);
			m_State = State::MoveRight;
			m_Direction = Direction::Right;
		}
		break;
	case Direction::Left:
		if (m_pTransform->GetPosition().x - (m_MoveSpeed * m_pGameTime->GetElapsedSec()) < m_Destination.x)
		{
			m_pTransform->Translate(m_Destination);
		}
		else
		{
			m_pTransform->Move(-(m_MoveSpeed * m_pGameTime->GetElapsedSec()), 0);
			m_State = State::MoveLeft;
			m_Direction = Direction::Left;
		}
		break;
	}

}

void Pengo::Update()
{
	UpdateMovement();
	UpdateAnimations();
}

void Pengo::UpdateMovement()
{
	if (m_pInput->IsKeyPressed(KEY_DOWN))
	{
		if (m_pTransform->GetPosition() == m_Destination || m_Direction == Direction::Up || m_Direction == Direction::Down)
		{
			m_pTransform->Move(0, m_MoveSpeed * m_pGameTime->GetElapsedSec());
			m_State = State::MoveDown;
			m_Direction = Direction::Down;

			if (m_pTransform->GetPosition().y > m_Destination.y)
			{
				m_Destination.y += 32.0f;

				auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

				if (wchar == L'#' || wchar == L'O' || wchar == L' ')
				{
					m_Destination.y -= 32.0f;
					m_pTransform->Translate(m_Destination);
				}
			}
		}
		else if (m_Direction == Direction::Left || m_Direction == Direction::Right)
		{
			MoveNext();
		}
	}
	else if (m_pInput->IsKeyPressed(KEY_UP))
	{
		if (m_pTransform->GetPosition() == m_Destination || m_Direction == Direction::Up || m_Direction == Direction::Down)
		{
			m_pTransform->Move(0, -(m_MoveSpeed * m_pGameTime->GetElapsedSec()));
			m_State = State::MoveUp;
			m_Direction = Direction::Up;

			if (m_pTransform->GetPosition().y < m_Destination.y)
			{
				m_Destination.y -= 32.0f;

				auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

				if (wchar == L'#' || wchar == L'O' || wchar == L' ')
				{
					m_Destination.y += 32.0f;
					m_pTransform->Translate(m_Destination);
				}
			}
		}
		else if (m_Direction == Direction::Left || m_Direction == Direction::Right)
		{
			MoveNext();
		}
	}
	else if (m_pInput->IsKeyPressed(KEY_RIGHT))
	{
		if (m_pTransform->GetPosition() == m_Destination || m_Direction == Direction::Left || m_Direction == Direction::Right)
		{
			m_pTransform->Move(m_MoveSpeed * m_pGameTime->GetElapsedSec(), 0);
			m_State = State::MoveRight;
			m_Direction = Direction::Right;

			if (m_pTransform->GetPosition().x > m_Destination.x)
			{
				m_Destination.x += 32.0f;

				auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

				if (wchar == L'#' || wchar == L'O' || wchar == L' ')
				{
					m_Destination.x -= 32.0f;
					m_pTransform->Translate(m_Destination);
				}
			}
		}
		else if (m_Direction == Direction::Up || m_Direction == Direction::Down)
		{
			MoveNext();
		}
	}
	else if (m_pInput->IsKeyPressed(KEY_LEFT))
	{
		if (m_pTransform->GetPosition() == m_Destination || m_Direction == Direction::Left || m_Direction == Direction::Right)
		{
			m_pTransform->Move(-(m_MoveSpeed * m_pGameTime->GetElapsedSec()), 0);
			m_State = State::MoveLeft;
			m_Direction = Direction::Left;

			if (m_pTransform->GetPosition().x < m_Destination.x)
			{
				m_Destination.x -= 32.0f;

				auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);

				if (wchar == L'#' || wchar == L'O' || wchar == L' ')
				{
					m_Destination.x += 32.0f;
					m_pTransform->Translate(m_Destination);
				}
			}
		}
		else if (m_Direction == Direction::Up || m_Direction == Direction::Down)
		{
			MoveNext();
		}
	}
	else
	{
		m_State = State::Idle;
	}
}

void Pengo::UpdateAnimations()
{
	switch (m_State)
	{
	case State::Idle:
		m_Sprite->SetClipIndex(State::MoveDown);
		break;
	case State::MoveDown:
		m_Sprite->SetClipIndex(State::MoveDown);
		break;
	case State::MoveUp:
		m_Sprite->SetClipIndex(State::MoveUp);
		break;
	case State::MoveRight:
		m_Sprite->SetClipIndex(State::MoveRight);
		break;
	case State::MoveLeft:
		m_Sprite->SetClipIndex(State::MoveLeft);
		break;
	}
}

void Pengo::Render()
{
}

void Pengo::OnTrigger(GameObject* gameObject)
{
	if (m_pInput->IsKeyPressed(KEY_SPACE) && gameObject->GetTag() == "Block" && m_State != State::Idle)
	{
		switch (m_Direction)
		{
		case Direction::Down:
		{
			m_Destination.y += 32.0f;

			auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);
			if (wchar == L'O' && gameObject->GetTransform()->GetPosition().y > GetTransform()->GetPosition().y && gameObject->GetTransform()->GetPosition().x == GetTransform()->GetPosition().x)
			{
				auto block = static_cast<Block*>(gameObject);

				if (block)
				{
					block->Push(Block::Down);
				}
			}

			m_Destination.y -= 32.0f;
			break;
		}
		case Direction::Up:
		{
			m_Destination.y -= 32.0f;

			auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);
			if (wchar == L'O' && gameObject->GetTransform()->GetPosition().y < GetTransform()->GetPosition().y && gameObject->GetTransform()->GetPosition().x == GetTransform()->GetPosition().x)
			{
				auto block = static_cast<Block*>(gameObject);

				if (block)
				{
					block->Push(Block::Up);
				}
			}

			m_Destination.y += 32.0f;
			break;
		}
		case Direction::Right:
		{
			m_Destination.x += 32.0f;

			auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);
			if (wchar == L'O' && gameObject->GetTransform()->GetPosition().x > GetTransform()->GetPosition().x && gameObject->GetTransform()->GetPosition().y == GetTransform()->GetPosition().y)
			{
				auto block = static_cast<Block*>(gameObject);

				if (block)
				{
					block->Push(Block::Right);
				}
			}

			m_Destination.x -= 32.0f;
			break;
		}
		case Direction::Left:
		{
			m_Destination.x -= 32.0f;

			auto wchar = m_pLevelManager->GetTile((int)m_Destination.x / 16, (int)m_Destination.y / 16);
			if (wchar == L'O' && gameObject->GetTransform()->GetPosition().x < GetTransform()->GetPosition().x && gameObject->GetTransform()->GetPosition().y == GetTransform()->GetPosition().y)
			{
				auto block = static_cast<Block*>(gameObject);

				if (block)
				{
					block->Push(Block::Left);
				}
			}

			m_Destination.x += 32.0f;
			break;
		}
		}
	}
}

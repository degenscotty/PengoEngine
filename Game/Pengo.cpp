#include "Pengo.h"

Pengo::Pengo()
	: m_pTransform(GetTransform())
	, m_Sprite(nullptr)
	, m_pInput(InputManager::GetInstance())
	, m_MoveSpeed(100.0f)
	, m_State(State::Idle)
	, m_Direction(Direction::Right)
	, m_Destination()
	, m_pGameTime(GameTime::GetInstance())
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

	m_Destination = GetTransform()->GetWorldPosition();

	AddComponent(m_Sprite);
}

void Pengo::MoveNext()
{
	switch (m_Direction)
	{
	case Direction::Down:
		if (m_pTransform->GetWorldPosition().y + (m_MoveSpeed * m_pGameTime->GetElapsedSec()) > m_Destination.y)
		{
			m_pTransform->TranslateWorld(m_Destination);
		}
		else
		{
			m_pTransform->MoveWorld(0, m_MoveSpeed * m_pGameTime->GetElapsedSec());
			m_State = State::MoveDown;
			m_Direction = Direction::Down;
		}
		break;
	case Direction::Up:
		if (m_pTransform->GetWorldPosition().y - (m_MoveSpeed * m_pGameTime->GetElapsedSec()) < m_Destination.y)
		{
			m_pTransform->TranslateWorld(m_Destination);
		}
		else
		{
			m_pTransform->MoveWorld(0, -(m_MoveSpeed * m_pGameTime->GetElapsedSec()));
			m_State = State::MoveUp;
			m_Direction = Direction::Up;
		}
		break;
	case Direction::Right:
		if (m_pTransform->GetWorldPosition().x + (m_MoveSpeed * m_pGameTime->GetElapsedSec()) > m_Destination.x)
		{
			m_pTransform->TranslateWorld(m_Destination);
		}
		else
		{
			m_pTransform->MoveWorld(m_MoveSpeed * m_pGameTime->GetElapsedSec(), 0);
			m_State = State::MoveRight;
			m_Direction = Direction::Right;
		}
		break;
	case Direction::Left:
		if (m_pTransform->GetWorldPosition().x - (m_MoveSpeed * m_pGameTime->GetElapsedSec()) < m_Destination.x)
		{
			m_pTransform->TranslateWorld(m_Destination);
		}
		else
		{
			m_pTransform->MoveWorld(-(m_MoveSpeed * m_pGameTime->GetElapsedSec()), 0);
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
	if (m_pInput->IsKeyPressed(KEY_UP))
	{
		if (m_pTransform->GetWorldPosition() == m_Destination ||m_Direction == Direction::Up || m_Direction == Direction::Down)
		{
			m_pTransform->MoveWorld(0, -(m_MoveSpeed * m_pGameTime->GetElapsedSec()));
			m_State = State::MoveUp;
			m_Direction = Direction::Up;

			if (m_pTransform->GetWorldPosition().y < m_Destination.y)
			{
				m_Destination.y -= 32.0f;
			}
		}
		else if (m_Direction == Direction::Left || m_Direction == Direction::Right)
		{
			MoveNext();
		}
	}
	else if (m_pInput->IsKeyPressed(KEY_DOWN))
	{
		if (m_pTransform->GetWorldPosition() == m_Destination || m_Direction == Direction::Up || m_Direction == Direction::Down)
		{
			m_pTransform->MoveWorld(0, m_MoveSpeed * m_pGameTime->GetElapsedSec());
			m_State = State::MoveDown;
			m_Direction = Direction::Down;

			if (m_pTransform->GetWorldPosition().y > m_Destination.y)
			{
				m_Destination.y += 32.0f;
			}
		}
		else if (m_Direction == Direction::Left || m_Direction == Direction::Right)
		{
			MoveNext();
		}
	}
	else if (m_pInput->IsKeyPressed(KEY_RIGHT))
	{
		if (m_pTransform->GetWorldPosition() == m_Destination || m_Direction == Direction::Left || m_Direction == Direction::Right)
		{
			m_pTransform->MoveWorld(m_MoveSpeed * m_pGameTime->GetElapsedSec(), 0);
			m_State = State::MoveRight;
			m_Direction = Direction::Right;

			if (m_pTransform->GetWorldPosition().x > m_Destination.x)
			{
				m_Destination.x += 32.0f;
			}
		}
		else if (m_Direction == Direction::Up || m_Direction == Direction::Down)
		{
			MoveNext();
		}
	}
	else if (m_pInput->IsKeyPressed(KEY_LEFT))
	{
		if (m_pTransform->GetWorldPosition() == m_Destination || m_Direction == Direction::Left || m_Direction == Direction::Right)
		{
			m_pTransform->MoveWorld(-(m_MoveSpeed * m_pGameTime->GetElapsedSec()), 0);
			m_State = State::MoveLeft;
			m_Direction = Direction::Left;

			if (m_pTransform->GetWorldPosition().x < m_Destination.x)
			{
				m_Destination.x -= 32.0f;
			}
		}
		else if (m_Direction == Direction::Up || m_Direction == Direction::Down)
		{
			MoveNext();
		}
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

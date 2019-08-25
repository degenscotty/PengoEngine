#include "Wall.h"
#include "Components.h"

Wall::Wall(const glm::vec2& position)
	: m_SpawnPosition(position)
	, m_State(State::IDLE)
	, m_Wiggle(false)
	, m_pLevelManager(LevelManager::GetInstance())
	, m_Direction(Direction::NONE)
	, m_pTransform(GetTransform())
	, m_pSpriteComponent(nullptr)
	, m_WiggleAvailable(true)
	, m_WiggleTimer(0.0f)
	, m_pGameTime(GameTime::GetInstance())
	, m_FlashTimer(0.0f)
	, m_FlashAvailable(true)
{
}

Wall::~Wall()
{
}

void Wall::Initialize()
{
	// ------------------------------- Sprite Component ------------------------------------- //

	m_pSpriteComponent = new SpriteComponent("Wall.png", 3, 6, 16);

	m_pSpriteComponent->AddClip(6, false);
	m_pSpriteComponent->AddClip(1, false);
	m_pSpriteComponent->AddClip(6, true);

	m_pSpriteComponent->SetClipIndex(1);

	AddComponent(m_pSpriteComponent);

	// ---------------------------- Collision Component ------------------------------------- //

	auto collisionComp = new CollisionComponent(16, 16);

	AddComponent(collisionComp);

	SetTag("Wall");
	GetTransform()->Translate(m_SpawnPosition);
}

void Wall::Update()
{
	if (m_State == State::FLASHING)
	{
		m_FlashTimer += m_pGameTime->GetElapsedSec();

		if (m_FlashTimer > 5.0f)
		{
			m_State = State::IDLE;
		}
	}

	if (!m_WiggleAvailable)
	{
		m_WiggleTimer += m_pGameTime->GetElapsedSec();

		if (m_WiggleTimer > 1.2f)
		{
			m_WiggleAvailable = true;
			m_WiggleTimer = 0.0f;
		}
	}

	if (m_Wiggle && m_pSpriteComponent->CheckEndOfCurrentClip())
	{
		m_Wiggle = false;
		m_State = State::IDLE;
		m_Direction = Direction::NONE;
	}

	UpdateAnimations();
}

void Wall::TriggerBonus()
{
	if (m_FlashAvailable)
	{
		m_State = State::FLASHING;
		m_FlashAvailable = false;
	}
}

void Wall::TriggerWiggle(const Wall::Direction& direction)
{
	if (m_WiggleAvailable)
	{
		m_Wiggle = true;
		m_State = State::WIGGLE;
		m_Direction = direction;
		m_pSpriteComponent->SetClipIndex(State::WIGGLE);
		m_WiggleAvailable = false;
	}
}

void Wall::UpdateAnimations()
{
	switch (m_State)
	{
	case State::IDLE:
	{
		m_pSpriteComponent->SetClipIndex(1);
	}
	break;
	case State::WIGGLE:
	{
		m_pSpriteComponent->SetClipIndex(0);
	}
	break;
	case State::FLASHING:
	{
		m_pSpriteComponent->SetClipIndex(2);
	}
	break;
	}
}

bool Wall::GetWiggle()
{
	return m_Wiggle;
}

void Wall::Render()
{
}

const Wall::Direction& Wall::GetDirection()
{
	return m_Direction;
}

void Wall::OnTrigger(GameObject* gameObject)
{
	if (gameObject->GetTag() == "Wall" && m_Wiggle)
	{
		auto wall = dynamic_cast<Wall*>(gameObject);

		if (wall)
		{
			if (!wall->GetWiggle())
			{
				if (m_Direction == Wall::Down || m_Direction == Wall::Up)
				{
					if (m_pTransform->GetPosition().y == wall->GetTransform()->GetPosition().y)
					{
						wall->TriggerWiggle(m_Direction);
					}
				}
				else if (m_Direction == Wall::Left || m_Direction == Wall::Right)
				{
					if (m_pTransform->GetPosition().x == wall->GetTransform()->GetPosition().x)
					{
						wall->TriggerWiggle(m_Direction);
					}
				}
			}
		}
	}
}

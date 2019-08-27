#include "Pengo.h"
#include "Components.h"
#include "Block.h"
#include "ArrowBlock.h"
#include "SceneManager.h"
#include "GarbageCollector.h"
#include "ResourceManager.h"
#include "PopUpManager.h"
#include "Wall.h"
#include "Enemy.h"
#include "utils.h"
#include "Texture2D.h"
#include <string>

Pengo::Pengo()
	: m_pTransform(GetTransform())
	, m_pSpriteComponent(nullptr)
	, m_pSoundManager(SoundManager::GetInstance())
	, m_pInput(InputManager::GetInstance())
	, m_MoveSpeed(100.0f)
	, m_State(State::Idle)
	, m_Direction(Direction::Right)
	, m_Destination()
	, m_pGameTime(GameTime::GetInstance())
	, m_pLevelManager(LevelManager::GetInstance())
	, m_Push(false)
	, m_PushAvailable(true)
	, m_PushTimer(0.0f)
	, m_Lives(5)
	, m_Invincible(false)
	, m_InvincibleTimer(0.0f)
	, m_pRenderer(Renderer::GetInstance())
	, m_pPengoLife(nullptr)
{
}

Pengo::~Pengo()
{
}

void Pengo::Initialize()
{
	// ------------------------------- Sprite Component ------------------------------------- //

	m_pSpriteComponent = new SpriteComponent("Pengo.png", 8, 2, 32);

	m_pSpriteComponent->AddClip(2, true);
	m_pSpriteComponent->AddClip(2, true);
	m_pSpriteComponent->AddClip(2, true);
	m_pSpriteComponent->AddClip(2, true);

	m_pSpriteComponent->AddClip(2, false);
	m_pSpriteComponent->AddClip(2, false);
	m_pSpriteComponent->AddClip(2, false);
	m_pSpriteComponent->AddClip(2, false);


	AddComponent(m_pSpriteComponent);

	m_pPengoLife = ResourceManager::GetInstance()->LoadTexture("PengoLife.png");

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
	if (m_Invincible)
	{
		m_InvincibleTimer += m_pGameTime->GetElapsedSec();

		if (m_InvincibleTimer > 3.0f)
		{
			m_Invincible = false;
			m_InvincibleTimer = 0.0f;
		}
	}

	if (m_Lives < 1)
	{
		GarbageCollector::GetInstance()->Destroy(SceneManager::GetInstance()->GetActiveScene());
		SceneManager::GetInstance()->SetActiveScene(L"GameOver");
	}

	if (!m_PushAvailable)
	{
		m_PushTimer += m_pGameTime->GetElapsedSec();

		if (m_PushTimer > 0.6f)
		{
			m_PushAvailable = true;
			m_PushTimer = 0.0f;
		}
	}

	if (m_Push)
	{
		if (m_pSpriteComponent->CheckEndOfCurrentClip())
		{
			m_Push = false;
		}
	}
	else
	{
		UpdateMovement();
		UpdateAnimations();
	}
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

				if (wchar != L'.')
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

				if (wchar != L'.')
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

				if (wchar != L'.')
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

				if (wchar != L'.')
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
		m_pSpriteComponent->SetClipIndex(State::MoveDown);
		break;
	case State::MoveDown:
		m_pSpriteComponent->SetClipIndex(State::MoveDown);
		break;
	case State::MoveUp:
		m_pSpriteComponent->SetClipIndex(State::MoveUp);
		break;
	case State::MoveRight:
		m_pSpriteComponent->SetClipIndex(State::MoveRight);
		break;
	case State::MoveLeft:
		m_pSpriteComponent->SetClipIndex(State::MoveLeft);
		break;
	}
}

void Pengo::Respawn()
{
	m_State = State::Idle;
	m_Direction = Direction::Right;
	m_pTransform->Translate(16.0f, 16.0f);
	m_Destination = { 16.0f, 16.0f };
	m_Push = false;
	m_PushAvailable = true;
}

void Pengo::Render()
{
	for (int i{ 0 }; i < m_Lives; ++i)
	{
		m_pRenderer->RenderTexture(m_pPengoLife->GetSDLTexture(), 4 + int(i * 2.0f) + int(i * 24.0f), 516);
	}
}

void Pengo::OnTrigger(GameObject* gameObject)
{
	if (!m_Push && m_PushAvailable && m_pInput->IsKeyPressed(KEY_SPACE) && (gameObject->GetTag() == "Block" || gameObject->GetTag() == "ArrowBlock") && m_State != State::Idle)
	{
		auto block = dynamic_cast<Block*>(gameObject);
		auto arrowBlock = dynamic_cast<ArrowBlock*>(gameObject);

		if (block && block->GetState() == Block::BRAKING)
			return;

		switch (m_Direction)
		{
		case Direction::Down:
		{
			m_Destination.y += 32.0f;

			if (gameObject->GetTransform()->GetPosition().y > GetTransform()->GetPosition().y && gameObject->GetTransform()->GetPosition().x == GetTransform()->GetPosition().x)
			{
				if (gameObject->GetTag() == "Block")
				{
					auto block = dynamic_cast<Block*>(gameObject);

					if (block)
					{
						block->Push(Block::Down);
						m_State = State::PushDown;
						m_pSpriteComponent->SetClipIndex(State::PushDown);
						m_Push = true;
						m_PushAvailable = false;
					}
				}
				else
				{
					auto arrowBlock = dynamic_cast<ArrowBlock*>(gameObject);

					if (arrowBlock)
					{
						arrowBlock->Push(ArrowBlock::Down);
						m_State = State::PushDown;
						m_pSpriteComponent->SetClipIndex(State::PushDown);
						m_Push = true;
						m_PushAvailable = false;
					}
				}
			}

			m_Destination.y -= 32.0f;
			break;
		}
		case Direction::Up:
		{
			m_Destination.y -= 32.0f;

			if (gameObject->GetTransform()->GetPosition().y < GetTransform()->GetPosition().y && gameObject->GetTransform()->GetPosition().x == GetTransform()->GetPosition().x)
			{
				if (gameObject->GetTag() == "Block")
				{
					auto block = dynamic_cast<Block*>(gameObject);

					if (block)
					{
						block->Push(Block::Up);
						m_State = State::PushUp;
						m_pSpriteComponent->SetClipIndex(State::PushUp);
						m_Push = true;
						m_PushAvailable = false;
					}
				}
				else
				{
					auto arrowBlock = dynamic_cast<ArrowBlock*>(gameObject);

					if (arrowBlock)
					{
						arrowBlock->Push(ArrowBlock::Up);
						m_State = State::PushUp;
						m_pSpriteComponent->SetClipIndex(State::PushUp);
						m_Push = true;
						m_PushAvailable = false;
					}
				}
			}

			m_Destination.y += 32.0f;
			break;
		}
		case Direction::Right:
		{
			m_Destination.x += 32.0f;

			if (gameObject->GetTransform()->GetPosition().x > GetTransform()->GetPosition().x && gameObject->GetTransform()->GetPosition().y == GetTransform()->GetPosition().y)
			{
				if (gameObject->GetTag() == "Block")
				{
					auto block = dynamic_cast<Block*>(gameObject);

					if (block)
					{
						block->Push(Block::Right);
						m_State = State::PushRight;
						m_pSpriteComponent->SetClipIndex(State::PushRight);
						m_Push = true;
						m_PushAvailable = false;
					}
				}
				else
				{
					auto arrowBlock = dynamic_cast<ArrowBlock*>(gameObject);

					if (arrowBlock)
					{
						arrowBlock->Push(ArrowBlock::Right);
						m_State = State::PushRight;
						m_pSpriteComponent->SetClipIndex(State::PushRight);
						m_Push = true;
						m_PushAvailable = false;
					}
				}
			}

			m_Destination.x -= 32.0f;
			break;
		}
		case Direction::Left:
		{
			m_Destination.x -= 32.0f;

			if (gameObject->GetTransform()->GetPosition().x < GetTransform()->GetPosition().x && gameObject->GetTransform()->GetPosition().y == GetTransform()->GetPosition().y)
			{
				if (gameObject->GetTag() == "Block")
				{
					auto block = dynamic_cast<Block*>(gameObject);

					if (block)
					{
						block->Push(Block::Left);
						m_State = State::PushLeft;
						m_pSpriteComponent->SetClipIndex(State::PushLeft);
						m_Push = true;
						m_PushAvailable = false;
					}
				}
				else
				{
					auto arrowBlock = dynamic_cast<ArrowBlock*>(gameObject);

					if (arrowBlock)
					{
						arrowBlock->Push(ArrowBlock::Left);
						m_State = State::PushLeft;
						m_pSpriteComponent->SetClipIndex(State::PushLeft);
						m_Push = true;
						m_PushAvailable = false;
					}
				}
			}

			m_Destination.x += 32.0f;
			break;
		}
		}
	}

	if (!m_Push && m_PushAvailable && m_pInput->IsKeyPressed(KEY_SPACE) && gameObject->GetTag() == "Wall")
	{
		auto wall = dynamic_cast<Wall*>(gameObject);

		if (wall->GetWiggle())
			return;

		switch (m_Direction)
		{
		case Direction::Down:
		{
			if (gameObject->GetTransform()->GetPosition().y > 495.0f)
			{
				if (wall)
				{
					wall->TriggerWiggle(Wall::Down);
					m_State = State::PushDown;
					m_pSpriteComponent->SetClipIndex(State::PushDown);
					m_Push = true;
					m_PushAvailable = false;
				}
			}
		}
		break;
		case Direction::Up:
		{
			if (gameObject->GetTransform()->GetPosition().y < 5.0f)
			{
				if (wall)
				{
					wall->TriggerWiggle(Wall::Up);
					m_State = State::PushUp;
					m_pSpriteComponent->SetClipIndex(State::PushUp);
					m_Push = true;
					m_PushAvailable = false;
				}
			}
		}
		break;
		case Direction::Right:
		{
			if (gameObject->GetTransform()->GetPosition().x > 431.0f)
			{
				if (wall)
				{
					wall->TriggerWiggle(Wall::Right);
					m_State = State::PushRight;
					m_pSpriteComponent->SetClipIndex(State::PushRight);
					m_Push = true;
					m_PushAvailable = false;
				}
			}
		}
		break;
		case Direction::Left:
		{
			if (gameObject->GetTransform()->GetPosition().x < 5.0f)
			{
				if (wall)
				{
					wall->TriggerWiggle(Wall::Left);
					m_State = State::PushLeft;
					m_pSpriteComponent->SetClipIndex(State::PushLeft);
					m_Push = true;
					m_PushAvailable = false;
				}
			}
		}
		break;
		}
	}

	if (gameObject->GetTag() == "Enemy")
	{
		auto enemy = dynamic_cast<Enemy*>(gameObject);

		if (enemy->CheckDizzle())
		{
			GarbageCollector::GetInstance()->Destroy(enemy);
			m_pLevelManager->EnemyDead();
			ScoreManager::GetInstance()->AddScore(100);
			PopUpManager::GetInstance()->AddPopUp("100", enemy->GetTransform()->GetPosition());
			return;
		}

		if (!m_Invincible)
		{
			if (utils::IsOverlapping({ enemy->GetTransform()->GetPosition().x
				, enemy->GetTransform()->GetPosition().y, 32.0f, 32.0f }
				, { m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, 32.0f, 32.0f }))
			{
				m_Lives -= 1;

				m_Invincible = true;

				if (m_Lives > 0)
					Respawn();
			}
		}
	}
}

#include "Enemy.h"
#include "Components.h"
#include "Block.h"
#include "ArrowBlock.h"
#include "GarbageCollector.h"
#include "Pengo.h"
#include "Wall.h"
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
	, m_State(State::SPAWNING)
	, m_Direction(Direction::NONE)
	, m_SpawnPosition(position)
	, m_WanderTimer(0.0f)
	, m_PunchTimer(0.0f)
	, m_SpawnTimer(0.0f)
	, m_PunchCooldown(float(rand() % 5 + 5))
	, m_WanderCooldown(float(rand() % 10 + 10))
	, m_StickToBlock(false)
	, m_pStickBlock(nullptr)
	, m_DizzleTimer(0.0f)
	, m_Dizzle(false)
	, m_pScoreManager(ScoreManager::GetInstance())
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	srand(unsigned int(time(NULL)));

	// ------------------------------------------- Sprite Component ------------------------------------------ //

	m_pSprite = new SpriteComponent("SnoBee.png", 14, 7, 32);
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

	m_pSprite->AddClip(2, true);

	m_pSprite->SetClipIndex(0);

	AddComponent(m_pSprite);

	// ------------------------------- Collision Component ------------------------------------- //

	auto collisionComp = new CollisionComponent(32.0f, 32.0f);

	AddComponent(collisionComp);

	GetTransform()->Translate(m_SpawnPosition);

	m_Destination = m_SpawnPosition;
}

void Enemy::Update()
{
	srand(unsigned int(time(NULL)));

	if (m_State == State::SPAWNING)
	{
		if (m_pSprite->CheckEndOfCurrentClip())
		{
			m_State = State::WANDERING;
			m_Direction = Direction(rand() % 4);
		}
		return;
	}

	if (m_Dizzle)
	{
		m_DizzleTimer += m_pGameTime->GetElapsedSec();

		if (m_DizzleTimer > 2.0f)
		{
			m_Dizzle = false;
			m_DizzleTimer = 0.0f;
			m_State = State::WANDERING;
		}

		UpdateAnimations();

		return;
	}

	if (!m_StickToBlock)
	{
		UpdateStates();
		UpdateMovement();
		UpdateAnimations();
	}
	else
	{
		FollowStickBlock();
		UpdateAnimations();
	}
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
		m_PunchTimer = 0.0f;
		m_WanderCooldown = float(rand() % 10 + 10);
		m_State = State::PUNCHING;
	}
	if (m_PunchTimer > m_PunchCooldown && m_pTransform->GetPosition() == m_Destination)
	{
		m_PunchTimer = 0.0f;
		m_WanderTimer = 0.0f;
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
	else if (m_State == State::STICKING)
	{
		switch (m_Direction)
		{
		case Direction::Down:
		{
			m_pSprite->SetClipIndex(9);
			break;
		}
		case Direction::Up:
		{
			m_pSprite->SetClipIndex(12);
			break;
		}
		case Direction::Right:
		{
			m_pSprite->SetClipIndex(11);
			break;
		}
		case Direction::Left:
		{
			m_pSprite->SetClipIndex(10);
			break;
		}
		case Direction::NONE:
		{
			m_pSprite->SetClipIndex(9);
			break;
		}
		}
	}
	else if (m_State == DIZZLING)
	{
		m_pSprite->SetClipIndex(13);
	}
}

void Enemy::FollowStickBlock()
{
	if (m_pStickBlock)
	{
		auto block = dynamic_cast<Block*>(m_pStickBlock);
		auto arrowBlock = dynamic_cast<ArrowBlock*>(m_pStickBlock);

		if (block)
		{
			if (!block->GetMoving())
			{
				GarbageCollector::GetInstance()->Destroy(this);
				m_pScoreManager->AddScore(400);
				return;
			}

			switch (block->GetDirection())
			{
			case Block::Down:
			{
				m_pTransform->Translate(block->GetTransform()->GetPosition().x, block->GetTransform()->GetPosition().y + 32.0f);
				m_State = State::STICKING;
				m_Direction = Direction::Down;
			}
			break;
			case Block::Up:
			{
				m_pTransform->Translate(block->GetTransform()->GetPosition().x, block->GetTransform()->GetPosition().y - 32.0f);
				m_State = State::STICKING;
				m_Direction = Direction::Up;
			}
			break;
			case Block::Right:
			{
				m_pTransform->Translate(block->GetTransform()->GetPosition().x + 32.0f, block->GetTransform()->GetPosition().y);
				m_State = State::STICKING;
				m_Direction = Direction::Right;
			}
			break;
			case Block::Left:
			{
				m_pTransform->Translate(block->GetTransform()->GetPosition().x - 32.0f, block->GetTransform()->GetPosition().y);
				m_State = State::STICKING;
				m_Direction = Direction::Left;
			}
			break;
			}
		}
		else if (arrowBlock)
		{
			if (!arrowBlock->GetMoving())
			{
				GarbageCollector::GetInstance()->Destroy(this);
				m_pScoreManager->AddScore(400);
				return;
			}

			switch (arrowBlock->GetDirection())
			{
			case ArrowBlock::Down:
			{
				m_pTransform->Translate(arrowBlock->GetTransform()->GetPosition().x, arrowBlock->GetTransform()->GetPosition().y + 32.0f);
				m_State = State::STICKING;
				m_Direction = Direction::Down;
			}
			break;
			case ArrowBlock::Up:
			{
				m_pTransform->Translate(arrowBlock->GetTransform()->GetPosition().x, arrowBlock->GetTransform()->GetPosition().y - 32.0f);
				m_State = State::STICKING;
				m_Direction = Direction::Up;
			}
			break;
			case ArrowBlock::Right:
			{
				m_pTransform->Translate(arrowBlock->GetTransform()->GetPosition().x + 32.0f, arrowBlock->GetTransform()->GetPosition().y);
				m_State = State::STICKING;
				m_Direction = Direction::Right;
			}
			break;
			case ArrowBlock::Left:
			{
				m_pTransform->Translate(arrowBlock->GetTransform()->GetPosition().x - 32.0f, arrowBlock->GetTransform()->GetPosition().y);
				m_State = State::STICKING;
				m_Direction = Direction::Left;
			}
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
	if ((gameObject->GetTag() == "Block" || gameObject->GetTag() == "ArrowBlock") && !m_StickToBlock)
	{
		auto block = dynamic_cast<Block*>(gameObject);
		auto arrowBlock = dynamic_cast<ArrowBlock*>(gameObject);

		if (block && block->GetMoving() && gameObject->GetTag() == "Block")
		{
			switch (block->GetDirection())
			{
			case Block::Down:
			{
				if (m_pTransform->GetPosition().y > block->GetTransform()->GetPosition().y
					&& m_pTransform->GetPosition().x > block->GetTransform()->GetPosition().x - 32.0f
					&& m_pTransform->GetPosition().x < block->GetTransform()->GetPosition().x + 32.0f)
				{
					m_State = State::STICKING;
					m_pStickBlock = gameObject;
					m_StickToBlock = true;
					m_Dizzle = false;
				}
			}
			break;
			case Block::Up:
			{
				if (m_pTransform->GetPosition().y < block->GetTransform()->GetPosition().y
					&& m_pTransform->GetPosition().x > block->GetTransform()->GetPosition().x - 32.0f
					&& m_pTransform->GetPosition().x < block->GetTransform()->GetPosition().x + 32.0f)
				{
					m_State = State::STICKING;
					m_pStickBlock = gameObject;
					m_StickToBlock = true;
					m_Dizzle = false;
				}
			}
			break;
			case Block::Right:
			{
				if (m_pTransform->GetPosition().x > block->GetTransform()->GetPosition().x
					&& m_pTransform->GetPosition().y > block->GetTransform()->GetPosition().y - 32.0f
					&& m_pTransform->GetPosition().y < block->GetTransform()->GetPosition().y + 32.0f)
				{
					m_State = State::STICKING;
					m_pStickBlock = gameObject;
					m_StickToBlock = true;
					m_Dizzle = false;
				}
			}
			break;
			case Block::Left:
			{
				if (m_pTransform->GetPosition().x < block->GetTransform()->GetPosition().x
					&& m_pTransform->GetPosition().y > block->GetTransform()->GetPosition().y - 32.0f
					&& m_pTransform->GetPosition().y < block->GetTransform()->GetPosition().y + 32.0f)
				{
					m_State = State::STICKING;
					m_pStickBlock = gameObject;
					m_StickToBlock = true;
					m_Dizzle = false;
				}
			}
			break;
			}
		}
		if (arrowBlock && arrowBlock->GetMoving() && gameObject->GetTag() == "ArrowBlock")
		{
			switch (arrowBlock->GetDirection())
			{
			case ArrowBlock::Down:
			{
				if (m_pTransform->GetPosition().y > arrowBlock->GetTransform()->GetPosition().y
					&& m_pTransform->GetPosition().x > arrowBlock->GetTransform()->GetPosition().x - 32.0f
					&& m_pTransform->GetPosition().x < arrowBlock->GetTransform()->GetPosition().x + 32.0f)
				{
					m_State = State::STICKING;
					m_pStickBlock = gameObject;
					m_StickToBlock = true;
					m_Dizzle = false;
				}
			}
			break;
			case ArrowBlock::Up:
			{
				if (m_pTransform->GetPosition().y < arrowBlock->GetTransform()->GetPosition().y
					&& m_pTransform->GetPosition().x > arrowBlock->GetTransform()->GetPosition().x - 32.0f
					&& m_pTransform->GetPosition().x < arrowBlock->GetTransform()->GetPosition().x + 32.0f)
				{
					m_State = State::STICKING;
					m_pStickBlock = gameObject;
					m_StickToBlock = true;
					m_Dizzle = false;
				}
			}
			break;
			case ArrowBlock::Right:
			{
				if (m_pTransform->GetPosition().x > arrowBlock->GetTransform()->GetPosition().x
					&& m_pTransform->GetPosition().y > arrowBlock->GetTransform()->GetPosition().y - 32.0f
					&& m_pTransform->GetPosition().y < arrowBlock->GetTransform()->GetPosition().y + 32.0f)
				{
					m_State = State::STICKING;
					m_pStickBlock = gameObject;
					m_StickToBlock = true;
					m_Dizzle = false;
				}
			}
			break;
			case ArrowBlock::Left:
			{
				if (m_pTransform->GetPosition().x < arrowBlock->GetTransform()->GetPosition().x
					&& m_pTransform->GetPosition().y > arrowBlock->GetTransform()->GetPosition().y - 32.0f
					&& m_pTransform->GetPosition().y < arrowBlock->GetTransform()->GetPosition().y + 32.0f)
				{
					m_State = State::STICKING;
					m_pStickBlock = gameObject;
					m_StickToBlock = true;
					m_Dizzle = false;
				}
			}
			break;
			}
		}
	}

	if (m_State == State::PUNCHING && gameObject->GetTag() == "Block" && m_Direction != Direction::NONE && !m_StickToBlock && !m_Dizzle)
	{
		switch (m_Direction)
		{
		case Direction::Down:
		{
			if (gameObject->GetTransform()->GetPosition().y > GetTransform()->GetPosition().y
				&& gameObject->GetTransform()->GetPosition().y < GetTransform()->GetPosition().y + 32.0f
				&& gameObject->GetTransform()->GetPosition().x == GetTransform()->GetPosition().x)
			{
				auto block = dynamic_cast<Block*>(gameObject);

				if (block)
				{
					block->Break();
				}
			}

			break;
		}
		case Direction::Up:
		{
			if (gameObject->GetTransform()->GetPosition().y < GetTransform()->GetPosition().y
				&& gameObject->GetTransform()->GetPosition().y > GetTransform()->GetPosition().y - 32.0f
				&& gameObject->GetTransform()->GetPosition().x == GetTransform()->GetPosition().x)
			{
				auto block = dynamic_cast<Block*>(gameObject);

				if (block)
				{
					block->Break();
				}
			}

			break;
		}
		case Direction::Right:
		{
			if (gameObject->GetTransform()->GetPosition().x > GetTransform()->GetPosition().x
				&& gameObject->GetTransform()->GetPosition().x < GetTransform()->GetPosition().x + 32.0f
				&& gameObject->GetTransform()->GetPosition().y == GetTransform()->GetPosition().y)
			{
				auto block = dynamic_cast<Block*>(gameObject);

				if (block)
				{
					block->Break();
				}
			}

			break;
		}
		case Direction::Left:
		{
			if (gameObject->GetTransform()->GetPosition().x < GetTransform()->GetPosition().x
				&& gameObject->GetTransform()->GetPosition().x > GetTransform()->GetPosition().x - 32.0f
				&& gameObject->GetTransform()->GetPosition().y == GetTransform()->GetPosition().y)
			{
				auto block = dynamic_cast<Block*>(gameObject);

				if (block)
				{
					block->Break();
				}
			}

			break;
		}
		}
	}

	if (gameObject->GetTag() == "Wall" && !m_StickToBlock && !m_Dizzle)
	{
		auto wall = dynamic_cast<Wall*>(gameObject);

		if (wall)
		{
			if (wall->GetWiggle())
			{
				m_Dizzle = true;
				m_State = State::DIZZLING;
			}
		}
	}
}

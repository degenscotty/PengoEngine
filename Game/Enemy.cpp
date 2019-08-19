#include "Enemy.h"
#include "Components.h"
#include "Block.h"
#include <string>

Enemy::Enemy(const glm::vec2& position)
	: m_pLevelManager(LevelManager::GetInstance())
	, m_pSprite(nullptr)
	, m_pGameTime(GameTime::GetInstance())
	, m_pTransform(GetTransform())
	, m_Destination()
	, m_Destroy(false)
	, m_MoveSpeed(100)
	, m_State(State::WANDERING)
	, m_Direction(Direction::NONE)
	, m_SpawnPosition(position)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
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
}

void Enemy::Update()
{
}

void Enemy::UpdateMovement()
{

}

void Enemy::UpdateAnimations()
{

}

void Enemy::Render()
{

}

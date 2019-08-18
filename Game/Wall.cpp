#include "Wall.h"
#include "Components.h"

Wall::Wall(const glm::vec2& position)
	: m_SpawnPosition(position)
	, m_State(State::IDLE)
{
}

Wall::~Wall()
{
}

void Wall::Initialize()
{
	// ------------------------------- Sprite Component ------------------------------------- //

	auto spriteComp = new SpriteComponent("Wall.png", 2, 6, 16);

	spriteComp->AddClip(6, false);
	spriteComp->AddClip(1, false);

	spriteComp->SetClipIndex(State::IDLE);

	AddComponent(spriteComp);
	// ---------------------------- Collision Component ------------------------------------- //

	auto collisionComp = new CollisionComponent(16, 16);

	AddComponent(collisionComp);

	SetTag("Wall");
	GetTransform()->Translate(m_SpawnPosition);
}

void Wall::Update()
{
}

void Wall::Render()
{
}

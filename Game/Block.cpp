#include "Block.h"
#include "Components.h"

Block::Block(const glm::vec2& position)
	: m_SpawnPosition(position)
{
}

Block::~Block()
{
}

void Block::Initialize()
{
	auto spriteComp = new SpriteComponent("Block.png", 2, 9, 32);

	spriteComp->AddClip(9, false);
	spriteComp->AddClip(1, false);

	spriteComp->SetClipIndex(State::IDLE);

	AddComponent(spriteComp);

	GetTransform()->Translate(m_SpawnPosition);
}

void Block::Update()
{
}

void Block::Render()
{
}


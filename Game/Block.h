#pragma once
#include "GameObject.h"
#include "GameTime.h"
#include "LevelManager.h"
#include <glm.hpp>

class SpriteComponent;

class Block : public GameObject
{
public:
	enum State
	{
		BRAKING,
		IDLE
	};

	enum Direction
	{
		Up,
		Down,
		Left,
		Right,
		NONE
	};

	Block(const glm::vec2& position);
	~Block();

	Block(const Block& other) = delete;
	Block(Block&& other) = delete;
	Block& operator=(const Block& other) = delete;
	Block& operator=(Block&& other) = delete;

	void UpdateMovement();
	void UpdateAnimations();

	void Push(const Direction& direction);
	void Break();

	bool GetMoving();
	const Block::Direction& GetDirection();

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	GameTime* m_pGameTime;
	SpriteComponent* m_pSpriteComponent;
	TransformComponent* m_pTransform;
	LevelManager* m_pLevelManager;

	glm::vec2 m_SpawnPosition;

	glm::vec2 m_Destination;
	State m_State;
	bool m_Moving;
	bool m_Destroy;
	float m_MoveSpeed;
	Direction m_Direction;
};


#pragma once
#include "GameObject.h"
#include "GameTime.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include <glm.hpp>

class SpriteComponent;

class ArrowBlock : public GameObject
{
public:
	enum State
	{
		FLICKER,
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

	ArrowBlock(const glm::vec2& position);
	~ArrowBlock();

	ArrowBlock(const ArrowBlock& other) = delete;
	ArrowBlock(ArrowBlock&& other) = delete;
	ArrowBlock& operator=(const ArrowBlock& other) = delete;
	ArrowBlock& operator=(ArrowBlock&& other) = delete;

	void UpdateMovement();
	void UpdateAnimations();

	void Push(const Direction& direction);

	bool GetMoving();
	const ArrowBlock::Direction& GetDirection();

	const State& GetState();
	void SetState(const State& state);

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	GameTime* m_pGameTime;
	TransformComponent* m_pTransform;
	SpriteComponent* m_pSpriteComponent;
	LevelManager* m_pLevelManager;
	SoundManager* m_pSoundManager;

	glm::vec2 m_SpawnPosition;

	glm::vec2 m_Destination;
	State m_State;
	bool m_Moving;
	float m_MoveSpeed;
	Direction m_Direction;
};


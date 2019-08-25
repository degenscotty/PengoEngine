#pragma once
#include "GameObject.h"
#include "LevelManager.h"
#include "GameTime.h"
#include <glm.hpp>

class SpriteComponent;

class Wall : public GameObject
{
public:
	enum State
	{
		WIGGLE,
		IDLE,
		FLASHING
	};

	enum Direction
	{
		Down,
		Up,
		Right,
		Left,
		NONE
	};

	Wall(const glm::vec2& position);
	~Wall();

	Wall(const Wall& other) = delete;
	Wall(Wall&& other) = delete;
	Wall& operator=(const Wall& other) = delete;
	Wall& operator=(Wall&& other) = delete;

	void UpdateAnimations();

	void TriggerWiggle(const Wall::Direction& direction);
	bool GetWiggle();

	const Direction& GetDirection();

	void OnTrigger(GameObject* gameObject);

	void TriggerBonus();

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

	Direction m_Direction;
	State m_State;
	bool m_Wiggle;
	bool m_WiggleAvailable;
	bool m_FlashAvailable;

	float m_WiggleTimer;
	float m_FlashTimer;
};


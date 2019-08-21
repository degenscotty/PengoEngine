#pragma once
#include "GameObject.h"
#include "GameTime.h"
#include <glm.hpp>

class SpriteComponent;
class LevelManager;

class Enemy : public GameObject
{
public:
	enum State
	{
		WANDERING,
		SEEKING,
		IDLE
	};

	enum Direction
	{
		Down,
		Up,
		Right,
		Left,
		NONE
	};

	Enemy(const glm::vec2& position);
	~Enemy();

	Enemy(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy& operator=(Enemy&& other) = delete;

	void UpdateStates();
	void UpdateMovement();
	void UpdateAnimations();

	void CheckNextDirection();

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	glm::vec2 m_SpawnPosition;
	GameTime* m_pGameTime;
	LevelManager* m_pLevelManager;

	TransformComponent* m_pTransform;
	SpriteComponent* m_pSprite;

	glm::vec2 m_Destination;
	State m_State;
	Direction m_Direction;
	float m_MoveSpeed;
	bool m_Destroy;

	float m_SeekTimer;
	float m_WanderTimer;


};


#pragma once
#include "GameObject.h"
#include "GameTime.h"
#include "LevelManager.h"
#include "ScoreManager.h"
#include <glm.hpp>

class SpriteComponent;

class Enemy : public GameObject
{
public:
	enum State
	{
		SPAWNING,
		WANDERING,
		PUNCHING,
		STICKING,
		DIZZLING,
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

	void CheckNextWander(int index);
	void CheckNextPunch(int index);
	void CheckPengoDirection();

	void FollowStickBlock();

	void OnTrigger(GameObject* gameObject);

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	glm::vec2 m_SpawnPosition;
	GameTime* m_pGameTime;
	LevelManager* m_pLevelManager;
	ScoreManager* m_pScoreManager;

	TransformComponent* m_pTransform;
	SpriteComponent* m_pSprite;

	glm::vec2 m_Destination;
	State m_State;
	Direction m_Direction;

	float m_MoveSpeed;
	float m_SpawnTimer;
	float m_PunchTimer;
	float m_PunchCooldown;
	float m_WanderTimer;
	float m_WanderCooldown;

	bool m_Destroy;
	
	GameObject* m_pStickBlock;
	bool m_StickToBlock;

	bool m_Dizzle;
	float m_DizzleTimer;
};


#pragma once
#include "GameObject.h"
#include "LevelManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Renderer.h"
#include "GameTime.h"
#include <glm.hpp>

class Texture2D;
class SpriteComponent;
class TransformComponent;

class Pengo : public GameObject
{
public:
	enum State
	{
		MoveDown,
		MoveUp,
		MoveRight,
		MoveLeft,
		PushDown,
		PushUp,
		PushLeft,
		PushRight,
		Idle
	};

	enum Direction
	{
		Up, 
		Down,
		Left,
		Right
	};

	Pengo();
	~Pengo();

	Pengo(const Pengo& other) = delete;
	Pengo(Pengo&& other) = delete;
	Pengo& operator=(const Pengo& other) = delete;
	Pengo& operator=(Pengo&& other) = delete;

	void UpdateMovement();
	void UpdateAnimations();
	void Respawn();

	void MoveNext();

	void OnTrigger(GameObject* gameObject);

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	Renderer* m_pRenderer;
	InputManager* m_pInput;
	SoundManager* m_pSoundManager;
	GameTime* m_pGameTime;
	LevelManager* m_pLevelManager;

	Texture2D* m_pPengoLife;

	TransformComponent* m_pTransform;
	SpriteComponent* m_pSpriteComponent;

	glm::vec2 m_Destination;
	State m_State;
	Direction m_Direction;
	float m_MoveSpeed;

	bool m_Invincible;
	bool m_Push;
	bool m_PushAvailable;
	
	float m_PushTimer;
	float m_InvincibleTimer;

	int m_Lives;
};


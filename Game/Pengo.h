#pragma once
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "GameTime.h"

class Pengo : public GameObject
{
public:
	enum State
	{
		MoveDown,
		MoveUp,
		MoveRight,
		MoveLeft,
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

	void MoveNext();

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	InputManager* m_pInput;
	GameTime* m_pGameTime;
	TransformComponent* m_pTransform;
	SpriteComponent* m_Sprite;

	glm::vec2 m_Destination;
	State m_State;
	Direction m_Direction;
	float m_MoveSpeed;
};


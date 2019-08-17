#pragma once
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"

class Pengo : public GameObject
{
public:
	enum State
	{
		DWALK,
		UWALK,
		RWALK,
		LWALK
	};

	Pengo();
	~Pengo();

	Pengo(const Pengo& other) = delete;
	Pengo(Pengo&& other) = delete;
	Pengo& operator=(const Pengo& other) = delete;
	Pengo& operator=(Pengo&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	InputManager* m_pInput;

	TransformComponent* m_pTransform;
	SpriteComponent* m_Sprite;

	State m_State;

	float m_MoveSpeed;
};


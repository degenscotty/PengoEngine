#pragma once
#include "BaseComponent.h"

class TransformComponent;

struct Rectf
{
	Rectf(float posX = 0, float posY = 0, float width = 32.0f, float height = 32.0f) : x{ posX }, y{ posY }, w{ width }, h{ height } {}

	float x;
	float y;
	float w;
	float h;
};

class CollisionComponent : public BaseComponent
{
public:
	CollisionComponent();
	~CollisionComponent();

	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent(CollisionComponent&& other) noexcept = delete;
	CollisionComponent& operator=(const CollisionComponent& other) = delete;
	CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

	void Update() override;
	void Render() override;
	virtual void Initialize() {}

	bool IsColliding(const Rectf& rect);

	const Rectf& GetRect() { return m_CollisionBox; }

private:
	TransformComponent* m_pTransformComponent;

	Rectf m_CollisionBox;
	bool m_IsActive;
};


#pragma once
#include "BaseComponent.h"
#include <glm.hpp>

class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent() = default;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) noexcept = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

	void Translate(float x, float y);
	void Translate(const glm::vec2& position);
	void Move(float x, float y);

	void Rotate(float x, bool isEuler = true);

	void Scale(float x, float y);
	void Scale(const glm::vec2& scale);

	const glm::vec2& GetPosition() const { return m_Position; }
	const glm::vec2& GetScale() const { return m_Scale; }
	const float GetRotation() const { return m_Rotation; }

	const glm::vec2& GetUp() const { return m_Up; }
	const glm::vec2& GetRight() const { return m_Right; }

protected:
	void Initialize() override;
	void Update() override;
	void Render() override {};

	void UpdateTransforms();

private:
	glm::vec2 m_Position;
	glm::vec2 m_Scale;
	float m_Rotation;

	glm::vec2 m_Up;
	glm::vec2 m_Right;
};


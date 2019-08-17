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

	void TranslateWorld(float x, float y);
	void TranslateWorld(const glm::vec2& position);
	void MoveWorld(float x, float y);

	void Rotate(float x, bool isEuler = true);
	void RotateWorld(float x, bool isEuler = true);

	void Scale(float x, float y);
	void Scale(const glm::vec2& scale);

	void ScaleWorld(float x, float y);
	void ScaleWorld(const glm::vec2& scale);

	const glm::vec2& GetPosition() const { return m_Position; }
	const glm::vec2& GetWorldPosition() const { return m_WorldPosition; }
	const glm::vec2& GetScale() const { return m_Scale; }
	const glm::vec2& GetWorldScale() const { return m_WorldScale; }
	const float GetRotation() const { return m_Rotation; }
	const float GetWorldRotation() const { return m_WorldRotation; }

	const glm::vec2& GetUp() const { return m_Up; }
	const glm::vec2& GetRight() const { return m_Right; }

protected:
	void Initialize() override;
	void Update() override;
	void Render() override {};

	void UpdateTransforms();

private:
	glm::vec2 m_Position;
	glm::vec2 m_WorldPosition;

	glm::vec2 m_Scale;
	glm::vec2 m_WorldScale;

	glm::vec2 m_Up;
	glm::vec2 m_Right;

	float m_Rotation;
	float m_WorldRotation;
};


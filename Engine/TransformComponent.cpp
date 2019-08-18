#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: m_Position(glm::vec2(0, 0))
	, m_Scale(glm::vec2(1, 1))
	, m_Up(glm::vec2(0, 1))
	, m_Right(glm::vec2(1, 0))
	, m_Rotation(0)
{
}

void TransformComponent::Initialize()
{
}

void TransformComponent::Update()
{
}

void TransformComponent::UpdateTransforms()
{
}

void TransformComponent::Translate(float x, float y)
{
	m_Position = glm::vec2(x, y);
}

void TransformComponent::Translate(const glm::vec2& position)
{
	m_Position = position;
}

void TransformComponent::Move(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
}

void TransformComponent::Rotate(float x, bool isEuler /*= true*/)
{
	m_Rotation = x;
}

void TransformComponent::Scale(float x, float y)
{
	m_Scale = glm::vec2(x, y);
}

void TransformComponent::Scale(const glm::vec2& scale)
{
	m_Scale = scale;
}

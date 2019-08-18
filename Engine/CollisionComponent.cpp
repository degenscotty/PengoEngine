#include "pch.h"
#include "CollisionComponent.h"

#include "TransformComponent.h"
#include "Renderer.h"

CollisionComponent::CollisionComponent()
	: m_pTransformComponent{ nullptr }
	, m_CollisionBox{}
	, m_IsActive{ true }
{
}

CollisionComponent::~CollisionComponent()
{
	m_pTransformComponent = nullptr;
}

void CollisionComponent::Update()
{
	if (m_pGameObject != nullptr)
	{
		m_pTransformComponent = GetTransform();
	}
	else
	{
		CORE_ERROR("CollisionComponent::Update() > This CollisionComponent has not been added to a gameObject!");
	}

	m_CollisionBox.x = m_pTransformComponent->GetPosition().x;
	m_CollisionBox.y = m_pTransformComponent->GetPosition().y;
}

bool CollisionComponent::IsColliding(const Rectf& rect)
{
	if ((rect.x + rect.w) <= m_CollisionBox.x || (m_CollisionBox.x + m_CollisionBox.w) <= rect.x)
	{
		return false;
	}

	if ((rect.y + rect.h) <= m_CollisionBox.y || (m_CollisionBox.y + m_CollisionBox.h) <= rect.y)
	{
		return false;
	}

	return true;
}

void CollisionComponent::Render()
{
	SDL_RenderDrawRect(Renderer::GetInstance()->GetSDLRenderer(), &SDL_Rect({ (int)m_CollisionBox.x, (int)m_CollisionBox.y, (int)m_CollisionBox.w, (int)m_CollisionBox.h }));
}

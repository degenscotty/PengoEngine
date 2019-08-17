#include "pch.h"
#include "BaseComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"


BaseComponent::BaseComponent()
	: m_pGameObject{ nullptr }
{

}

TransformComponent* BaseComponent::GetTransform() const
{
	if (m_pGameObject == nullptr)
	{
		CORE_ERROR("Failed to retrieve TransformComponent")
			return nullptr;
	}

	return m_pGameObject->GetTransform();
}

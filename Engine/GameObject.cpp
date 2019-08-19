#include "pch.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"

GameObject::GameObject()
	: m_Tag()
	, m_Components{}
	, m_pTransform(nullptr)
	, m_pScene(nullptr)
{
	m_pTransform = new TransformComponent();
	m_Components.push_back(m_pTransform);

	SetCollisionCallBack(BIND_FN(GameObject::OnTrigger));
}

GameObject::~GameObject()
{
	for (BaseComponent* component : m_Components)
	{
		SafeDelete(component);
	}
}

void GameObject::RootInitialize()
{
	Initialize();

	for (BaseComponent* component : m_Components)
	{
		component->Initialize();
	}
}

void GameObject::RootUpdate()
{
	Update();

	for (BaseComponent* component : m_Components)
	{
		component->Update();
	}
}

void GameObject::RootRender()
{
	Render();

	for (BaseComponent* component : m_Components)
	{
		component->Render();
	}
}

void GameObject::AddComponent(BaseComponent* component)
{
	if (typeid(*component) == typeid(TransformComponent) && HasComponent<TransformComponent>())
	{
		CORE_ERROR("GameObject::AddComponent > GameObject can contain only one TransformComponent!");
		return;
	}

	auto it = find(m_Components.begin(), m_Components.end(), component);

	if (it != m_Components.end())
	{
		CORE_ERROR("GameObject::AddComponent > Component is already attached to this GameObject!");
		return;
	}

	m_Components.push_back(component);
	component->m_pGameObject = this;
}

void GameObject::RemoveComponent(BaseComponent* component)
{
	auto it = find(m_Components.begin(), m_Components.end(), component);

	if (it == m_Components.end())
	{
		CORE_ERROR("GameObject::RemoveComponent > Component is not attached to this GameObject!");
		return;
	}

	m_Components.erase(it);
	component->m_pGameObject = nullptr;
}

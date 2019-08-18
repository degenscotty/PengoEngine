#pragma once
#include <typeinfo>
#include <functional>
#include <vector>
#include <string>
#include "Scene.h"

class BaseComponent;
class TransformComponent;
class CollisionComponent;

class GameObject
{
public:
	GameObject();

	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void AddComponent(BaseComponent* component);
	void RemoveComponent(BaseComponent* component);

	void SetCollisionCallBack(std::function<void(GameObject*)> collisionCallBack) { m_CollisionCallBack = collisionCallBack; }

	TransformComponent* GetTransform() const { return m_pTransform; }

	void Destroy() { m_Destroy = true; }
	bool CheckDestroy() { return m_Destroy; }

	void SetTag(const std::string& tag) { m_Tag = tag; }
	const std::string& GetTag() { return m_Tag; }

	Scene* GetScene() { if (m_pScene) return m_pScene; else return nullptr; }

	virtual void OnTrigger(GameObject* gameObject) {}

#pragma region 
	///This code is completely based on Overlord engine(GP2)
	template <class T>
	bool HasComponent()
	{
		return GetComponent<T>() != nullptr;
	}

	template <class T>
	T* GetComponent()
	{
		const type_info& ti = typeid(T);
		for (auto* component : m_Components)
		{
			if (component && typeid(*component) == ti)
				return static_cast<T*>(component);
		}

		return nullptr;
	}

#pragma endregion Template Methods

protected:
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}

private:
	friend class Scene;

	void RootInitialize();
	void RootUpdate();
	void RootRender();

	std::string m_Tag;
	bool m_Destroy;

	Scene* m_pScene;
	std::vector<BaseComponent*> m_Components;
	TransformComponent* m_pTransform;
	std::function<void(GameObject*)> m_CollisionCallBack;
};


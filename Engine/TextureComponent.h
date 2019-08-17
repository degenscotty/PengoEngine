#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <glm.hpp>

class Renderer;
class TransformComponent;
class GameObject;

class TextureComponent : public BaseComponent
{
public:
	explicit TextureComponent(const std::string& file);
	virtual ~TextureComponent() = default;

	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) noexcept = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

	void Render() override;
	virtual void Initialize() {}
	virtual void Update() {}

	void SetPivot(const glm::vec2& pivot);
	void SetTexture(const std::string& file);

	Texture2D* GetTexture() { return m_pTexture; };
	const glm::vec2& GetPivot() { return m_Pivot; };

private:
	std::string m_File;
	Texture2D* m_pTexture;
	glm::vec2 m_Pivot;

	Renderer* m_Renderer;
};


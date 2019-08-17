#include "pch.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Renderer.h"

TextureComponent::TextureComponent(const std::string& file)
	: m_pTexture{ nullptr }
	, m_Pivot{}
	, m_Renderer(Renderer::GetInstance())
	, m_File{}
{
	SetTexture(file);
}

void TextureComponent::SetTexture(const std::string& file)
{
	if (file == m_File)
	{
		CORE_INFO("TextureComponent::SetTexture > This Texture has already been set! {0}", file);
	}

	m_File = file;
	m_pTexture = ResourceManager::GetInstance()->LoadTexture(m_File);
}

void TextureComponent::SetPivot(const glm::vec2& pivot)
{
	m_Pivot = pivot;
}

void TextureComponent::Render()
{
	if (!m_pTexture)
	{
		CORE_ERROR("TextureComponent::Render > Failed to render Texture!");
	}

	TransformComponent* transformComponent = GetGameObject()->GetComponent<TransformComponent>();
	m_Renderer->RenderTextureComponent(this, transformComponent);
}

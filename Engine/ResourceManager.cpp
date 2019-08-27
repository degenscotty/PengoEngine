#include "pch.h"
#include "ResourceManager.h"
#include "Renderer.h"

ResourceManager::ResourceManager()
	: m_FolderPath("./Resources/")
{
}

ResourceManager::~ResourceManager()
{
	for (auto texture : m_Textures)
	{
		delete texture.second;
	}
	for (auto font : m_Fonts)
	{
		delete font.second;
	}
}

Texture2D* ResourceManager::LoadTexture(const std::string& file)
{
	Renderer* renderer = Renderer::GetInstance();

	if (renderer->GetSDLRenderer())
	{
		if (m_Textures[file]) return m_Textures[file];

		std::string filePath = m_FolderPath + file;
		SDL_Surface* surface = IMG_Load(filePath.c_str());

		if (surface == nullptr)
		{
			CORE_ERROR("ResourceManager::LoadTexture > Failed to load SDL_Surface: {0}", SDL_GetError());
		}

		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(), surface);
		if (pTexture == nullptr)
		{
			CORE_ERROR("ResourceManager::LoadTexture > Failed to create texture: {0}", SDL_GetError());
		}
		m_Textures[file] = new Texture2D(pTexture);
		return m_Textures[file];
	}
	else
	{
		CORE_ERROR("ResourceManager::LoadTexture > Renderer is invalid!");
		return nullptr;
	}
}

Font* ResourceManager::LoadFont(const std::pair<std::string, unsigned int>& fontData)
{
	if (m_Fonts[fontData]) return m_Fonts[fontData];

	std::string filePath = m_FolderPath + fontData.first;
	TTF_Font* pFont = TTF_OpenFont(filePath.c_str(), fontData.second);

	if (pFont == nullptr)
	{
		CORE_ERROR("ResourceManager::LoadFont > Error loading Font: {0}", TTF_GetError());
		return nullptr;
	}

	m_Fonts[fontData] = new Font(pFont);
	return m_Fonts[fontData];
}

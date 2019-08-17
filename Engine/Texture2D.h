#pragma once

#include <SDL_image.h>
#include "Log.h"

class Texture2D
{
public:
	explicit Texture2D(SDL_Texture* texture) : m_pTexture{ texture } {};
	~Texture2D() { SDL_DestroyTexture(m_pTexture); };

	Texture2D(const Texture2D &) = delete;
	Texture2D(Texture2D &&) = delete;
	Texture2D & operator= (const Texture2D &) = delete;
	Texture2D & operator= (const Texture2D &&) = delete;

	SDL_Texture* GetSDLTexture() const
	{
		if (m_pTexture)
			return m_pTexture;
		CORE_ERROR("Texture2D::GetSDLTexture() > Texture not available: m_pTexture = nullptr");
		return nullptr;
	};
private:
	SDL_Texture* m_pTexture;
};

#pragma once

#include <SDL_ttf.h>

class Font
{
public:
	explicit Font(TTF_Font* font) : m_pFont{ font } {};
	~Font() { TTF_CloseFont(m_pFont); };

	Font(const Font &) = delete;
	Font(Font &&) = delete;
	Font & operator= (const Font &) = delete;
	Font & operator= (const Font &&) = delete;

	TTF_Font* GetTTFFont() const
	{
		if (m_pFont)
			return m_pFont;
		CORE_ERROR("Font::GetTTFFont() > TTF_Font not available: m_pFont = nullptr");
		return nullptr;
	}
private:
	TTF_Font* m_pFont;
	unsigned int m_Size;
};

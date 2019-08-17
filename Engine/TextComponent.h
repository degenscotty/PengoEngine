#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"
#include <glm.hpp>
#include <SDL.h>

#include "Font.h"

class TextComponent : public BaseComponent
{
public:
	TextComponent(const std::string& file, const std::string& text, unsigned int size);
	virtual ~TextComponent() = default;

	void Initialize() override {};
	void Update() override;
	void Render() override;

	void SetText(const std::string& text);
	void SetFont(const std::pair<std::string, unsigned int>& fontData);
	void SetColor(const SDL_Color& color);
	void SetPivot(const glm::vec3& pivot);

	const glm::vec3& GetPivot() { return m_pPivot; };
	Texture2D* GetTexture() const { return m_pTexture; }

private:
	std::pair<std::string, unsigned int> m_FontData;

	std::string m_Text;
	bool m_UpdateText;

	Font* m_pFont;
	Texture2D* m_pTexture;

	SDL_Color m_Color;
	glm::vec3 m_pPivot;

	Renderer* m_Renderer;
};

inline std::ostream& operator<<(std::ostream& os, const std::pair<std::string, unsigned int>& fontData)
{
	return os << "[" << fontData.first << ", " << fontData.second << "]";
}

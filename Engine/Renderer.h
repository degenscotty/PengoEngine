#pragma once
#include "Singleton.h"
#include "Texture2D.h"
#include "SceneManager.h"
#include "Components.h"

class Renderer : public Singleton<Renderer>
{
public:
	Renderer();
	~Renderer();

	void Initialize();
	void Render();
	void ClearBuffer();

	void RenderTexture(const Texture2D& texture, float x, float y) const;
	void RenderTexture(SDL_Texture* texture, int x, int y, int width, int height);
	void RenderTextureComponent(TextureComponent* textureComponent, TransformComponent* transfComponent);
	void RenderSpriteComponent(SpriteComponent* spriteComponent, TransformComponent* transfComponent, const SDL_Rect& srcRect, const SDL_RendererFlip& flip);
	void RenderTextComponent(TextComponent* textureComponent, TransformComponent* transfComponent);

	SDL_Renderer* GetSDLRenderer();

private:
	SDL_Renderer* m_pRenderer;
};


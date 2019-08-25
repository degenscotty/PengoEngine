#include "pch.h"
#include "Renderer.h"
#include "Application.h"
#include "ResourceManager.h"

Renderer::Renderer()
	: m_pRenderer{ nullptr }
	, m_pResourceManager(ResourceManager::GetInstance())
{
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = nullptr;

	IMG_Quit();
}

void Renderer::Initialize()
{
	m_pRenderer = SDL_CreateRenderer(Application::get().GetWindow().GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr)
	{
		CORE_ERROR("WindowsWindow::Initialize( ) > error when calling SDL_CreateRenderer: {0}", SDL_GetError());
		return;
	}

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		CORE_ERROR("WindowsWindow::Initialize( ) > error when calling IMG_Init: {0}", IMG_GetError());
		return;
	}

	if (TTF_Init() == -1)
	{
		CORE_ERROR("WindowsWindow::Initialize( ) > error when calling TTF_Init: {0}", TTF_GetError());
		return;
	}
}

SDL_Renderer* Renderer::GetSDLRenderer()
{
	return m_pRenderer;
}

void Renderer::ClearBuffer()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
}

void Renderer::Render()
{
	SDL_RenderPresent(m_pRenderer);
}

void Renderer::RenderTexture(const Texture2D& texture, float x, float y) const
{

}

void Renderer::RenderTexture(SDL_Texture* texture, int x, int y, int width, int height)
{
	SDL_Rect dest;

	dest.x = (int)x;
	dest.y = (int)y;

	SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

	dest.w = int(width);
	dest.h = int(height);

	//dest.x = dest.x - (int)(dest.w / 2.0f);
	//dest.y = dest.y - (int)(dest.h / 2.0f);

	SDL_RenderCopyEx(GetSDLRenderer(), texture, nullptr, &dest, 0, nullptr, SDL_FLIP_NONE);
}

void Renderer::RenderTextureComponent(TextureComponent* textureComponent, TransformComponent* transfComponent)
{
	SDL_Rect dest;
	TransformComponent* pTransform = transfComponent;
	Texture2D* pTexture = textureComponent->GetTexture();

	dest.x = static_cast<int>(pTransform->GetPosition().x);
	dest.y = static_cast<int>(pTransform->GetPosition().y);

	SDL_QueryTexture(pTexture->GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);

	dest.w = int(dest.w * pTransform->GetScale().x);
	dest.h = int(dest.h * pTransform->GetScale().y);

	//dest.x = dest.x - (int)(dest.w / 2.0f);
	//dest.y = dest.y - (int)(dest.h / 2.0f);

	//SDL_Point* pPivot = new SDL_Point();
	//pPivot->x = static_cast<int>(texComponent->GetPivot().x);
	//pPivot->y = static_cast<int>(texComponent->GetPivot().y);

	//if (texComponent->GetPivot())
	//{
	//	pPivot = new SDL_Point();
	//	pPivot->x = static_cast<int>(transfComponent->GetPivot()->x);
	//	pPivot->y = static_cast<int>(transfComponent->GetPivot()->y);
	//}
	SDL_RenderCopyEx(GetSDLRenderer(), pTexture->GetSDLTexture(), nullptr, &dest, pTransform->GetRotation(), nullptr, SDL_FLIP_NONE);
}

void Renderer::RenderSpriteComponent(SpriteComponent* spriteComponent, TransformComponent* transfComponent, const SDL_Rect& srcRect, const SDL_RendererFlip& flip)
{
	SDL_Rect dest;
	TransformComponent* pTransform = transfComponent;
	Texture2D* pTexture = spriteComponent->GetTexture();

	dest.x = static_cast<int>(pTransform->GetPosition().x);
	dest.y = static_cast<int>(pTransform->GetPosition().y);

	SDL_QueryTexture(pTexture->GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);

	dest.w = int(srcRect.w);
	dest.h = int(srcRect.h);

	//dest.x = dest.x - (int)(dest.w / 2.0f);
	//dest.y = dest.y - (int)(dest.h / 2.0f);

	//SDL_Point* pPivot = new SDL_Point();
	//pPivot->x = static_cast<int>(texComponent->GetPivot().x);
	//pPivot->y = static_cast<int>(texComponent->GetPivot().y);

	//if (texComponent->GetPivot())
	//{
	//	pPivot = new SDL_Point();
	//	pPivot->x = static_cast<int>(transfComponent->GetPivot()->x);
	//	pPivot->y = static_cast<int>(transfComponent->GetPivot()->y);
	//}
	SDL_RenderCopyEx(GetSDLRenderer(), pTexture->GetSDLTexture(), &srcRect, &dest, pTransform->GetRotation(), nullptr, flip);
}

void Renderer::RenderTextComponent(TextComponent* textureComponent, TransformComponent* transfComponent)
{
	SDL_Rect dest;
	TransformComponent* pTransform = transfComponent;
	Texture2D* pTexture = textureComponent->GetTexture();

	dest.x = static_cast<int>(pTransform->GetPosition().x);
	dest.y = static_cast<int>(pTransform->GetPosition().y);

	SDL_QueryTexture(pTexture->GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);

	dest.w = int(dest.w * pTransform->GetScale().x);
	dest.h = int(dest.h * pTransform->GetScale().y);

	//dest.x = dest.x - (int)(dest.w / 2.0f);
	//dest.y = dest.y - (int)(dest.h / 2.0f);

	SDL_RenderCopyEx(GetSDLRenderer(), pTexture->GetSDLTexture(), nullptr, &dest, pTransform->GetRotation(), nullptr, SDL_FLIP_NONE);
}

void Renderer::RenderText(const std::string& string, SDL_Color color, const std::string& file, int size, int x, int y)
{
	auto font = ResourceManager::GetInstance()->LoadFont(std::make_pair(file, size));

	SDL_Surface* pSurface = TTF_RenderText_Blended(font->GetTTFFont(), string.c_str(), color);
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(GetSDLRenderer(), pSurface);
	SDL_FreeSurface(pSurface);

	auto texture2D = new Texture2D(pTexture);

	SDL_Rect dest;

	dest.x = static_cast<int>(x);
	dest.y = static_cast<int>(y);

	SDL_QueryTexture(pTexture, nullptr, nullptr, &dest.w, &dest.h);

	dest.w = int(dest.w * 1);
	dest.h = int(dest.h * 1);

	dest.x = dest.x - (int)(dest.w / 2.0f);
	dest.y = dest.y - (int)(dest.h / 2.0f);

	SDL_RenderCopyEx(GetSDLRenderer(), texture2D->GetSDLTexture(), nullptr, &dest, 0, nullptr, SDL_FLIP_NONE);

	delete texture2D;
}

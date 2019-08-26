#include "pch.h"
#include "Button.h"

#include "ResourceManager.h"
#include "Texture2D.h"
#include "utils.h"

Button::Button(const glm::vec2& position, const std::string& filepathS, const std::string& filepathNS)
	: m_Rectf(position.x, position.y, 0, 0)
	, m_FilePathS(filepathS)
	, m_FilePathNS(filepathNS)
	, m_pButtonNS(nullptr)
	, m_pButtonS(nullptr)
	, m_Selected(false)
	, m_pSoundManager(SoundManager::GetInstance())
	, m_pRenderer(Renderer::GetInstance())
{
}

Button::~Button()
{
}

void Button::Initialize()
{
	SDL_Rect dest;

	m_pButtonS = ResourceManager::GetInstance()->LoadTexture(m_FilePathS);
	m_pButtonNS = ResourceManager::GetInstance()->LoadTexture(m_FilePathNS);

	SDL_QueryTexture(m_pButtonS->GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);

	m_Rectf.x -= (float)dest.w / 2.0f;
	m_Rectf.y -= (float)dest.h / 2.0f;
	m_Rectf.z = (float)dest.w;
	m_Rectf.w = (float)dest.h;
}

void Button::Update(const glm::vec2& mousePos)
{
	if (utils::IsPointInRect(mousePos, m_Rectf))
	{
		//if (!m_Selected) m_pSoundManager->PlaySoundByID(5, 5, 0.2f, eSoundMerge::Replay);
		m_Selected = true;
	}
	else m_Selected = false;
}

bool Button::OnClick()
{
	if (m_Selected)
	{
		//m_pSoundManager->PlaySoundByID(6, 6, 0.4f, eSoundMerge::Replay);
		return true;
	}
	else return false;
}

void Button::Render()
{
	if (m_Selected)
	{
		m_pRenderer->RenderTexture(m_pButtonS->GetSDLTexture(), (int)m_Rectf.x, (int)m_Rectf.y);
	}
	else
	{
		m_pRenderer->RenderTexture(m_pButtonNS->GetSDLTexture(), (int)m_Rectf.x, (int)m_Rectf.y);
	}
}
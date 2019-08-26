 #pragma once
#include "Renderer.h"
#include "SoundManager.h"
#include <glm.hpp>

class Texture2D;

class Button
{
public:
	Button(const glm::vec2& position, const std::string& filepathS, const std::string& filepathNS);
	~Button();

	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;

	void Initialize();
	void Update(const glm::vec2& mousePos);
	bool OnClick();
	void Render();

private:
	Renderer* m_pRenderer;
	SoundManager* m_pSoundManager;
	std::string m_FilePathS;
	std::string m_FilePathNS;

	glm::vec4 m_Rectf;

	Texture2D* m_pButtonS;
	Texture2D* m_pButtonNS;

	bool m_Selected;
};


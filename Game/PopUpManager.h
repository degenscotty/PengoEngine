#pragma once
#include "Singleton.h"

#include "GameTime.h"
#include "Renderer.h"

#include <glm.hpp>
#include <vector>
#include <string>

class Texture2D;

struct PopUp
{
	std::string number;
	glm::vec2 position;
	float timer;
};

class PopUpManager : public Singleton<PopUpManager>
{
public:

	PopUpManager();
	~PopUpManager();

	PopUpManager(const PopUpManager& other) = delete;
	PopUpManager(PopUpManager&& other) = delete;
	PopUpManager& operator=(const PopUpManager& other) = delete;
	PopUpManager& operator=(PopUpManager&& other) = delete;

	void Update();
	void AddPopUp(const std::string& string, const glm::vec2& position);
	void Render();

private:
	Renderer* m_pRenderer;
	GameTime* m_pGameTime;

	std::vector<PopUp> m_PopUps;
};


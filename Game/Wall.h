#pragma once
#include "GameObject.h"
#include <glm.hpp>

class Wall : public GameObject
{
public:
	enum State
	{
		WIGGLE,
		IDLE
	};

	Wall(const glm::vec2& position);
	~Wall();

	Wall(const Wall& other) = delete;
	Wall(Wall&& other) = delete;
	Wall& operator=(const Wall& other) = delete;
	Wall& operator=(Wall&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	glm::vec2 m_SpawnPosition;

	State m_State;
};


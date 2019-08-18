#pragma once
#include "GameObject.h"
#include <glm.hpp>

class Block : public GameObject
{
public:
	enum State
	{
		BRAKING,
		IDLE
	};

	Block(const glm::vec2& position);
	~Block();

	Block(const Block& other) = delete;
	Block(Block&& other) = delete;
	Block& operator=(const Block& other) = delete;
	Block& operator=(Block&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;

private:
	glm::vec2 m_SpawnPosition;

	State m_State;
};


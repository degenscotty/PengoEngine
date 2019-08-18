#pragma once
#include "BaseComponent.h"
#include "GameTime.h"

#include "Texture2D.h"
#include <vector>
#include <glm.hpp>

class Renderer;
class TransformComponent;
class GameObject;

class SpriteComponent : public BaseComponent
{
public:
	explicit SpriteComponent(const std::string& file, int rows, int cols, int clipsize);
	virtual ~SpriteComponent() = default;

	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) noexcept = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

	void Render() override;
	void Update() override;
	virtual void Initialize() {}

	void SetPivot(const glm::vec2& pivot);
	void SetTexture(const std::string& file);
	void SetClipIndex(int index);
	void AddClip(int clipSize, bool repeat);
	void SetFlip(const SDL_RendererFlip& flip);

	Texture2D* GetTexture() { return m_pTexture; };
	const glm::vec2& GetPivot() { return m_Pivot; };

	bool CheckEndOfCurrentClip();

private:
	TransformComponent* m_pTransformComponent;

	std::string m_File;
	Texture2D* m_pTexture;
	glm::vec2 m_Pivot;

	Renderer* m_Renderer;
	GameTime* m_GameTime;

	int m_Cols;
	int m_Rows;
	float m_AnimTime;
	int m_FramesPerSecond;
	float m_ClipWidth;
	float m_ClipHeight;
	int m_AnimFrame;
	bool m_EndOfClip;

	int m_ClipIndex;

	std::vector<std::pair<unsigned int, bool>> m_Clips;
	std::vector<bool> m_EndedClips;
	SDL_RendererFlip m_Flip;
};


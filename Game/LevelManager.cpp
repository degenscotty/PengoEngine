#include "LevelManager.h"

#include "Scene.h"
#include "Wall.h"
#include "Block.h"

LevelManager::LevelManager()
	: m_LevelHeight{ 32 }
	, m_LevelWidth{ 28 }
	, m_pSceneManager{ SceneManager::GetInstance() }
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::Initialize()
{
	m_LevelString += L"############################";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"#......O=O=O=O=O=......O=O=#";
	m_LevelString += L"#......==========......====#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........................#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"#..........O=..............#";
	m_LevelString += L"#..........==..............#";
	m_LevelString += L"############################";

	InitializeLevel();
}

void LevelManager::InitializeLevel()
{
	for (int x = 0; x < m_LevelWidth; ++x)
	{
		for (int y = 0; y < m_LevelHeight; ++y)
		{
			wchar_t tileID = GetTile(x, y);
			switch (tileID)
			{
			case L'O':
			{
				auto block = new Block({ x * 16.0f, y * 16.0f });
				m_pSceneManager->GetActiveScene()->Add(block);
			}
			break;
			case L'#':
			{
				auto wall = new Wall({ x * 16.0f, y * 16.0f });
				m_pSceneManager->GetActiveScene()->Add(wall);
			}
			break;
			default:
				break;
			}
		}
	}
}

void LevelManager::Update()
{
}

wchar_t LevelManager::GetTile(int x, int y)
{
	if (x >= 0 && x < m_LevelWidth && y >= 0 && y < m_LevelHeight)
	{
		return m_LevelString[y * m_LevelWidth + x];
	}
	else
	{
		return L' ';
	}
}

void LevelManager::SetTile(int x, int y, wchar_t c)
{
	if (x >= 0 && x < m_LevelWidth && y >= 0 && y < m_LevelHeight)
	{
		m_LevelString[y * m_LevelWidth + x] = c;
	}
}

void LevelManager::Render()
{
}

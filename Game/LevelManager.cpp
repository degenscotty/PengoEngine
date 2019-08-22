#include "LevelManager.h"

#include "Scene.h"
#include "Wall.h"
#include "Block.h"
#include "Enemy.h"
#include "Pengo.h"
#include "ArrowBlock.h"

LevelManager::LevelManager()
	: m_LevelHeight(32)
	, m_LevelWidth(28)
	, m_pSceneManager(SceneManager::GetInstance())
	, m_pPengo(nullptr)
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::SetPengo(Pengo* pengo)
{
	m_pPengo = pengo;
}

Pengo* LevelManager::GetPengo()
{
	return m_pPengo;
}

void LevelManager::Initialize()
{
	m_LevelString += L"############################";
	m_LevelString += L"#..O=......O=..........O=..#";
	m_LevelString += L"#..==......==..........==..#";
	m_LevelString += L"#..O=..O=O=O=O=X.O=O=..A=..#";
	m_LevelString += L"#..==..========..====..==..#";
	m_LevelString += L"#......O=..........O=..O=..#";
	m_LevelString += L"#......==..........==..==..#";
	m_LevelString += L"#..O=O=O=..O=O=O=..O=..O=..#";
	m_LevelString += L"#..======..======..==..==..#";
	m_LevelString += L"#..........O=......O=......#";
	m_LevelString += L"#..........==......==......#";
	m_LevelString += L"#O=O=O=O=O=O=..O=O=O=..X...#";
	m_LevelString += L"#============..======......#";
	m_LevelString += L"#..............O=..O=..O=..#";
	m_LevelString += L"#..............==..==..==..#";
	m_LevelString += L"#..O=O=O=O=O=O=O=..A=..O=O=#";
	m_LevelString += L"#..==============..==..====#";
	m_LevelString += L"#..O=..........O=..........#";
	m_LevelString += L"#..==..........==..........#";
	m_LevelString += L"#..O=O=O=O=O=..O=..O=O=O=..#";
	m_LevelString += L"#..==========..==..======..#";
	m_LevelString += L"#..O=..........O=..O=......#";
	m_LevelString += L"#..==..........==..==......#";
	m_LevelString += L"#..O=..O=O=O=O=O=..O=O=X.O=#";
	m_LevelString += L"#..==..==========..====..==#";
	m_LevelString += L"#......O=......O=..........#";
	m_LevelString += L"#......==......==..........#";
	m_LevelString += L"#O=O=..O=..A=..O=O=O=O=O=..#";
	m_LevelString += L"#====..==..==..==========..#";
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
			case L'X':
			{
				auto enemy = new Enemy({ x * 16.0f, y * 16.0f });
				SetTile(x, y, L'.');
				m_pSceneManager->GetActiveScene()->Add(enemy);
			}
			break;
			case L'A':
			{
				auto arrowBlock = new ArrowBlock({ x * 16.0f, y * 16.0f });
				m_pSceneManager->GetActiveScene()->Add(arrowBlock);
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

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
	, m_pArrowBlocks()
	, m_ArrowBlockBonus(false)
	, m_pScoreManager(ScoreManager::GetInstance())
	, m_ArrowBlockPositions()
	, m_pWalls()
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
	m_LevelString += L"#..O=......H=..........O=..#";
	m_LevelString += L"#..==......==..........==..#";
	m_LevelString += L"#..O=..O=O=O=O=X.O=O=..A=..#";
	m_LevelString += L"#..==..========..====..==..#";
	m_LevelString += L"#......O=..........O=..O=..#";
	m_LevelString += L"#......==..........==..==..#";
	m_LevelString += L"#..O=O=O=..O=O=O=..O=..O=..#";
	m_LevelString += L"#..======..======..==..==..#";
	m_LevelString += L"#..........O=......O=......#";
	m_LevelString += L"#..........==......==......#";
	m_LevelString += L"#O=H=O=O=O=O=..O=O=O=..X...#";
	m_LevelString += L"#============..======......#";
	m_LevelString += L"#..............O=..O=..O=..#";
	m_LevelString += L"#..............==..==..==..#";
	m_LevelString += L"#..O=O=O=O=O=H=O=..A=..O=O=#";
	m_LevelString += L"#..==============..==..====#";
	m_LevelString += L"#..O=..........O=..........#";
	m_LevelString += L"#..==..........==..........#";
	m_LevelString += L"#..O=O=O=O=O=..O=..O=O=O=..#";
	m_LevelString += L"#..==========..==..======..#";
	m_LevelString += L"#..O=..........O=..O=......#";
	m_LevelString += L"#..==..........==..==......#";
	m_LevelString += L"#..O=..O=O=O=O=O=..O=O=X.O=#";
	m_LevelString += L"#..==..==========..====..==#";
	m_LevelString += L"#......O=......H=..........#";
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
				auto block = new Block({ x * 16.0f, y * 16.0f }, false);
				m_pSceneManager->GetActiveScene()->Add(block);
			}
			break;
			case L'H':
			{
				auto block = new Block({ x * 16.0f, y * 16.0f }, true);
				m_pSceneManager->GetActiveScene()->Add(block);
			}
			break;
			case L'#':
			{
				auto wall = new Wall({ x * 16.0f, y * 16.0f });
				m_pWalls.push_back(wall);
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
				m_pArrowBlocks.push_back(arrowBlock);
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
	if (!m_ArrowBlockBonus)
	{
		CheckArrowBlocks();
	}
}

void LevelManager::CheckArrowBlocks()
{
	for (int x = 0; x < m_LevelWidth; ++x)
	{
		for (int y = 0; y < m_LevelHeight; ++y)
		{
			auto wchar = GetTile((int)x, (int)y);

			if (wchar == L'A')
			{
				CheckArrowBlockSides(x, y, 0);
				m_ArrowBlockPositions.clear();
			}
		}
	}
}

void LevelManager::CheckArrowBlockSides(int posx, int posy, int index)
{
	m_ArrowBlockPositions.push_back({ posx, posy });

	if (index == 1)
	{
		std::for_each(m_pArrowBlocks.begin(), m_pArrowBlocks.end(), [](ArrowBlock* arrowBlock) 
		{
			arrowBlock->SetState(ArrowBlock::FLICKER);
		});
	}

	if (index == 2)
	{
		m_pScoreManager->AddScore(1000);
		m_ArrowBlockBonus = true;
		std::for_each(m_pWalls.begin(), m_pWalls.end(), [](Wall* wall)
		{
			wall->TriggerBonus();
		});
		return;
	}

	int x = posx + 2;
	int y = posy;
	auto wchar = GetTile((int)x, (int)y);
	if (wchar == 'A')
	{
		if (m_ArrowBlockPositions.size() > 1)
		{
			if (m_ArrowBlockPositions[index - 1] != glm::vec2{ x, y })
			{
				CheckArrowBlockSides(x, y, index + 1);
			}
		}
		else
		{
			CheckArrowBlockSides(x, y, index + 1);
		}
		return;
	}

	x -= 4;
	wchar = GetTile((int)x, (int)y);
	if (wchar == 'A')
	{
		if (m_ArrowBlockPositions.size() > 1)
		{
			if (m_ArrowBlockPositions[index - 1] != glm::vec2{ x, y })
			{
				CheckArrowBlockSides(x, y, index + 1);
			}
		}
		else
		{
			CheckArrowBlockSides(x, y, index + 1);
		}
		return;
	}

	x += 2;
	y += 2;
	wchar = GetTile((int)x, (int)y);
	if (wchar == 'A')
	{
		if (m_ArrowBlockPositions.size() > 1)
		{
			if (m_ArrowBlockPositions[index - 1] != glm::vec2{ x, y })
			{
				CheckArrowBlockSides(x, y, index + 1);
			}
		}
		else
		{
			CheckArrowBlockSides(x, y, index + 1);
		}
		return;
	}

	y -= 4;
	wchar = GetTile((int)x, (int)y);
	if (wchar == 'A')
	{
		if (m_ArrowBlockPositions.size() > 1)
		{
			if (m_ArrowBlockPositions[index - 1] != glm::vec2{ x, y })
			{
				CheckArrowBlockSides(x, y, index + 1);
			}
		}
		else
		{
			CheckArrowBlockSides(x, y, index + 1);
		}
		return;
	}

	if (index == 1)
	{
		std::for_each(m_pArrowBlocks.begin(), m_pArrowBlocks.end(), [](ArrowBlock* arrowBlock)
		{
			arrowBlock->SetState(ArrowBlock::IDLE);
		});
	}
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

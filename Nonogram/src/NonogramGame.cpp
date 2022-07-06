#include "NonogramGame.h"

NonogramGame::NonogramGame()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(800, 600), "Nonogram", sf::Style::Titlebar);
	m_GameState = GameStates::Menu;
}

NonogramGame::~NonogramGame()
{
	delete m_Window;
}

bool NonogramGame::Start()
{
	uint32_t chosenLevel = 1;
	while (m_GameState != GameStates::Exit)
	{
		if (m_GameState == GameStates::Menu)
		{
			MainMenu *menu = new MainMenu(m_Window, &m_Event);
			chosenLevel = menu->Run(m_GameState);
			delete menu;
		}
		if (m_GameState == GameStates::InGame)
		{
			switch (chosenLevel)
			{
			case 1:
			{
				Level *testLevel = new Level(m_Window, &m_Event, RSC_DIR "Levels/TestLevel.lv");
				testLevel->Run(m_GameState);
				delete testLevel;
			}
			break;
			default:
				return false;
			}
		}
	}
	m_Window->close();
	return true;
}

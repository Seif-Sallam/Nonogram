#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include <fstream>

#include "SimpleButton.h"
#include "GameStates.h"

class MainMenu {
public:
	MainMenu(sf::RenderWindow* window, sf::Event* event);
	uint32_t Run(GameStates& g);
	~MainMenu();
private:
	void EventHandling(GameStates& g);
	void Update(GameStates& g);
	void Draw();
	uint32_t GetNumberOfLevels();
private:
	sf::RenderWindow* m_Window;
	sf::Event* m_Event;
	sf::View m_View;
	sf::Font m_Font;
	sf::Texture m_BackgroundTexture;
	sf::Sprite m_Background;
	SimpleButton* m_ExitButton;
	SimpleButton* m_StartButton;
	SimpleButton* m_LeftLevelChanger;
	SimpleButton* m_RightLevelChanger;
	std::vector<SimpleButton*> m_LevelsList;
	uint32_t m_ChosenLevel;
	uint32_t m_CurrentLevel;
	uint32_t m_NumberOfLevels;
	enum class State {
		StartingMenu,
		LevelSelection
	} m_MenuState;
};
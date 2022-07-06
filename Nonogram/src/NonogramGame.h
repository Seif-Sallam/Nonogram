#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include <stack>
#include "Level.h"
#include "MainMenu.h"

class NonogramGame {
public:
	NonogramGame();
	~NonogramGame();
	bool Start();

private:
	sf::RenderWindow* m_Window;
	sf::Event m_Event;
	GameStates m_GameState;
};
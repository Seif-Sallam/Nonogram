#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

#include "Grid.h"
#include "Label.h"
#include "GameStates.h"
#include "SimpleButton.h"

class Level {
public:
	Level(sf::RenderWindow* window, sf::Event* event, const std::string& levelName);
	void Run(GameStates& g);
	~Level();
private:
	void EventHandling(GameStates& g);
	void Update(GameStates& g);
	void Draw();
	void ReadLevel(const std::string& levelName);
	void CheckWin(GameStates& g);
private:
	sf::RenderWindow* m_Window;
	sf::Event* m_Event;
	sf::View m_View;
	sf::Font m_Font;
	sf::Text m_NumberOfPlacedTilesText;
	sf::Text m_WinningText;
	bool m_Won;
	Grid* m_Grid;
	std::vector<Label*> m_VertLabels;
	std::vector<Label*> m_HorizLabels;
	std::vector<std::vector<std::vector<uint32_t>>> m_RowAnswerSequences;
	std::vector<std::vector<std::vector<uint32_t>>> m_ColumnAnswerSequences;
	std::vector<TileState> m_AnswerSequence;
	uint32_t m_MaxNumberOfBlackTiles;
	SimpleButton* m_ExitButton;
	SimpleButton* m_ResetButton;
	sf::Clock m_Clock;
};
#include "Level.h"

Level::Level(sf::RenderWindow *window, sf::Event *event, const std::string &levelName)
{
	m_Window = window;
	m_Event = event;
	if (!m_Font.loadFromFile(RSC_DIR "Roboto.ttf"))
	{
		std::cout << "Font Roboto was not Loaded\n";
		throw;
	}
	m_MaxNumberOfBlackTiles = 0;

	ReadLevel(levelName);
	m_NumberOfPlacedTilesText.setFont(m_Font);
	Vec2f exitButtonPosition = Vec2f(m_Window->getSize().x - 50.f, m_Window->getSize().y - 50.f);
	Vec2f resetButtonPosition = Vec2f(10.f, m_Window->getSize().y - 50.f);
	m_ExitButton = new SimpleButton("Exit", &m_Font, exitButtonPosition, 20);
	m_ResetButton = new SimpleButton("Reset", &m_Font, resetButtonPosition, 20);
	m_WinningText.setString("You Won!\n");
	m_WinningText.setFont(m_Font);
	m_WinningText.setCharacterSize(35);
	m_WinningText.setPosition(sf::Vector2f(m_Window->getSize().x / 2.0f - 50.0f, m_Window->getSize().y / 2.0f));
}

Level::~Level()
{
	for (uint32_t i = 0; i < m_HorizLabels.size(); i++)
		delete m_HorizLabels[i];
	for (uint32_t i = 0; i < m_VertLabels.size(); i++)
		delete m_VertLabels[i];
	delete m_Grid;
}

void Level::EventHandling(GameStates &g)
{
	while (m_Window->pollEvent(*m_Event))
	{
		if (m_Event->type == sf::Event::KeyPressed && m_Event->key.code == sf::Keyboard::Key::Escape)
			g = GameStates::Exit;
		if (!m_Won)
			m_Grid->PollEvents(m_Event);
		m_ExitButton->HandleEvents(m_Window, m_Event);
		m_ResetButton->HandleEvents(m_Window, m_Event);
	}
}

void Level::Update(GameStates &g)
{
	float elapsedTime = m_Clock.getElapsedTime().asSeconds();
	if (m_Won)
	{
		m_WinningText.setFillColor(sf::Color((uint8_t)abs(std::sin(elapsedTime)) * 255, 100, 125));
	}
	// Checking the buttons clicks
	if (m_ExitButton->IsPressed())
	{
		g = GameStates::Menu;
	}

	if (m_ResetButton->IsPressed())
	{
		m_Grid->Reset();
		for (uint32_t i = 0; i < m_HorizLabels.size(); i++)
		{
			m_HorizLabels[i]->Reset();
		}
		for (uint32_t i = 0; i < m_VertLabels.size(); i++)
		{
			m_VertLabels[i]->Reset();
		}
		m_Won = false;
	}
	m_ExitButton->Update();
	m_ResetButton->Update();
	// Update The labels
	const std::vector<TileState> &currentTileStates = m_Grid->GetCurrentState();

	// Check Columns:
	for (uint32_t c = 0; c < m_ColumnAnswerSequences.size(); c++)
	{
		for (uint32_t i = 0; i < m_ColumnAnswerSequences[c].size(); i++)
		{
			bool flag = true;
			for (uint32_t j = 0; j < m_ColumnAnswerSequences[c][i].size(); j++)
			{
				uint32_t index = m_ColumnAnswerSequences[c][i][j];
				if (currentTileStates[index] != TileState::Black)
				{
					flag = false;
					break;
				}
			}
			m_VertLabels[c]->UpdateCell(i, flag);
		}
	}
	// Check Rows:
	for (uint32_t r = 0; r < m_RowAnswerSequences.size(); r++)
	{
		for (uint32_t i = 0; i < m_RowAnswerSequences[r].size(); i++)
		{
			bool flag = true;
			for (uint32_t j = 0; j < m_RowAnswerSequences[r][i].size(); j++)
			{
				uint32_t index = m_RowAnswerSequences[r][i][j];
				if (currentTileStates[index] != TileState::Black)
				{
					flag = false;
					break;
				}
			}
			m_HorizLabels[r]->UpdateCell(i, flag);
		}
	}
	CheckWin(g);

	m_NumberOfPlacedTilesText.setString(std::to_string(m_Grid->GetNumberOfPLacedTiles()) + "/" + std::to_string(m_MaxNumberOfBlackTiles));
}

void Level::Draw()
{
	m_Window->setView(m_View);
	m_Window->clear(sf::Color(4, 134, 79));
	m_Window->draw(*m_Grid);
	for (uint32_t i = 0; i < m_VertLabels.size(); i++)
		m_Window->draw(*m_VertLabels[i]);
	for (uint32_t i = 0; i < m_HorizLabels.size(); i++)
		m_Window->draw(*m_HorizLabels[i]);
	m_Window->draw(*m_ExitButton);
	m_Window->draw(*m_ResetButton);
	m_Window->draw(m_NumberOfPlacedTilesText);
	if (m_Won)
		m_Window->draw(m_WinningText);
	m_Window->display();
}

void Level::ReadLevel(const std::string &levelName)
{
	std::ifstream inputFile(levelName);
	if (!inputFile.is_open())
	{
		std::cout << "Level: " << levelName << " was not opened\n";
		throw;
	}
	std::vector<TileState> gridNumbers;
	Vec2u gridSize;
	inputFile >> gridSize.x >> gridSize.y;
	Vec2f scale;

	for (uint32_t i = 0; i < gridSize.x; i++)
		for (uint32_t j = 0; j < gridSize.y; j++)
		{
			uint16_t number;
			inputFile >> number;
			gridNumbers.push_back(TileState(number));
		}
	{
		std::string div;
		std::getline(inputFile, div);
	}

	for (uint32_t i = 0; i < gridSize.x; i++)
		for (uint32_t j = 0; j < gridSize.y; j++)
		{
			uint16_t number;
			inputFile >> number;
			m_AnswerSequence.push_back(TileState(number));
		}

	uint32_t maxSet;
	inputFile >> maxSet;

	float labelOffset;
	labelOffset = maxSet * 15 + 10.0f;

	m_RowAnswerSequences.resize(gridSize.x);
	m_ColumnAnswerSequences.resize(gridSize.y);
	for (uint32_t i = 0; i < m_RowAnswerSequences.size(); i++)
		m_RowAnswerSequences[i].resize(maxSet);

	for (uint32_t i = 0; i < m_ColumnAnswerSequences.size(); i++)
		m_ColumnAnswerSequences[i].resize(maxSet);
	// Columns Part
	for (uint32_t i = 0; i < gridSize.x; i++)
	{
		uint32_t counter = 0;
		uint32_t numberingIndex = 0;

		m_VertLabels.push_back(new Label(Vec2f(labelOffset + (i * 32.0f) + 10.0f, 10.0f), maxSet, &m_Font, false, 15u));
		for (uint32_t j = 0; j < gridSize.y; j++)
		{
			uint32_t index = i + j * gridSize.x;

			if (m_AnswerSequence[index] != TileState::Crossed)
			{
				m_ColumnAnswerSequences[i][numberingIndex].push_back(index);
				counter++;
				if (j == gridSize.y - 1)
				{
					m_VertLabels[i]->FillInNumbers(numberingIndex, counter);
					counter = 0;
				}
			}
			else if (m_AnswerSequence[index] == TileState::Crossed)
			{
				if (counter > 0)
				{
					m_VertLabels[i]->FillInNumbers(numberingIndex, counter);
					numberingIndex++;
					counter = 0;
				}
			}
		}
	}

	for (uint32_t i = 0; i < gridSize.y; i++)
	{
		uint32_t counter = 0;
		uint32_t numberingIndex = 0;
		m_HorizLabels.push_back(new Label(Vec2f(10.0f, labelOffset + (i * 32.0f) + 10.0f), maxSet, &m_Font, true, 15u));
		for (uint32_t j = 0; j < gridSize.x; j++)
		{
			uint32_t index = j + i * gridSize.y;

			if (m_AnswerSequence[index] != TileState::Crossed)
			{
				m_RowAnswerSequences[i][numberingIndex].push_back(index);
				counter++;
				if (j == gridSize.x - 1)
				{
					m_HorizLabels[i]->FillInNumbers(numberingIndex, counter);
					counter = 0;
				}
			}
			else if (m_AnswerSequence[index] == TileState::Crossed)
			{
				if (counter > 0)
				{
					m_HorizLabels[i]->FillInNumbers(numberingIndex, counter);
					numberingIndex++;
					counter = 0;
				}
			}
		}
	}

	inputFile.close();
	Vec2f horzPos = m_HorizLabels[0]->GetShapeSize() + m_HorizLabels[0]->GetShapePos();
	Vec2f vertPos = m_VertLabels[0]->GetShapeSize() + m_VertLabels[0]->GetShapePos();
	m_Grid = new Grid(gridSize, Vec2f(horzPos.x, vertPos.y), m_Window, gridNumbers);
	Vec2f windowSize;
	windowSize.x = gridSize.x * 32.0f + horzPos.x + 10.0f;
	windowSize.y = gridSize.y * 32.0f + horzPos.y + 20.0f;

	m_Window->setSize({(uint32_t)windowSize.x, (uint32_t)windowSize.y});
	m_View.setCenter(windowSize / 2.0f);
	m_View.setSize(windowSize);

	for (uint32_t i = 0; i < m_AnswerSequence.size(); i++)
	{
		if (m_AnswerSequence[i] == TileState::Black)
		{
			m_MaxNumberOfBlackTiles = m_MaxNumberOfBlackTiles + 1;
		}
	}
	Vec2f textPosition;
	textPosition.x = (gridSize.x / 2.0f) * 32.0f - 20.0f + labelOffset;
	textPosition.y = gridSize.y * 32.0f + 20.0f + labelOffset;

	m_NumberOfPlacedTilesText.setPosition(textPosition);
	m_NumberOfPlacedTilesText.setCharacterSize(18u);
	m_NumberOfPlacedTilesText.setFillColor(sf::Color::Black);
}

void Level::CheckWin(GameStates &g)
{
	const std::vector<TileState> &currentState = m_Grid->GetCurrentState();
	bool win = true;
	for (uint32_t i = 0; i < currentState.size(); i++)
	{
		if (!(currentState[i] == m_AnswerSequence[i] ||
			  (m_AnswerSequence[i] == TileState::Crossed && currentState[i] == TileState::White)))
			win = false;
	}
	if (win)
	{
		m_Won = true;
	}
}

void Level::Run(GameStates &g)
{
	while (g == GameStates::InGame)
	{
		EventHandling(g);
		Update(g);
		Draw();
	}
}

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* window, sf::Event* event)
	: m_Window(window), m_Event(event)
{
	m_Window->setSize(sf::Vector2u(370.0f, 390.0f));
	m_View.setCenter(sf::Vector2f(m_Window->getSize()) / 2.0f);
	m_View.setSize(sf::Vector2f(m_Window->getSize()));

	if (!m_Font.loadFromFile("rsc/Roboto.ttf"))
	{
		std::cout << "Font FilbertColor.ttf was not opened \n";
	
#ifdef _DEBUG
        throw "Font Was not opened in MainMenu\n";
#else
		exit(1);
#endif // _DEBUG
	}
	if (!m_BackgroundTexture.loadFromFile("rsc/Background.png"))
	{
		std::cout << "Background.png was not opened\n";
#ifdef _DEBUG
        throw "Background Was not opened";
#else
		exit(1);
#endif
	}

	m_Background.setTexture(m_BackgroundTexture);
	m_ChosenLevel = 0;
	m_StartButton = new SimpleButton("Start", &m_Font, Vec2f(145.0f, 100.0f), 45u);
	m_ExitButton = new SimpleButton("Exit", &m_Font, Vec2f(145.0f, 300.0f), 45u);
	m_MenuState = State::StartingMenu;
	m_CurrentLevel = 0;
	m_NumberOfLevels = GetNumberOfLevels();
	std::cout << m_NumberOfLevels << std::endl;
}

uint32_t MainMenu::Run(GameStates& g)
{
	while (g == GameStates::Menu) 
	{
		EventHandling(g);
		Update(g);
		Draw();
	}
	return m_ChosenLevel;
}

MainMenu::~MainMenu()
{
	if (m_MenuState == State::StartingMenu)
		delete m_StartButton;
	else
	{
		delete m_LeftLevelChanger;
		delete m_RightLevelChanger;
		for (uint32_t i = 0; i < m_LevelsList.size(); i++)
			delete m_LevelsList[i];
	}
	delete m_ExitButton;
	
}

void MainMenu::EventHandling(GameStates& g)
{
	while (m_Window->pollEvent(*m_Event))
	{
		if (m_Event->type == sf::Event::KeyPressed && m_Event->key.code == sf::Keyboard::Key::Escape)
			g = GameStates::Exit;
		m_ExitButton->HandleEvents(m_Window, m_Event);
		if(m_MenuState == State::StartingMenu)
			m_StartButton->HandleEvents(m_Window, m_Event);
		if (m_MenuState == State::LevelSelection) {
			m_LevelsList[m_CurrentLevel]->HandleEvents(m_Window, m_Event);

			m_LeftLevelChanger->HandleEvents(m_Window, m_Event);
			m_RightLevelChanger->HandleEvents(m_Window, m_Event);
		}
	}
}

void MainMenu::Update(GameStates& g)
{
	if (m_MenuState == State::LevelSelection)
	{

		if (m_RightLevelChanger->IsPressed())
			if (m_CurrentLevel < m_NumberOfLevels - 1)
				m_CurrentLevel += 1;
			else
				m_CurrentLevel = 0;

		if (m_LeftLevelChanger->IsPressed())
			if (m_CurrentLevel > 0)
				m_CurrentLevel -= 1;
			else
				m_CurrentLevel = m_NumberOfLevels - 1;


		m_LeftLevelChanger->Update();
		m_RightLevelChanger->Update();

		if (m_LevelsList[m_CurrentLevel]->IsPressed())
		{
			m_ChosenLevel = m_CurrentLevel + 1;
			g = GameStates::InGame;
		}
		m_LevelsList[m_CurrentLevel]->Update();

	}

	if (m_ExitButton->IsPressed())
		g = GameStates::Exit;
	if (m_StartButton->IsPressed())
	{
		delete m_StartButton;
		m_MenuState = State::LevelSelection;
		
		for (uint32_t i = 0; i < m_NumberOfLevels; i++)
		{
			m_LevelsList.push_back(new SimpleButton("Level " + std::to_string(i + 1), &m_Font, Vec2f(120.0f, 155.0f), 45u));
		
		}
		m_LeftLevelChanger = new SimpleButton(Vec2f(20.0f, 200.0f), 30.f, true);
		m_RightLevelChanger = new SimpleButton(Vec2f(350.0f, 170.0f), 30.f, false);
	}
	if (m_MenuState == State::StartingMenu) {
		m_StartButton->Update();
	}
	m_ExitButton->Update();
}


void MainMenu::Draw()
{
	m_Window->setView(m_View);
	m_Window->clear();
	
	m_Window->draw(m_Background);
	if (m_MenuState == State::StartingMenu)
		m_Window->draw(*m_StartButton);
	else 
	{
		m_Window->draw(*m_LevelsList[m_CurrentLevel]);
		m_Window->draw(*m_RightLevelChanger);
		m_Window->draw(*m_LeftLevelChanger);
	}
	m_Window->draw(*m_ExitButton);
	m_Window->display();
}

uint32_t MainMenu::GetNumberOfLevels()
{
	std::ifstream inputFile("rsc/Levels/Levels.ini");
	if (!inputFile.is_open())
		return 0;

	uint32_t input;
	inputFile >> input;
	inputFile.close();
	return input;
}
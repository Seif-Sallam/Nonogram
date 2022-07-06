#include "SimpleButton.h"

SimpleButton::SimpleButton(const std::string &text, sf::Font *font, Vec2f position, uint32_t characterSize)
{
	m_Text.setFont(*font);
	m_Text.setString(text);
	m_Text.setPosition(position);
	m_Text.setCharacterSize(characterSize);
	m_TriangleShape.setRadius(0);
	m_IsTriangle = false;
	m_Pressed = false;
	m_CharacterSize = characterSize;
	m_Radius = 0;
}

SimpleButton::SimpleButton(Vec2f position, float_t radius, bool leftTri)
{
	m_TriangleShape.setPointCount(3);
	m_TriangleShape.setOrigin(sf::Vector2f(radius / 2.0f, radius / 2.0f));
	m_TriangleShape.setPosition(position);
	m_TriangleShape.setRadius(radius);

	m_TriangleShape.rotate((leftTri) ? -90.0f : 90.0f);
	m_IsTriangle = true;
	m_Pressed = false;
	m_Radius = radius;
	m_CharacterSize = 0;
}

SimpleButton::~SimpleButton()
{
}

void SimpleButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_Text, states);
	target.draw(m_TriangleShape, states);
}

void SimpleButton::Update() // must be called after knowing whether the button was pressed or not
{
	m_Pressed = false;
}

void SimpleButton::HandleEvents(sf::RenderWindow *window, sf::Event *event)
{
	if (MouseOnButton(window))
	{
		if (m_IsTriangle)
		{
			m_TriangleShape.setFillColor(sf::Color(64, 64, 64));
			m_TriangleShape.setRadius(m_Radius - 2);
		}
		else
		{
			m_Text.setFillColor(sf::Color(64, 64, 64));
			m_Text.setCharacterSize(m_CharacterSize - 2);
		}
		if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
		{
			m_Pressed = true;
		}
	}
	else
	{
		if (m_IsTriangle)
		{
			m_TriangleShape.setFillColor(sf::Color::White);
			m_TriangleShape.setRadius(m_Radius);
		}
		else
		{
			m_Text.setFillColor(sf::Color::White);
			m_Text.setCharacterSize(m_CharacterSize);
		}
	}
}

bool SimpleButton::MouseOnButton(sf::RenderWindow *window)
{
	Vec2i mousePos = window->mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition(*window)));
	sf::FloatRect mouseRect = sf::FloatRect(sf::Vector2f(mousePos.x, mousePos.y), sf::Vector2f(2.0f, 2.0f));

	if (!m_IsTriangle)
		return m_Text.getGlobalBounds().intersects(mouseRect);
	else
		return m_TriangleShape.getGlobalBounds().intersects(mouseRect);
}

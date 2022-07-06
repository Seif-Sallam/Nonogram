#include "Label.h"

Label::Label(Vec2f position, uint32_t numberOfSets, sf::Font *font, bool horizontal, uint32_t characterSize)
{
	m_CompletedSets.resize(numberOfSets, false);
	m_Numbers.resize(numberOfSets);
	m_Shape.setPosition(position);
	m_Shape.setFillColor(sf::Color(125, 125, 125));
	uint32_t size = characterSize * numberOfSets + 10.0f;
	m_Shape.setSize((horizontal) ? Vec2f(size, 32.0f) : Vec2f(32.0f, size));
	for (uint32_t i = 0; i < m_Numbers.size(); i++)
	{
		if (characterSize < 18)
			m_Numbers[i].setCharacterSize(characterSize);
		else
			m_Numbers[i].setCharacterSize(17);
		m_Numbers[i].setFont(*font);
		if (horizontal)
		{
			Vec2f position = {m_Shape.getPosition().x + (i + 1) * 15.f, m_Shape.getPosition().y + 5.0f};
			m_Numbers[i].setPosition(position);
		}
		else
		{
			Vec2f position = {m_Shape.getPosition().x + 10.0f, m_Shape.getPosition().y + (i + 1) * 15.f - 10.0f};
			m_Numbers[i].setPosition(position);
		}
	}
}

Label::~Label()
{
}

void Label::FillInNumbers(const std::vector<uint32_t> &numbers)
{
	for (uint32_t i = 0; i < m_Numbers.size(); i++)
	{
		m_Numbers[i].setString(std::to_string(numbers[i]));
	}
}

void Label::FillInNumbers(uint32_t index, uint32_t number)
{
	m_Numbers[index].setString(std::to_string(number));
}

void Label::UpdateCell(uint32_t index, bool complete)
{
	if (complete)
	{
		m_Numbers[index].setFillColor(sf::Color::Black);
		m_CompletedSets[index] = true;
	}
	else
	{
		m_Numbers[index].setFillColor(sf::Color::White);
		m_CompletedSets[index] = false;
	}
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
	target.draw(m_Shape, state);
	for (uint32_t i = 0; i < m_Numbers.size(); i++)
		target.draw(m_Numbers[i]);
}

void Label::Reset()
{
	for (auto &number : m_Numbers)
		number.setFillColor(sf::Color::White);
}

#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "Vec2.h"

class Label : public sf::Drawable
{
public:
	Label(Vec2f position, uint32_t numberOfSets, sf::Font* font, bool horizontal, uint32_t characterSize);
	~Label();
	void FillInNumbers(const std::vector<uint32_t>& numbers);
	void FillInNumbers(uint32_t index, uint32_t number);
	void UpdateCell(uint32_t index, bool complete);
	inline Vec2f GetShapeSize() const { return m_Shape.getSize(); }
	inline Vec2f GetShapePos() const { return m_Shape.getPosition(); }
	void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
	void Reset();
private:
	std::vector<sf::Text> m_Numbers;
	std::vector<bool> m_CompletedSets;
	sf::RectangleShape m_Shape;
};
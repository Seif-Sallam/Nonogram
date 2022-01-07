#pragma once

#include <string>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "Vec2.h"

class SimpleButton : public sf::Drawable
{
public:
	SimpleButton(const std::string& text, sf::Font* font, Vec2f position, uint32_t characterSize);
	SimpleButton(Vec2f position, float_t radius, bool leftTri);
	~SimpleButton();
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	void Update();
	void HandleEvents(sf::RenderWindow* window, sf::Event* event);
	inline bool IsPressed() const { return m_Pressed; }
private:
	bool MouseOnButton(sf::RenderWindow* window);

private:
	bool m_Pressed;
	bool m_IsTriangle;
	sf::Text m_Text;
	sf::CircleShape m_TriangleShape;
	uint32_t m_CharacterSize;
	float_t m_Radius;
};
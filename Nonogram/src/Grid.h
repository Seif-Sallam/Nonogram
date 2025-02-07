#pragma once
#include <vector>
#include <iostream>
#include "Vec2.h"
#include "SFML/Graphics.hpp"

enum class TileState
{
	White = 0,
	Black,
	Crossed
};

class Grid : public sf::Drawable
{
public:
	Grid(Vec2u size, Vec2f offset, sf::RenderWindow *window, const std::vector<TileState> &gridStates);
	~Grid();
	Vec2u GetSize() const;
	int32_t GetNumberOfPLacedTiles() const;
	void PollEvents(sf::Event *event);
	void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;
	const std::vector<TileState> &GetCurrentState();
	void Reset();

private:
	void MarkTile(uint32_t index, TileState tileState);
	std::vector<sf::Sprite> m_Grid;
	sf::RenderWindow *m_Window;
	sf::Texture m_TileTextures;
	Vec2u m_Size;
	Vec2f m_Offset;
	std::vector<TileState> m_CurrentStates;
	const std::vector<TileState> m_InitialStates;
	int32_t m_PlacedTiles;
};
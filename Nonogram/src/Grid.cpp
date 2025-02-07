#include "Grid.h"

Grid::Grid(Vec2u size, Vec2f offset, sf::RenderWindow *window, const std::vector<TileState> &gridStates)
	: m_InitialStates(gridStates)
{
	m_TileTextures.loadFromFile(RSC_DIR "Tiles.png");
	m_Grid.resize(size.x * size.y);
	m_CurrentStates.resize(size.x * size.y);
	for (int32_t i = 0; i < size.x; i++)
		for (int32_t j = 0; j < size.y; j++)
		{
			uint32_t index = i + j * size.x;
			m_Grid[index].setPosition(sf::Vector2f(offset.x + i * 32.0f, offset.y + j * 32.0f));
			Vec2f v = m_Grid[index].getPosition();
			m_Grid[index].setTexture(m_TileTextures);
			MarkTile(index, gridStates[index]);
			m_CurrentStates[index] = gridStates[index];
		}
	m_Window = window;
	m_Size = size;
	m_Offset = offset;
	m_PlacedTiles = 0;
}

Grid::~Grid()
{
}

void Grid::MarkTile(uint32_t index, TileState tileState)
{
	m_Grid[index].setTextureRect(sf::IntRect(sf::Vector2i(int32_t(tileState) * 32, 0), sf::Vector2i(32, 32)));
}

Vec2u Grid::GetSize() const
{
	return m_Size;
}

void Grid::PollEvents(sf::Event *event)
{
	Vec2i mousePos = m_Window->mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition(*m_Window)));
	Vec2f pos = Vec2f(mousePos.x - m_Offset.x, mousePos.y - m_Offset.y);

	uint32_t x = int(pos.x / 32.0f);
	uint32_t y = int(pos.y / 32.0f);
	uint32_t index = x + y * int(m_Size.x);
	if (pos.x > -1 && pos.y > -1 && x < m_Size.x && y < m_Size.y)
	{
		if (index < m_Size.x * m_Size.y && index >= 0)
		{
			if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
			{
				if (m_CurrentStates[index] == TileState::Black)
				{
					MarkTile(index, TileState::White);
					m_CurrentStates[index] = TileState::White;
					m_PlacedTiles -= 1;
				}
				else
				{
					MarkTile(index, TileState::Black);
					m_CurrentStates[index] = TileState::Black;
					m_PlacedTiles += 1;
				}
			}
			else if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Right)
			{
				if (m_CurrentStates[index] == TileState::Crossed)
				{
					MarkTile(index, TileState::White);
					m_CurrentStates[index] = TileState::White;
				}
				else if (m_CurrentStates[index] == TileState::Black)
				{
					m_PlacedTiles -= 1;
					MarkTile(index, TileState::Crossed);
					m_CurrentStates[index] = TileState::Crossed;
				}
				else
				{
					MarkTile(index, TileState::Crossed);
					m_CurrentStates[index] = TileState::Crossed;
				}
			}
		}
	}
}

int32_t Grid::GetNumberOfPLacedTiles() const
{
	return m_PlacedTiles;
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (uint32_t i = 0; i < m_Size.x; i++)
		for (uint32_t j = 0; j < m_Size.y; j++)
		{
			uint32_t index = i + j * int(m_Size.x);
			m_Window->draw(m_Grid[index], states);
		}
}

const std::vector<TileState> &Grid::GetCurrentState()
{
	return m_CurrentStates;
}

void Grid::Reset()
{
	for (uint32_t i = 0; i < m_Size.x; i++)
	{
		for (uint32_t j = 0; j < m_Size.y; j++)
		{
			uint32_t index = i + j * m_Size.x;
			MarkTile(index, m_InitialStates[index]);
			m_CurrentStates[index] = m_InitialStates[index];
		}
	}
	m_PlacedTiles = 0;
}

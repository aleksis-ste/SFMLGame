#include "TileMap.h"
#include <iostream>

bool TileMap::load(const std::string& tileset, const int* level, unsigned int width, unsigned int height)
{
	if (!m_tileset.loadFromFile(tileset))
		return false;

	rect.width = 32;
	rect.height = 32;

	length = width * height;

	tiles = new Tile[length];

	int tileNumber = 0;

	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			tiles[tileNumber].setPosition(sf::Vector2f(32 * i, 32 * j));
			rect.left = 32 * level[tileNumber];
			tiles[tileNumber].setTexture(m_tileset, rect, level[tileNumber]);

			tileNumber++;
		}
	}

	return true;
}

void TileMap::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < length; i++)
	{
		window.draw(tiles[i].getShape());
	}
}

int TileMap::getLength()
{
	return length;
}

sf::Texture TileMap::getTexture()
{
	return m_tileset;
}

Tile *TileMap::getTiles()
{
	return tiles;
}

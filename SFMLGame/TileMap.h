#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class TileMap
{

private:
	Tile *tiles;
	sf::Texture m_tileset;
	sf::IntRect rect;
	int length;

public:
	bool load(const std::string& tileset, const int* tiles, unsigned int width, unsigned int height);
	void draw(sf::RenderWindow &window);
	int getLength();
	sf::Texture getTexture();
	Tile *getTiles();
};

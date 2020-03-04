#include "Tile.h"

Tile::Tile()
{
	shape.setSize(sf::Vector2f(32, 32));
}

void Tile::setPosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
}

sf::RectangleShape Tile::getShape()
{
	return this->shape;
}

void Tile::setTexture(sf::Texture &t, sf::IntRect &rect, int level)
{
	shape.setTexture(&t);
	shape.setTextureRect(rect);
	this->level = level;
}

int Tile::getLevel()
{
	return level;
}

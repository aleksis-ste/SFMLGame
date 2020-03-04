#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
private:
	sf::RectangleShape shape;
	int level;

public:
	Tile();
	void setPosition(sf::Vector2f pos);
	sf::RectangleShape getShape();
	void setTexture(sf::Texture &t, sf::IntRect &rect, int level);
	int getLevel();
};


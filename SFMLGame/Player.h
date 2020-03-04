#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Player
{
private:
	int id = -1;
	std::string username;
	sf::Texture texture;
	sf::IntRect rectSourceSprite;
	sf::RectangleShape sprite;
	sf::Clock clock;
	sf::Clock timeInAir;
	sf::Clock mineTime;
	sf::Texture tileset;

public:
	Player(int id, std::string &username);
	Player(std::string &username);
	void update(sf::Vector2f pos);
	void draw(sf::RenderWindow &render);
	void move(sf::Vector2f &pos);
	void setPos(sf::Vector2f pos);
	void animation(sf::Vector2f &direction, bool &mine);
	std::string getUsername();
	void setUsername(std::string username);
	void setId(int id);
	int getId();
	Tile *collideWithOre(TileMap &map, sf::Vector2f &currentVelocity);
	void mine(TileMap &map, sf::Vector2f &currentVelocity, sf::Vector2f &direction, bool &mine);
	void resetClock();
	bool collision(TileMap &map, sf::Vector2f &currentVelocity);
	sf::RectangleShape getSprite();
};


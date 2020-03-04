#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h" 
#include <iostream>
#include "Network.h"

class Client
{
private:
	sf::RenderWindow *window;
	Player *player;
	std::vector<Player> players;
	Network *client;

public:
	Client();
	void render();
};


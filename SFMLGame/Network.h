#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include <iostream>
#include <string>

class Network
{
private:
	sf::UdpSocket client;
	sf::IpAddress ip;
	unsigned short bindPort = 12345;
	Player *player;
	std::vector<Player> *players;
	const double version = 0.11;
	sf::Clock sendClock;
	int playerId;
	bool connected = false;


public:
	Network(Player *p, std::vector<Player> &players);
	void send(unsigned short type);
	void receiveMessages();

	void updatePlayer(int id, float x, float y);
	void sendUpdate();
};


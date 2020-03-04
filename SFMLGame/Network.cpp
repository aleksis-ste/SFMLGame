#include "Network.h"

enum
{
	CONNECT = 0,
	DISCONNECT = 1,
	UPDATE = 2,
	CONNECTED = 3,
	DISCONNECTED = 4
};

Network::Network(Player *p, std::vector<Player> &players)
{
	this->player = p;
	this->players = &players;
	ip = sf::IpAddress("play.brog.pro");

	std::cout << "Ievadiet lietotajvardu:";
	std::string username;
	std::cin >> username;
	player->setUsername(username);

	client.bind(sf::UdpSocket::AnyPort, sf::IpAddress::Any);

	sf::Thread receive(&Network::receiveMessages, this);
	receive.launch();

	std::cout << "Connecting...";
	while (!connected)
	{
		if (sendClock.getElapsedTime().asMilliseconds() > 100)
		{
			std::cout << ".";
			Network::send(CONNECT);
			sendClock.restart();
		}
	}
	std::cout << std::endl;

	sf::Thread u(&Network::sendUpdate, this);
	u.launch();
}

void Network::send(unsigned short type)
{
	sf::Packet data;
	data.clear();
	if(type == CONNECT)
		data << (int)type << version << player->getUsername() << (int)255 << (int)255 << (int)255;
	else if(type == UPDATE)
		data << (int)type << playerId << (float)player->getSprite().getPosition().x << (float)player->getSprite().getPosition().y;

	client.send(data, ip, bindPort);
}

void Network::receiveMessages()
{
	sf::IpAddress receivedAddress;
	sf::Packet packet;
	unsigned short receivedPort;
	int action;

	int id;
	std::string username;
	float x, y;

	while (true)
	{
		packet.clear();
		client.receive(packet, receivedAddress, receivedPort);

		packet >> action;

		switch (action)
		{
		case CONNECT:
			connected = true;
			packet >> playerId;
			player->setId(playerId);
			std::cout << "My id on server: " << player->getId() << std::endl;

		break;

		case CONNECTED:
			packet >> id >> username;
			players->push_back(Player(id, username));
			std::cout << "Player id: " << id << ", username: " << username << " joined" << std::endl;

		break;

		case DISCONNECT:

		break;

		case UPDATE:
			packet >> id >> x >> y;
			Network::updatePlayer(id, x, y);
		break;
		}

	}
}

void Network::updatePlayer(int id, float x, float y) {
	std::cout << "updated: " << id << std::endl;
	for (auto i = players->begin(); i != players->end(); ++i) {
		if (i->getId() == id) {
			i->setPos({ x, y });
		}
	}
}

void Network::sendUpdate()
{
	//while (true)
	//{
	//	if (sendClock.getElapsedTime().asSeconds() > 1.f)
	//	{
	//		std::cout << "sent" << std::endl;
	//		send(UPDATE);
	//		sendClock.restart();
	//	}
	//}
}




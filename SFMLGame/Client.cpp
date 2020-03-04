#include "Client.h"

Client::Client()
{
	sf::Thread render(&Client::render, this);
	render.launch();

	std::string username = "Aleksis";

	player = new Player(username);

	client = new Network(player, players);
	
	while (true);
}

void ResizeView(sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(480 * aspectRatio, 480);
}

void Client::render()
{
	window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[4], "Game Demo", sf::Style::Resize);

	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(720.f, 480.f));

	const int level[] =
	{
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,13,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,13,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,13,1,1,1,1,1,1,13,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,13,1,1,1,1,1,1,13,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,11,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,11,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,
	};

	TileMap map;
	map.load("tileset.png", level, 46, 24);

	//Gravity Variables:
	sf::Vector2f currentVelocity;
	sf::Vector2f direction;
	float maxVelocity = 5.f;
	float acceleration = 1.5f;
	float drag = 0.5f;
	sf::Clock timeInAir;

	//
	bool mine = false;
	bool jump = false;

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			if (event.type == sf::Event::Resized)
			{
				ResizeView(*window, view);
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (sf::Keyboard::E)
					mine = false;
			}
		}

		direction = sf::Vector2f(0.f, 0.f);
		if(window->hasFocus()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				direction.x = -1.f;

				if (currentVelocity.x > -maxVelocity)
					currentVelocity.x += acceleration * direction.x;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				direction.x = 1.f;

				if (currentVelocity.x < maxVelocity)
					currentVelocity.x += acceleration * direction.x;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jump)
			{
				direction.y = -5.f;
				jump = true;

				timeInAir.restart();

				if (currentVelocity.y > -maxVelocity)
					currentVelocity.y += acceleration * direction.y;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && player->collideWithOre(map, currentVelocity) != nullptr)
			{
				if (!mine)
					player->resetClock();

				player->mine(map, currentVelocity, direction, mine);

				mine = true;
				jump = true;
			}
		}

		//Drag
		if (currentVelocity.x > 0.f)
		{
			currentVelocity.x -= drag;

			if (currentVelocity.x < 0.f)
				currentVelocity.x = 0.f;
		}
		else if (currentVelocity.x < 0.f)
		{
			currentVelocity.x += drag;

			if (currentVelocity.x > 0.f)
				currentVelocity.x = 0.f;
		}
		if (currentVelocity.y > 0.f)
		{
			currentVelocity.y -= drag;

			if (currentVelocity.y < 0.f)
				currentVelocity.y = 0.f;
		}
		else if (currentVelocity.y < 0.f)
		{
			currentVelocity.y += drag;

			if (currentVelocity.y > 0.f)
				currentVelocity.y = 0.f;
		}

		if (jump && timeInAir.getElapsedTime().asSeconds() > 0.3f)
		{
			if (!player->collision(map, currentVelocity))
			{
				direction.y = 1.f;

				if (currentVelocity.y > -maxVelocity)
					currentVelocity.y += acceleration * direction.y;
			}
			else
			{
				jump = false;
			}
		}

		player->collision(map, currentVelocity);

		player->animation(direction, mine);

		player->move(currentVelocity);
		view.setCenter(player->getSprite().getPosition());

		window->clear();
		window->setView(view);
		map.draw(*window);
		player->draw(*window);
		for (auto i = players.begin(); i != players.end(); ++i) {
			i->draw(*window);
		}

		// end the current frame
		window->display();
	}
}


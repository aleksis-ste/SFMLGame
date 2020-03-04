#include "Player.h"
#include <iostream>

Player::Player(int id, std::string &username)
{
	this->id = id;
	this->username = username;

	if (!texture.loadFromFile("sprite.png"))
		std::cout << "Neizdevas ieladet failu! sprite.png" << std::endl;

	rectSourceSprite.width = 32;
	rectSourceSprite.height = 32;
	rectSourceSprite.left = 64;
	sprite.setSize({ 32.f, 32.f });
	sprite.setPosition({ 288, 320 });
	sprite.setTexture(&texture);
	sprite.setTextureRect(rectSourceSprite);
}

Player::Player(std::string &username)
{
	this->id = id;
	this->username = username;

	if (!texture.loadFromFile("sprite.png"))
		std::cout << "Neizdevas ieladet failu! sprite.png" << std::endl;

	rectSourceSprite.width = 32;
	rectSourceSprite.height = 32;
	rectSourceSprite.left = 64;
	sprite.setSize({ 32.f, 32.f });
	sprite.setPosition({ 288, 320 });
	sprite.setTexture(&texture);
	sprite.setTextureRect(rectSourceSprite);

	if(!tileset.loadFromFile("tileset.png"))
		std::cout << "Neizdevas ieladet failu! tileset.png" << std::endl;
}

void Player::update(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::draw(sf::RenderWindow &render)
{
	render.draw(this->sprite);
}

void Player::move(sf::Vector2f &pos)
{
	this->sprite.setPosition(sprite.getPosition().x + pos.x, sprite.getPosition().y + pos.y);
}

void Player::setPos(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Player::animation(sf::Vector2f &direction, bool &mine)
{
	if (!mine && direction.x != 0)
	{
		if (clock.getElapsedTime().asSeconds() > 0.1f) 
		{
			if (direction.x < 0)
				rectSourceSprite.top = 0;
			else
				rectSourceSprite.top = 32;

			if (rectSourceSprite.left == 0)
				rectSourceSprite.left = 64;
			else
				rectSourceSprite.left -= 32;

			sprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}
	}
}

std::string Player::getUsername()
{
	return this->username;
}

void Player::setUsername(std::string username)
{
	this->username = username;
}

void Player::setId(int id)
{
	this->id = id;
}

int Player::getId()
{
	return this->id;
}

Tile *Player::collideWithOre(TileMap &map, sf::Vector2f &currentVelocity)
{
	sf::FloatRect nextPos;
	Tile *tiles = map.getTiles();

	for (int i = 0; i < map.getLength(); i++)
	{
		sf::FloatRect playerBounds = this->getSprite().getGlobalBounds();
		sf::FloatRect objectBounds = tiles[i].getShape().getGlobalBounds();

		nextPos = playerBounds;
		nextPos.left += currentVelocity.x;
		nextPos.top += currentVelocity.y + 0.5f;

		if (objectBounds.intersects(nextPos) && (tiles[i].getLevel() == 9 || tiles[i].getLevel() == 10 || tiles[i].getLevel() == 11 || tiles[i].getLevel() == 13)) {
			return &tiles[i];
		}
	}

	return nullptr;
}

void Player::mine(TileMap &map, sf::Vector2f &currentVelocity, sf::Vector2f &direction, bool &mine)
{
	if (clock.getElapsedTime().asSeconds() > 0.1f)
	{
		if (direction.x != 0)
		{
			if (direction.x < 0)
				rectSourceSprite.top = 0;
			else
				rectSourceSprite.top = 32;
		}

		if (rectSourceSprite.left <= 96)
			rectSourceSprite.left = 160;
		else
			rectSourceSprite.left -= 32;

		sprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
	if (mineTime.getElapsedTime().asSeconds() > 1.f)
	{
		sf::IntRect rect(32,0,32,32);

		rect.left = 32 * 3;
		rect.top = 0;
		rect.width = 32;
		rect.height = 32;

		this->collideWithOre(map, currentVelocity)->setTexture(tileset, rect, 3);
		mine = false;
	}
}

void Player::resetClock()
{
	mineTime.restart();
}

bool Player::collision(TileMap &map, sf::Vector2f &currentVelocity)
{
	sf::FloatRect nextPos;
	Tile *tiles = map.getTiles();

	bool collide = false;

	for (int i = 0; i < map.getLength(); i++)
	{
		sf::FloatRect playerBounds = this->getSprite().getGlobalBounds();
		sf::FloatRect objectBounds = tiles[i].getShape().getGlobalBounds();

		nextPos = playerBounds;
		nextPos.left += currentVelocity.x;
		nextPos.top += currentVelocity.y;

		if (objectBounds.intersects(nextPos) && tiles[i].getLevel() != 1) {

			//Top collision
			if (playerBounds.top > objectBounds.top
				&& playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height
				&& playerBounds.left < objectBounds.left + objectBounds.width
				&& playerBounds.left + playerBounds.width > objectBounds.left) {
				currentVelocity.y = 0.f;
				this->setPos({ playerBounds.left, objectBounds.top + objectBounds.height + 0.1f });
			}

			//Bottom collision
			if (playerBounds.top < objectBounds.top
				&& playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height
				&& playerBounds.left < objectBounds.left + objectBounds.width
				&& playerBounds.left + playerBounds.width > objectBounds.left) {
				currentVelocity.y = 0.f;
				this->setPos({ playerBounds.left, objectBounds.top - objectBounds.height - 0.1f });
			}

			//Right collision
			if (playerBounds.left < objectBounds.left
				&& playerBounds.left + playerBounds.width < objectBounds.left
				&& playerBounds.top < objectBounds.top + objectBounds.height
				&& playerBounds.top + playerBounds.height > objectBounds.top) {
				currentVelocity.x = 0.f;
				this->setPos({ objectBounds.left - objectBounds.width - 0.1f, playerBounds.top });
			}

			//Left collision
			if (playerBounds.left > objectBounds.left
				&& playerBounds.left + playerBounds.width > objectBounds.left
				&& playerBounds.top < objectBounds.top + objectBounds.height
				&& playerBounds.top + playerBounds.height > objectBounds.top) {
				currentVelocity.x = 0.f;
				this->setPos({ objectBounds.left + objectBounds.width + 0.1f, playerBounds.top });
			}

			collide = true;
		}
	}
	return collide;
}

sf::RectangleShape Player::getSprite()
{
	return this->sprite;
}


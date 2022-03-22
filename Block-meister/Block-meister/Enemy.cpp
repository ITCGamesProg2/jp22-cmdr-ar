#include "Enemy.h"
sf::RenderWindow* Enemy::window = nullptr;
Player* Enemy::player = nullptr;

Enemy::Enemy()
{
}

void Enemy::SetTexture(const char* path)
{
	tex.loadFromFile(path);
	body.setTexture(tex);
}

void Enemy::processEvents(sf::Event& ev)
{
}

void Enemy::update(sf::Time& dt)
{
}

void Enemy::render()
{
	window->draw(body);
}

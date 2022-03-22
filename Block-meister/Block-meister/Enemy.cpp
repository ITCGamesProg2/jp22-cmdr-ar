#include "Enemy.h"

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

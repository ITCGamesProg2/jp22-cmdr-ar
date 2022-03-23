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

void Enemy::SetTexture(EnemyType _type)
{
	type = _type;
	switch (_type)
	{
	case EnemyType::Slime:
		tex.loadFromFile("resources/images/game/enemies/slime/slime.png");
		break;
	default:
		tex.loadFromFile("resources/images/game/enemies/slime/slime.png");
		break;
	}
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

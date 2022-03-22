#include "AttackEntity.h"
sf::RenderWindow* AttackEntity::window = nullptr;
Player* AttackEntity::player = nullptr;

AttackEntity::AttackEntity()
{
	tex.loadFromFile("resources/images/game/player/sword.png");
	body.setTexture(tex);
	body.setScale(3, 3);
	body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height);

}

void AttackEntity::processEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::Space == ev.key.code)
		{
			if (!isAttacking)
			{
				isAttacking = true;
				attackDirSet = false;
				readyToDraw = false;
				attackTimer.restart();
			}
		}
	}
}

void AttackEntity::update(sf::Time& dt)
{
	if (attackTimer.getElapsedTime().asSeconds() > 0.25f) isAttacking = false;

	if (isAttacking)
	{
		if (!attackDirSet)
			setAttackPos();
		else
			animateAttack(dt);
	}
}

void AttackEntity::render()
{
	if (isAttacking)
	{
		if (readyToDraw) window->draw(body);
	}
}

void AttackEntity::setAttackPos()
{
	sf::Vector2f playerPos = player->getSprite().getPosition();
	float playerHeight = player->getSprite().getLocalBounds().height;
	float playerWidth = player->getSprite().getLocalBounds().width;
	
	if (firstTime)
	{
		prevDir = sf::Vector2f(0, -playerHeight);
		prevRotation = 270.f;
		firstTime = false;
	}

	switch (player->getDir())
	{
	case Direction::Up:
		offset = sf::Vector2f(0, -playerHeight);
		rotation = 270.f;
		break;
	case Direction::Right:
		offset = sf::Vector2f(playerWidth, 0);
		rotation = 0.f;
		break;
	case Direction::Down:
		offset = sf::Vector2f(0, playerHeight);
		rotation = 90.f;
		break;
	case Direction::Left:
		offset = sf::Vector2f(-playerWidth, 0);
		rotation = 180.f;
		break;
	default:
		offset = prevDir;
		rotation = prevRotation;
		break;
	}
	
	prevDir = offset;
	prevRotation = rotation;

	body.setRotation(rotation);
	body.setPosition(playerPos + (offset));
	if (attackTimer.getElapsedTime().asSeconds() > 0.05f) attackDirSet = true;
	readyToDraw = true;
}

void AttackEntity::animateAttack(sf::Time& dt)
{
	sf::Vector2f playerPos = player->getSprite().getPosition();
	body.setPosition(playerPos + (offset));
	body.rotate(900.f * dt.asSeconds());
}

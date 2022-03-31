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
	sf::Vector2f dir = player->getSprite().getPosition() - MousePosition::GetOffGrid();

	rotation = atan2(dir.y, dir.x) * 180.f / 3.1415f/* PI */;
	offset = sf::Vector2f(cos(rotation * 3.1416 / 180), sin(rotation * 3.1416 / 180)) * -50.f;

	body.setRotation(rotation + 180.f);
	body.setPosition(player->getSprite().getPosition() + (offset));
	if (attackTimer.getElapsedTime().asSeconds() > 0.05f) attackDirSet = true;
	readyToDraw = true;
}

void AttackEntity::animateAttack(sf::Time& dt)
{
	sf::Vector2f playerPos = player->getSprite().getPosition();
	body.setPosition(playerPos + (offset));
	body.rotate(900.f * dt.asSeconds());
}

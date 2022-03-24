#include "RangedAttackEntity.h"

sf::RenderWindow* RangedAttackEntity::window = nullptr;
Player* RangedAttackEntity::player = nullptr;
sf::Clock RangedAttackEntity::attackTimer;
int RangedAttackEntity::currentAttack = 0;

RangedAttackEntity::RangedAttackEntity()
{
	tex.loadFromFile("resources/images/game/player/sword.png");
	body.setTexture(tex);
	body.setScale(1.5, 1.5);
	body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height);

}

void RangedAttackEntity::processEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::Q == ev.key.code)
		{
			if (!active &&
				attackTimer.getElapsedTime().asSeconds() > timeBetweenAttacks)
			{
				body.setPosition(player->getPos());
				active = true;
				calculateDirection(getMousePosition(*window));

				currentAttack++;
				if (currentAttack >= MAX_ATTACKS)
				{
					currentAttack = 0;
				}
				attackTimer.restart();
			}
		}
	}
}

void RangedAttackEntity::update(sf::Time& dt)
{
	if (active)
	{
		body.move(direction * speed * dt.asSeconds());
		boundsCollision(dt);
	}
}

void RangedAttackEntity::render()
{
	if (active)
	{
		window->draw(body);
	}
}

sf::Vector2f RangedAttackEntity::getMousePosition(sf::RenderWindow& t_window)
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(t_window).x;
	m_mousePosition.y = (float)sf::Mouse::getPosition(t_window).y;

	return m_mousePosition;
}

void RangedAttackEntity::calculateDirection(sf::Vector2f t_mousePos)
{
	direction = t_mousePos - player->getPos();
	float vectorLength = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction = direction / vectorLength;

	float angle = atan2(t_mousePos.y - player->getPos().y, t_mousePos.x - player->getPos().x);
	angle = angle * 180 / 3.1416;
	body.setRotation(angle + 90);
}


void RangedAttackEntity::boundsCollision(sf::Time& dt)
{
	//Left Side Bounds
	if (body.getPosition().x < 0)
	{
		active = false;
	}
	//Right Side Bounds
	if (body.getPosition().x > Window::WIDTH)
	{
		active = false;
	}
	//Top Side Bounds
	if (body.getPosition().y < 0)
	{
		active = false;
	}
	//Bottom Side Bounds
	if (body.getPosition().y > Window::HEIGHT)
	{
		active = false;
	}
}
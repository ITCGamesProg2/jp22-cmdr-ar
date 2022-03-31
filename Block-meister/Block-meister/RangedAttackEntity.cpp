#include "RangedAttackEntity.h"

sf::RenderWindow* RangedAttackEntity::window = nullptr;
Player* RangedAttackEntity::player = nullptr;
sf::Clock RangedAttackEntity::attackTimer;

RangedAttackEntity::RangedAttackEntity()
{
	tex.loadFromFile("resources/images/game/player/sword.png");
	body.setTexture(tex);
	body.setScale(1.5, 1.5);
	body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height);
}


void RangedAttackEntity::update(sf::Time& dt)
{
	if (active)
	{
		body.move(direction * speed * dt.asSeconds());
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

void RangedAttackEntity::calculateDirection(sf::Vector2f t_mousePos, sf::Vector2f t_start)
{
	t_mousePos.x += (window->getView().getCenter().x) - (window->getView().getSize().x / 2);
	t_mousePos.y += (window->getView().getCenter().y) - (window->getView().getSize().y / 2);

	direction = t_mousePos - t_start;
	float vectorLength = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction = direction / vectorLength;

	float angle = atan2(t_mousePos.y - player->getPos().y, t_mousePos.x - player->getPos().x);
	angle = angle * 180.f / 3.1416f;
	body.setRotation(angle + 90);
}


/// <summary>
/// Enemy Projectile Activation
/// </summary>
/// <param name="t_position"></param>
/// <param name="t_direction"></param>
void RangedAttackEntity::activateProjectile(sf::Vector2f t_position, sf::Vector2f t_direction)
{
	body.setPosition(t_position);
	active = true;
	direction = t_direction;

	attackTimer.restart();
}

/// <summary>
/// Player Projectile Activation
/// </summary>
/// <param name="t_position"></param>
void RangedAttackEntity::activateProjectile(sf::Vector2f t_position)
{
	if (!active &&
		attackTimer.getElapsedTime().asSeconds() > timeBetweenAttacks)
	{
		body.setPosition(t_position);
		active = true;
		calculateDirection(getMousePosition(*window), player->getPos());
		player->damageSelf();

		attackTimer.restart();
	}
}

void RangedAttackEntity::changeTex(const char* t_path)
{
	tex.loadFromFile(t_path);
	body.setTexture(tex);
	body.setTextureRect({ 0,0,10,10 });
	body.setScale(1.5, 1.5);
	body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
}

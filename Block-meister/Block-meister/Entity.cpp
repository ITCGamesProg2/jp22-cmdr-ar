#include "Entity.h"
sf::RenderWindow* Entity::window = nullptr;
Player* Entity::player = nullptr;

Entity::Entity()
{
	SetTexture("resources/images/game/heart.png");
}

void Entity::SetTexture(const char* path)
{
	tex.loadFromFile(path);
	body.setTexture(tex);
	body.setOrigin((body.getLocalBounds().width / 2), (body.getLocalBounds().height / 2));
}

void Entity::processEvents(sf::Event& ev)
{
}

void Entity::update(sf::Time& dt)
{
}

void Entity::render()
{
	if (active)
	{
		window->draw(body);
	}
}

void Entity::spawn(sf::Vector2f t_pos)
{
	active = true;
	body.setPosition(t_pos);
}

void Entity::heal()
{
	if (active)
	{
		player->heal(HEAL_VALUE);
	}
	active = false;
}

void Entity::setType(EntityType t_type)
{
	type = t_type;
}

#include "Entity.h"
sf::RenderWindow* Entity::window = nullptr;
Player* Entity::player = nullptr;

Entity::Entity()
{
}

void Entity::SetTexture(const char* path)
{
	tex.loadFromFile(path);
	body.setTexture(tex);
}

void Entity::processEvents(sf::Event& ev)
{
}

void Entity::update(sf::Time& dt)
{
}

void Entity::render()
{
	window->draw(body);
}

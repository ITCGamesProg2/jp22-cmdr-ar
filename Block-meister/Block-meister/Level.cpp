#include "Level.h"

Level::Level(sf::RenderWindow& t_window)
	: window{ &t_window }, player{ t_window }
{
	loadLevel(0);
	Entity::window = &t_window;
	Entity::player = &player;
}

void Level::loadLevel(int no)
{
	
}

void Level::processEvents(sf::Event& ev)
{
	player.processEvents(ev);
}

void Level::update(sf::Time& dt)
{
	player.update(dt);
}

void Level::render()
{
	window->clear(sf::Color::Black);

	for (Entity& e : objects)
	{
		e.render();
	}
	player.render();

	window->display();
}

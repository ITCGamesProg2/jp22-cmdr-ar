#include "Level.h"

Level::Level(sf::RenderWindow& t_window)
	: window{ &t_window }, player{ t_window }
{
	loadLevel(0);
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

	player.render();

	window->display();
}

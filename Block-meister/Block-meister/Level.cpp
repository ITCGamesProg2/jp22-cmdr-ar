#include "Level.h"

Level::Level(sf::RenderWindow& t_window)
	: window{ &t_window }, player{ t_window }
{
	loadLevel(0);
	object.SetWindowPtr(t_window);
}

void Level::loadLevel(int no)
{
	object.SetPlayerPtr(player);
	object.SetTexture("resources/images/game/yoda.png");
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

	object.render();
	player.render();

	window->display();
}

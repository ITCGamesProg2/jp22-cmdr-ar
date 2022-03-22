#include "Level.h"

Level::Level(sf::RenderWindow& t_window)
	: window{ &t_window }, player{ t_window }
{
	loadLevel(0);
	Entity::window = &t_window;
	Entity::player = &player;
	Terrain::window = &t_window;
}

void Level::loadLevel(int no)
{
	
}

void Level::processEvents(sf::Event& ev)
{
	player.processEvents(ev);
	editor.processEvents(ev);

	if (ev.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::Space == ev.key.code)
		{
			createTerrain();
		}
	}
}

void Level::update(sf::Time& dt)
{
	player.update(dt);
	editor.update(*window);
	checkCollisions();
}

void Level::render()
{
	window->clear(sf::Color::Black);

	for (Entity& e : entities)
	{
		e.render();
	}
	for (Terrain& e : terrain)
	{
		e.render();
	}
	player.render();

	window->display();
}

void Level::createTerrain()
{
	Terrain wall;

	switch (editor.getDesiredType())
	{
	case 1:
		wall.setType(Type::wall);
		wall.setPos(editor.getMouse());
		wall.SetTexture("./resources/images/game/yoda.png");
		terrain.push_back(wall);
		break;
	default:
		break;
	}
}

void Level::checkCollisions()
{
	collision.collisionDetection(player, terrain);
}

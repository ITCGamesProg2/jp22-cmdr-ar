#include "Level.h"

Level::Level(sf::RenderWindow& t_window)
	: window{ &t_window }, player{ t_window }
{
	loadLevel(0);
	Entity::window = &t_window;
	Entity::player = &player;
	Terrain::window = &t_window;

	//Outline for editor placement
	outline.setSize({ 100,100 });
	outline.setFillColor(sf::Color::Green);
	outline.setOrigin(50, 50);

	//Mouse bounds
	mouseBounds.setSize(sf::Vector2f{ 1, 1 });
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
		if (sf::Keyboard::Space == ev.key.code &&
			outline.getFillColor() == sf::Color::Green)
		{
			createTerrain();
		}
	}
	if (ev.type == sf::Event::MouseButtonPressed)
	{
		if (sf::Mouse::Right == ev.key.code)
		{
			int x = collision.selectTerrain(mouseBounds, terrain);
			if (x != -1)
			{
				std::vector<Terrain>::const_iterator i = terrain.begin() + x;
				terrain.erase(i);
			}
			int count = 0;
			for (Terrain& e : terrain)
			{
				e.setCounter(count);
				count++;
			}
		}
	}
}

void Level::update(sf::Time& dt)
{
	player.update(dt);
	editor.update(*window);
	checkCollisions();
	outline.setPosition(gridPlacement(editor.getMouse()));
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
	if (editor.getEditor())
	{
		window->draw(outline);
	}

	window->display();
}

void Level::createTerrain()
{
	Terrain wall;

	switch (editor.getDesiredType())
	{
	case 1:
		wall.setType(Type::wall);
		wall.setPos(gridPlacement(editor.getMouse()));
		wall.SetTexture("./resources/images/game/yoda.png");
		terrain.push_back(wall);
		break;
	default:
		break;
	}

	int count = 0;
	for (Terrain& e : terrain)
	{
		e.setCounter(count);
		count++;
	}
}

void Level::checkCollisions()
{
	mouseBounds.setPosition(editor.getMouse());

	collision.collisionDetection(player, terrain);
	collision.collisionDetection(outline, terrain);
}

void Level::setOutline()
{
	outline.setSize({ 100,100 });
	outline.setFillColor(sf::Color::Green);
	outline.setOrigin(50, 50);
}

sf::Vector2f Level ::gridPlacement(sf::Vector2f mousePosition)
{
	sf::Vector2f mouseGridPlacement;
	mouseGridPlacement.x = (static_cast<int>(mousePosition.x) / 10) * 10;
	mouseGridPlacement.y = (static_cast<int>(mousePosition.y) / 10) * 10;

	return mouseGridPlacement;
}
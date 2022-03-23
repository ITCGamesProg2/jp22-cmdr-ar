#include "Level.h"

Level::Level(sf::RenderWindow& t_window)
	: window{ &t_window }, player{ t_window }
{
	loadLevel(0);
	Entity::window = &t_window;
	Entity::player = &player;
	Terrain::window = &t_window;
	AttackEntity::window = &t_window;
	AttackEntity::player = &player;
	Enemy::window = &t_window;
	Enemy::player = &player;
	
	//Outline for editor placement
	outline.setSize({ 100,100 });
	outline.setFillColor(sf::Color::Green);
	outline.setOrigin(50, 50);

	//Mouse bounds
	mouseBounds.setSize(sf::Vector2f{ 1, 1 });

	//test enemies
	enemies.reserve(1024);
	Enemy slime;
	slime.SetTexture(EnemyType::Slime);
	slime.setPos(10,10);
	enemies.push_back(slime);
	enemies.back().SetTexture(enemies.back().type);
	Enemy slime2;
	slime2.SetTexture(EnemyType::Slime);
	slime2.setPos(100, 10);
	enemies.push_back(slime2);
	enemies.back().SetTexture(enemies.back().type);
	Enemy slime3;
	slime3.SetTexture(EnemyType::Slime);
	slime3.setPos(200, 10);
	enemies.push_back(slime3);
	enemies.back().SetTexture(enemies.back().type);
}

void Level::loadLevel(int no)
{
	
}

void Level::processEvents(sf::Event& ev)
{
	player.processEvents(ev);
	editor.processEvents(ev);
	playerAttack.processEvents(ev);

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

		if (sf::Mouse::Left == ev.key.code &&
			outline.getFillColor() == sf::Color::Green)
		{
			createTerrain();
		}
	}
}

void Level::update(sf::Time& dt)
{
	player.update(dt);
	playerAttack.update(dt);
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
	for (Terrain& t : terrain)
	{
		t.render();
	}
	for (Enemy& e : enemies)
	{
		e.render();
	}
	player.render();
	playerAttack.render();

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
		wall.changeType(Type::wall);
		wall.setPos(gridPlacement(editor.getMouse()));
		terrain.push_back(wall);
		break;
	case 2:
		wall.changeType(Type::ground);
		wall.setPos(gridPlacement(editor.getMouse()));
		terrain.push_back(wall);
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

	// Player and Terrain
	collision.collisionDetection(player, terrain);
	// Player, Terrain and Outline 
	collision.collisionDetection(player, outline, terrain);
}

void Level::setOutline()
{
	outline.setSize({ 100,100 });
	outline.setFillColor(sf::Color::Green);
	outline.setOrigin(50, 50);
}

sf::Vector2f Level::gridPlacement(sf::Vector2f mousePosition)
{
	sf::Vector2f mouseGridPlacement;
	mouseGridPlacement.x = (static_cast<int>(mousePosition.x) / 10) * 10;
	mouseGridPlacement.y = (static_cast<int>(mousePosition.y) / 10) * 10;

	return mouseGridPlacement;
}

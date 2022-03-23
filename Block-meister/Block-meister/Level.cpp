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
	for (int i = 0; i < 3; i++)
	{
		auto slime = std::make_shared<Enemy>();
		slime.get()->SetTexture(EnemyType::Slime);
		slime.get()->setPos(100 * i, 10);
		enemies.push_back(slime);
	}
	
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
			int terrainIndex = collision.selectTerrain(mouseBounds, terrain);
			editor.deleteTerrain(terrain, terrainIndex);
		}

		if (sf::Mouse::Left == ev.key.code &&
			outline.getFillColor() == sf::Color::Green)
		{
			editor.createTerrain(terrain);
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
	for (std::shared_ptr<Enemy> e : enemies)
	{
		e.get()->render();
	}
	player.render();
	playerAttack.render();

	if (m_levelEditor)
	{
		window->draw(outline);
	}

	window->display();
}


void Level::checkCollisions()
{
	mouseBounds.setPosition(editor.getMouse());

	// Player and Terrain
	collision.collisionDetection(player, terrain);
	// Player, Terrain and Outline 
	collision.collisionDetection(player, outline, terrain);
}

void Level::editorOn()
{
	if (!m_levelEditor)
	{
		std::cout << "*anime moans* I-It's n-not like I wanted to edit baka!" << std::endl;
		m_levelEditor = true;
		editor.editorOn();
	}
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

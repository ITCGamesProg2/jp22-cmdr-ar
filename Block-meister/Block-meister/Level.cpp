#include "Level.h"

Level::Level(sf::RenderWindow& t_window)
	: window{ &t_window }, player{ t_window }
{
	Entity::window = &t_window;
	Entity::player = &player;
	Terrain::window = &t_window;
	AttackEntity::window = &t_window;
	AttackEntity::player = &player;
	RangedAttackEntity::window = &t_window;
	RangedAttackEntity::player = &player;
	Enemy::window = &t_window;
	Enemy::player = &player;
	
	//Outline for editor placement
	outline.setSize({ 100,100 });
	outline.setFillColor(sf::Color::Green);
	outline.setOrigin(50, 50);

	outlineFill.setSize({ 90,90 });
	outlineFill.setFillColor(sf::Color::Blue);
	outlineFill.setOrigin(45, 45);

	//Mouse bounds
	mouseBounds.setSize(sf::Vector2f{ 1, 1 });

	//test enemies
	for (int i = 0; i < 3; i++)
	{
		auto slime = std::make_shared<Enemy>();
		slime.get()->SetTexture(EnemyType::Slime);
		slime.get()->setPos(100 * i, 10);
		slime.get()->setScale(2.f,2.f);
		enemies.push_back(slime);
	}

	loadLevel(1);
}

void Level::loadLevel(int no)
{
	editor.editorOn(); // EDITOR ENABLED
	//////////////////////////////////////////////////////////////////////////

	yml.load(no, levelData);
	for (Object& o : levelData.levelData.objects)
	{
		editor.createTerrain(terrain, sf::Vector2f(o.X, o.Y), static_cast<Type>(o.Type));
	}

	//////////////////////////////////////////////////////////////////////////
	editor.editorOff();
	if (m_levelEditor) editor.editorOn(); // EDITOR OFF OR REENABLED
}

void Level::saveLevel(int no)
{
	yml.emittter(no, terrain);
}

void Level::processEvents(sf::Event& ev)
{
	player.processEvents(ev);
	editor.processEvents(ev);
	playerAttack.processEvents(ev);
	playerRangedAttack[RangedAttackEntity::currentAttack].processEvents(ev);

	if (m_levelEditor)
	{
		if (ev.type == sf::Event::MouseButtonPressed)
		{
			// Deleteing Entities
			if (sf::Mouse::Right == ev.key.code)
			{
				// Terrain Mode
				if (editor.getMode() == Mode::terrain)
				{
					int terrainIndex = collision.selectTerrain(mouseBounds, terrain);
					editor.deleteTerrain(terrain, terrainIndex);
				}
				// Enemy Mode
				else if (editor.getMode() == Mode::enemies)
				{

				}
			}
			// Creating Entities
			if (sf::Mouse::Left == ev.key.code &&
				outline.getFillColor() == sf::Color::Green)
			{
				// Terrain Mode
				if (editor.getMode() == Mode::terrain)
				{
					editor.createTerrain(terrain);
				}
				// Enemy Mode
				else if (editor.getMode() == Mode::enemies)
				{
					editor.createEnemy(enemies);
				}
			}
		}
		if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::LControl)
			{
				ctrlDown = true;
			}
			if (ctrlDown)
			{
				if (ev.key.code == sf::Keyboard::S)
				{
					saveLevel(1);
				}
			}
			setOutline();
		}
		if (ev.type == sf::Event::KeyReleased)
		{
			if (ev.key.code == sf::Keyboard::LControl)
			{
				ctrlDown = false;
			}
		}
	}
}

void Level::update(sf::Time& dt)
{
	player.update(dt);
	playerAttack.update(dt);
	for (RangedAttackEntity& e : playerRangedAttack)
	{
		e.update(dt);
	}
	editor.update(*window);
	checkCollisions();
	outline.setPosition(gridPlacement(editor.getMouse()));
	outlineFill.setPosition(outline.getPosition());
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
	for (RangedAttackEntity& e : playerRangedAttack)
	{
		e.render();
	}
	player.render();
	playerAttack.render();

	if (m_levelEditor)
	{
		window->draw(outline);
		window->draw(outlineFill);
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
	switch (editor.getDesiredType())
	{
	case 1:
		outlineFill.setFillColor(sf::Color::Blue);
		break;
	case 2:
		outlineFill.setFillColor(sf::Color::Yellow);
		break;
	default:
		outlineFill.setFillColor(sf::Color::Yellow);
		break;
	}
}

sf::Vector2f Level::gridPlacement(sf::Vector2f mousePosition)
{
	sf::Vector2f mouseGridPlacement;
	mouseGridPlacement.x = (static_cast<int>(mousePosition.x) / 10) * 10;
	mouseGridPlacement.y = (static_cast<int>(mousePosition.y) / 10) * 10;

	return mouseGridPlacement;
}

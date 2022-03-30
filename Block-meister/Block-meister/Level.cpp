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
	Enemy::terrain = &terrain;
	ParticleManager::window = &t_window;
	LevelEditor::terrain = &terrain;
	
	//Outline for editor placement
	outline.setSize({ 50,50 });
	outline.setFillColor(sf::Color::Green);
	outline.setOrigin(25, 25);

	outlineFill.setSize({ 45,45 });
	outlineFill.setFillColor(sf::Color::Blue);
	outlineFill.setOrigin(22.5, 22.5);

	//Mouse bounds
	mouseBounds.setSize(sf::Vector2f{ 1, 1 });

	//test enemies
	auto slime = std::make_shared<Enemy>();
	slime->changeType(EnemyType::Slime);
	slime.get()->setPos(600, 400);
	enemies.push_back(slime);

	loadLevel();
}

void Level::loadLevel()
{
	editor.editorOn(); // EDITOR ENABLED
	//////////////////////////////////////////////////////////////////////////

	yml.load(playerData); // load the player data
	currentLevel = playerData.Level;
	player.setPos(playerData.X, playerData.Y);

	yml.load(currentLevel, levelData); // load the current level


	for (Object& o : levelData.objects)
	{

		std::shared_ptr<Terrain> ter = std::make_shared<Terrain>(editor.createTerrain(sf::Vector2f(o.X, o.Y), static_cast<Type>(o.Type)));
		ter->changeType(ter->getType());
		terrain.push_back(ter);

		int count = 0;

		for (std::shared_ptr<Terrain> t : terrain)
		{
			t->setCounter(count);
			count++;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	editor.editorOff();
	if (m_levelEditor) editor.editorOn(); // EDITOR OFF OR REENABLED

	for (std::shared_ptr<Enemy>& e : enemies)
	{
		e->setupPathing();
	}
}

void Level::saveLevel()
{
	yml.emittter(currentLevel, terrain);
}

void Level::saveGame()
{
	yml.emittter(currentLevel, player.getPos());
}

void Level::processEvents(sf::Event& ev)
{
	player.processEvents(ev);
	editor.processEvents(ev);
	playerAttack.processEvents(ev);
	for (std::shared_ptr<Enemy> e : enemies)
	{
		e->processEvents(ev);
	}
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::V)
		{
		}
	}

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
					std::shared_ptr<Terrain> ter = std::make_shared<Terrain>(editor.createTerrain());
					ter->changeType(ter->getType());
					terrain.push_back(ter);

					int count = 0;

					for (std::shared_ptr<Terrain>& t : terrain)
					{
						t->setCounter(count);
						count++;
					}
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
					saveLevel();
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
	// Outside level editor
	if (ev.type == sf::Event::KeyPressed)
	{
		// Player Ranged Attack
		if (ev.key.code == sf::Keyboard::Q)
		{
			playerRangedAttack->activateProjectile(player.getPos());
			currentPlayerAttack++;
			if (currentPlayerAttack >= RangedAttackEntity::MAX_ATTACKS)
			{
				currentPlayerAttack = 0;
			}
		}
		// Beetle Ranged Test
		if (ev.key.code == sf::Keyboard::B)
		{
			for (std::shared_ptr<Enemy> e : enemies)
			{
				e->beetleReadyup();
			}
		}
	}
}

void Level::update(sf::Time& dt)
{
	checkCollisions();
	player.update(dt);
	playerAttack.update(dt);
	for (RangedAttackEntity& e : playerRangedAttack)
	{
		e.update(dt);
	}
	if (!m_levelEditor)
	{
		for (RangedAttackEntity& e : beetleAttacks)
		{
			e.update(dt);
		}
		for (std::shared_ptr<Enemy> e : enemies)
		{
			e->update(dt);
			//Beetle aiming update loop
			if (e->getBeetleAttacking())
			{
				sf::Vector2f* aimTemp = e->getTriAim();
				for (size_t i = 0; i < RangedAttackEntity::MAX_BEETLE_ATTACKS; i++)
				{
					beetleAttacks[i].activateProjectile(e->getSprite().getPosition(), aimTemp[i]);
				}
				e->resetBeetleAttacking();
			}
		}
	}
	editor.update(*window);
	outline.setPosition(gridPlacement(editor.getMouse()));
	outlineFill.setPosition(outline.getPosition());
	particleManager.update(dt);
}

void Level::render()
{
	window->clear(sf::Color::Black);

	for (Entity& e : entities)
	{
		e.render();
	}
	for (std::shared_ptr<Terrain> t : terrain)
	{
		t->render();
	}
	particleManager.render();
	for (std::shared_ptr<Enemy> e : enemies)
	{
		e.get()->render();
	}
	player.render();
	for (RangedAttackEntity& e : playerRangedAttack)
	{
		e.render();
	}
	for (RangedAttackEntity& e : beetleAttacks)
	{
		e.render();
	}
	playerAttack.render();

	if (m_levelEditor)
	{
		window->draw(outline);
		window->draw(outlineFill);
	}

	{ // FORBIDDEN CODE I AM SORRY - conor
		sf::Vector2f newPos = window->getView().getCenter() - (window->getView().getSize() / 2.f);
		player.health.setPos(newPos.x, newPos.y);
		player.health.render(*window);
	}

	window->display();
}


void Level::checkCollisions()
{
	mouseBounds.setPosition(editor.getMouse());

	//Player and Enemies
	collision.collisionDetection(player, enemies);
	// Player and Terrain
	collision.collisionDetection(player, terrain);
	// Player, Terrain and Outline 
	collision.collisionDetection(player, outline, terrain);
	// Enemies and Terrain
	collision.collisionDetection(terrain, enemies);
	// Enemies and Attack
	collision.collisionDetection(playerAttack, enemies);
	// Enemies and Ranged Attack
	collision.collisionDetection(playerRangedAttack, enemies);

	// Particle Manager
	for (std::shared_ptr<Enemy> e : enemies)
	{
		if (e->getParticleReady())
		{
			particleManager.createParticle(e->enemyType, e->getSprite().getPosition());
		}
	}
	
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

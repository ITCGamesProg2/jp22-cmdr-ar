#include "Level.h"

Level::Level(sf::RenderWindow& t_window)
	: window{ &t_window }, player{ t_window }
{
	Collision::ptrplayer = &player;
	MousePosition::window = &t_window;
	Entity::window = &t_window;
	Entity::player = &player;
	Terrain::window = &t_window;
	Terrain::player = &player;
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

	//player projectiles
	for (RangedAttackEntity& e : playerRangedAttack)
	{
		e.setFriendly(true);
	}
	//beetle projectiles
	for (RangedAttackEntity& e : beetleAttacks)
	{
		e.changeTex("resources/images/game/player/blob.png");
	}

	loadLevel();
}

void Level::TraverseLevel()
{
	if (Terrain::NextLevelReady)
	{
		Terrain::NextLevelReady = false;
		currentLevel++;
		saveGame();
		terrain.clear();
		enemies.clear();
		entities.clear();
		loadLevel();
	}
}

void Level::loadLevel()
{
	editor.editorOn(); // EDITOR ENABLED
	//////////////////////////////////////////////////////////////////////////

	yml.load(playerData); // load the player data
	currentLevel = playerData.Level;
	player.setPos(playerData.X, playerData.Y);

	levelData.enemies.clear();
	levelData.objects.clear();
	yml.load(currentLevel, levelData); // load the current level


	for (Object& o : levelData.objects) // TERRAIN
	{

		std::shared_ptr<Terrain> ter = std::make_shared<Terrain>(editor.createTerrain(sf::Vector2f(o.X, o.Y), static_cast<Block>(o.Type)));
		ter->changeType(ter->getType());
		ter->changeBlock(ter->getBlock());
		terrain.push_back(ter);

		int count = 0;

		for (std::shared_ptr<Terrain> t : terrain)
		{
			t->setCounter(count);
			count++;
		}
	}

	for (EnemyObj& e : levelData.enemies) // ENEMIES
	{

		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->changeType((EnemyType)e.Type);
		enemy->setPos(e.X, e.Y);
		enemies.push_back(enemy);
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
	yml.emittter(currentLevel, terrain, enemies);
}

void Level::saveGame()
{
	yml.emittter(currentLevel, player.getPos());
}

void Level::processEvents(sf::Event& ev)
{
	player.processEvents(ev);
	editor.processEvents(ev);
	if (player.getAlive())
	{
		playerAttack.processEvents(ev);
	}
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
		// Deleteing Entities
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
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
				int enemyIndex = collision.selectEnemy(mouseBounds, enemies);
				editor.deleteEnemy(enemies, enemyIndex);
			}
		}
		// Creating Entities
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// Terrain Mode
			if (editor.getMode() == Mode::terrain && outline.getFillColor() == sf::Color::Green)
			{
				std::shared_ptr<Terrain> ter = std::make_shared<Terrain>(editor.createTerrain());
				ter->changeType(ter->getType());
				ter->changeBlock(ter->getBlock());
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
				std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(editor.createEnemy());
				enemy->changeType(enemy->enemyType);
				enemies.push_back(enemy);

				int count = 0;
				for (std::shared_ptr<Enemy>& t : enemies)
				{
					t->setCounter(count);
					count++;
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
		if (ev.key.code == sf::Keyboard::Q && player.getAlive())
		{
			playerRangedAttack[currentPlayerAttack].activateProjectile(player.getPos());
			currentPlayerAttack++;
			if (currentPlayerAttack >= RangedAttackEntity::MAX_ATTACKS)
			{
				currentPlayerAttack = 0;
			}
		}
		// Test
		if (ev.key.code == sf::Keyboard::B)
		{
		}
	}
}

void Level::update(sf::Time& dt)
{
	checkCollisions();
	player.update(dt);
	if (!player.getAlive() && !savedAfterDeath)
	{
		savedAfterDeath = true;
		yml.emittter(1, sf::Vector2f(300.f, 300.f));
	}
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
		for (std::shared_ptr<Terrain>& t : terrain)
		{
			t->update(dt);
			if (Terrain::NextLevelReady) TraverseLevel();
		}
		for (std::shared_ptr<Enemy>& e : enemies)
		{
			float dist = player.getDistance(e->getSprite().getPosition());
			if (dist < 700.f)
			{
				// Drop health hearts
				if (e->dropHealth())
				{
					std::shared_ptr<Entity> entity = std::make_shared<Entity>();
					entity->setType(EntityType::Heart);
					entity->spawn(e->getSprite().getPosition());
					entities.push_back(entity);
				}
				e->update(dt);
				//Beetle aiming update loop
				if (e->getBeetleAttacking())
				{
					sf::Vector2f* aimTemp = e->getTriAim();
					for (size_t i = 0; i < RangedAttackEntity::MAX_BEETLE_ATTACKS; i++)
					{
						if (currentBeetleAttack >= 50)
						{
							currentBeetleAttack = 0;
						}
						beetleAttacks[currentBeetleAttack].activateProjectile(e->getSprite().getPosition(), aimTemp[i]);
						currentBeetleAttack++;
					}
					e->resetBeetleAttacking();
				}
				//Hive Spawning
				if (e->getSpawnReady())
				{
					bool found = false;
					for (std::shared_ptr<Enemy>& s : enemies)
					{
						if (!s->getAlive() && s->enemyType == EnemyType::Spawn)
						{
							s->spawnReset(e->getSprite().getPosition());
							e->setSpawnReady(false);
							found = true;
						}
					}
					if (!found)
					{
						e->setSpawnReady(false);
						spawnReady = true;
						spawnPos = e->getSprite().getPosition();
					}
				}
				//Particles for hitting hive
				if (e->enemyType == EnemyType::Hive && e->getHiveHit())
				{
					particleManager.createParticle(EnemyType::Hive, e->getSprite().getPosition());
					e->setHiveHit(false);
				}
			}
		}
		if (spawnReady) SpawnSpawn();
	}
	editor.update(*window);
	outline.setPosition(MousePosition::Get());
	outlineFill.setPosition(outline.getPosition());
	particleManager.update(dt);
}

void Level::render()
{
	window->clear(sf::Color::Black);

	for (std::shared_ptr<Terrain>& t : terrain)
	{
		float dist = player.getDistance(t->getPos());
		if (dist < 700.f) t->render();
	}
	for (std::shared_ptr<Entity>& e : entities)
	{
		float dist = player.getDistance(e->getSprite().getPosition());
		if (dist < 700.f) e->render();
	}
	particleManager.render();
	for (std::shared_ptr<Enemy>& e : enemies)
	{
		float dist = player.getDistance(e->getSprite().getPosition());
		if (dist < 700.f) e.get()->render();
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
		player.healthBar.setPos(newPos.x, newPos.y);
		player.healthBar.render(*window);
	}

	window->display();
}


void Level::checkCollisions()
{
	mouseBounds.setPosition(MousePosition::Get());

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
	// Terrain and Ranged Attack
	collision.collisionDetection(playerRangedAttack, terrain);
	// Player and Enemy Ranged Attacks
	collision.collisionDetection(player, beetleAttacks);
	// Player and Entity
	collision.collisionDetection(player, entities);

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
	if (editor.getMode() == Mode::enemies)
	{
		outlineFill.setFillColor(sf::Color::White);
	}
	else 
	{
		switch (editor.getDesiredType())
		{
		case 0:
			outlineFill.setFillColor(sf::Color::Blue);
			break;
		case 1:
			outlineFill.setFillColor(sf::Color::Yellow);
			break;
		default:
			outlineFill.setFillColor(sf::Color::Yellow);
			break;
		}
	}
}

void Level::SpawnSpawn()
{
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(editor.createSpawn(spawnPos));
	enemy->changeType(enemy->enemyType);
	enemies.push_back(enemy);

	int count = 0;
	for (std::shared_ptr<Enemy>& t : enemies)
	{
		t->setCounter(count);
		count++;
	}
	spawnReady = false;
}

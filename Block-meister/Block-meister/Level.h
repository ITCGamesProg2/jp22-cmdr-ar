#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Terrain.h"
#include "Collision.h"
#include "LevelEditor.h"
#include "AttackEntity.h"
#include "RangedAttackEntity.h"
#include "YamlLoader.h"
#include "ParticleManager.h"

class Level
{
public:
	Level(sf::RenderWindow& t_window);
	sf::RenderWindow* window;
	ParticleManager particleManager;

	void loadLevel();
	void saveLevel(); // editor save
	void saveGame();

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	void checkCollisions();
	void editorOn();
	void setOutline();
	sf::Vector2f gridPlacement(sf::Vector2f mousePosition);

private:
	LevelEditor editor;
	sf::RectangleShape mouseBounds;
	Collision collision;
	Player player;
	AttackEntity playerAttack;

	static const int MAX_RANGED_ATTACKS{ 20 };
	RangedAttackEntity playerRangedAttack[MAX_RANGED_ATTACKS];

	std::vector<Entity> entities;
	std::vector<std::shared_ptr<Terrain>> terrain;
	std::vector<std::shared_ptr<Enemy>> enemies;
	sf::RectangleShape outline;
	sf::RectangleShape outlineFill;

	bool m_levelEditor{ false };
	bool ctrlDown = false;
	YamlLoader yml;
	LevelData levelData;
	PlayerData playerData;
	int currentLevel = 1;
};


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

class Level
{
public:
	Level(sf::RenderWindow& t_window);
	sf::RenderWindow* window;

	void loadLevel(int no);

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
	std::vector<Entity> entities;
	std::vector<Terrain> terrain;
	std::vector<std::shared_ptr<Enemy>> enemies;
	sf::RectangleShape outline;

	bool m_levelEditor{ false };
};


#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Terrain.h"
#include "Enemy.h"
#include "MousePosition.h"

enum class Mode {
	terrain, enemies
};

class LevelEditor
{
public:
	LevelEditor();
	static std::vector<std::shared_ptr<Terrain>>* terrain;

	void update(sf::RenderWindow& t_window);
	void processEvents(sf::Event& event);

	//Terrain creation
	Terrain createTerrain();
	Terrain createTerrain(sf::Vector2f position, Type type);
	void deleteTerrain(std::vector<std::shared_ptr<Terrain>>& terrain, int terrainIndex);

	//Enemy creation
	void createEnemy(std::vector<std::shared_ptr<Enemy>>& enemies);
	Enemy createEnemy(sf::Vector2f position, EnemyType type);
	void deleteEnemy(std::vector<std::shared_ptr<Enemy>>& enemies, int enemiesIndex);

	//Tools
	void editorOn() { levelEditor = true; }
	void editorOff() { levelEditor = false; }

	//Getters
	bool getEditor() { return levelEditor; }
	int getDesiredType() { return desiredType; }
	Mode getMode() { return currentMode; }

private:

	int desiredType{ 0 };
	Mode currentMode{ Mode::terrain };
	int modeIndex{ 1 };

	bool levelEditor{ false };

	// tool vars
	int toolIndex{ 1 };
	sf::Vector2f fillPosition[2] = { {0,0}, {0,0} };
	void rectFill();
};


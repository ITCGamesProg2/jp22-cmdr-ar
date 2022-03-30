#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Terrain.h"
#include "Enemy.h"

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
	void createEnemy(std::vector<Enemy>& enemies, sf::Vector2f position, Type type);
	void deleteEnemy(std::vector<Enemy>& enemies, int enemiesIndex);

	//Tools
	sf::Vector2f gridPlacement(sf::Vector2f mousePosition);
	void editorOn() { levelEditor = true; }
	void editorOff() { levelEditor = false; }

	//Getters
	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);
	sf::Vector2f getMouse() { return mousePosition; }
	bool getEditor() { return levelEditor; }
	int getDesiredType() { return desiredType; }
	Mode getMode() { return currentMode; }

private:

	int desiredType{ 0 };
	Mode currentMode{ Mode::terrain };
	int modeIndex{ 1 };

	sf::Vector2f mousePosition{ 0,0 };

	bool levelEditor{ false };

	// tool vars
	int toolIndex{ 1 };
	sf::Vector2f fillPosition[2] = { {0,0}, {0,0} };
	void rectFill();
};


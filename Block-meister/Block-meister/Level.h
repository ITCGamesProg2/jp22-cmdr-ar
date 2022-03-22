#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Entity.h"
#include "Terrain.h"
#include "LevelEditor.h"

class Level
{
public:
	Level(sf::RenderWindow& t_window);
	sf::RenderWindow* window;

	void loadLevel(int no);

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	void createTerrain();

private:
	LevelEditor editor;
	Player player;
	std::vector<Entity> entities;
	std::vector<Terrain> terrain;
};


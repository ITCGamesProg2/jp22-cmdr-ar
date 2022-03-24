#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Terrain.h"

class LevelEditor
{
public:
	LevelEditor();

	void update(sf::RenderWindow& t_window);
	void processEvents(sf::Event& event);
	void editorOn() { levelEditor = true; }
	void editorOff() { levelEditor = false; }

	void createTerrain(std::vector<Terrain>& terrain);
	void createTerrain(std::vector<Terrain>& terrain, sf::Vector2f position, Type type);
	void deleteTerrain(std::vector<Terrain>& terrain, int terrainIndex);
	sf::Vector2f gridPlacement(sf::Vector2f mousePosition);

	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);
	sf::Vector2f getMouse() { return mousePosition; }
	bool getEditor() { return levelEditor; }
	int getDesiredType() { return desiredType; }

private:

	int desiredType{ 0 };

	sf::Vector2f mousePosition{ 0,0 };

	bool levelEditor{ false };
};


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

	void selectEntity(Entity& t_entity);
	void selectTerrain(Terrain& t_terrain);
	void moveSelected();

	int getDesiredType() { return desiredType; }
	sf::Vector2f getMouse() { return mousePosition; }

private:
	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);

	Entity* currentlySelectedEntity;
	Terrain* currentlySelectedTerrain;

	int desiredType{ 0 };

	sf::RectangleShape mouseBounds;
	sf::Vector2f mousePosition{ 0,0 };
	bool levelEditor{ true };
};


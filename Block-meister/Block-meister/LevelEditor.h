#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class LevelEditor
{
public:
	LevelEditor();

	void update(sf::RenderWindow& t_window);

	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);
	void selectEntity(Entity t_entity);
	void moveEntity();

private:
	Entity* currentlySelected;
	sf::RectangleShape mouseBounds;
	sf::Vector2f mousePosition{ 0,0 };
	bool levelEditor{ true };
};


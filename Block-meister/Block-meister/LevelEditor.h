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

	int getDesiredType() { return desiredType; }
	sf::Vector2f getMouse() { return mousePosition; }
	bool getEditor() { return levelEditor; }

private:
	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);

	int desiredType{ 0 };

	sf::Vector2f mousePosition{ 0,0 };

	bool levelEditor{ true };
};


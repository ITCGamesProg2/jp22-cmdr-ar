#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Level.h"

enum class State {
	Menu, Game
};

class Game
{
public:
	Game();
	void Run();

	State state;

private:
	sf::RenderWindow m_window;

	void processEvents();
	void update(sf::Time dt);
	void render();

	bool m_exitGame = false;

	Menu menu;
	Level level;

};


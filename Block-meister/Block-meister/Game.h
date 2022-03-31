#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "DeadMenu.h"
#include "Level.h"

enum class State {
	Menu, Game, Dead
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
	DeadMenu deadMenu;
	Level level;

	sf::Clock deadTimer;
};


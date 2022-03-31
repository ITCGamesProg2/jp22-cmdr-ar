#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Window.h"

class DeadMenu
{
public:
	DeadMenu(sf::RenderWindow& t_window);
	sf::RenderWindow* window;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	bool restartClicked = false;

private:
	void Setup();

	sf::Sprite bg;
	sf::Texture bgTex;
	Animation bg_anim;

	sf::Sprite lamp[2];
	sf::Texture lampTex;
	Animation lamp_anim[2];

	sf::Font alagard;
	sf::Text Title;
	sf::Text Summary;
	sf::Text Restart;

};


#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Menu
{
public:
	Menu(sf::RenderWindow& t_window);
	sf::RenderWindow* window;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	bool playClicked = false;

private:
	void Setup();

	sf::Sprite bg;
	sf::Texture bgTex;
	Animation bg_anim;

	sf::Sprite logo;
	sf::Texture logoTex;
	Animation logo_anim;

	sf::Sprite lamp;
	sf::Texture lampTex;
	Animation lamp_anim;

	sf::Sprite title;
	sf::Texture titleTex;
	sf::Sprite play;
	sf::Texture playTex;

	

};


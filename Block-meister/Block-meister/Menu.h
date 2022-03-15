#pragma once
#include <SFML/Graphics.hpp>

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
	sf::Clock bgTimer;
	int bgcurrentFrame = 0;
	float bgincrement = 0.4f;

	sf::Sprite logo;
	sf::Texture logoTex;
	sf::Clock logoTimer;
	int logocurrentFrame = 0;
	float logoincrement = 2.5f;

	sf::Sprite lamp;
	sf::Texture lampTex;
	sf::Clock lampTimer;
	int lampcurrentFrame = 0;
	float lampincrement = 0.25f;

	sf::Sprite title;
	sf::Texture titleTex;
	sf::Sprite play;
	sf::Texture playTex;

};


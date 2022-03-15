#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(sf::RenderWindow& t_window);
	sf::RenderWindow* window;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

private:
	sf::View view;
	sf::Sprite body;
	sf::Texture tex;
	sf::Vector2f moveBy;
	float speed = 150.f;


	//animation
	void animate();
	bool up = false;
	bool down = false;
	bool otherKey = false;
	bool lastMovedUp = false;

	int currentFrame = 0;
	sf::Clock Timer;
	float increment = 0.15f;

};


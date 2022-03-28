#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Animation.h"

enum class Direction
{
	Up, Down, Left, Right, None,
	UpRight, UpLeft, DownRight, DownLeft
};

class Player
{
public:
	Player(sf::RenderWindow& t_window);
	sf::RenderWindow* window;

	void processEvents(sf::Event& event);
	void update(sf::Time& dt);
	void render();
	void bump();
	void dodge();

	sf::Sprite getSprite() { return body; }
	Direction getDir() { return currentDirection; }
	sf::Vector2f getPos() { return body.getPosition(); }

	void setPos(float x, float y) { body.setPosition(x, y); }

private:
	sf::View view;
	sf::Sprite body;
	sf::Texture tex;
	sf::Vector2f moveBy;
	float speed = 150.f;
	sf::Time m_dt;

	//dodging
	bool dodging;
	sf::Clock dodgeTimer;
	void animateDodge(sf::Time& dt);
	float alpha = 255;

	//movement
	Direction currentDirection{ Direction::None };
	sf::RectangleShape nextMovement;
	void setMovement();

	//animation
	void animate();
	Animation anim;

};


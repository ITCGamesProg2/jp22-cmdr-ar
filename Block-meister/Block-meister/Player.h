#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Animation.h"
#include "HealthBar.h"

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
	HealthBar health;

	void processEvents(sf::Event& event);
	void update(sf::Time& dt);
	void render();
	void bump();
	void dodge();
	void knockbackEntity();
	bool timer(float t_desiredTime, sf::Clock t_timer);

	//Getters
	sf::Sprite getSprite() { return body; }
	sf::RectangleShape getNextMove() { return nextMovement; }
	bool getDodging() { return dodging; }
	bool getKnockedback() { return knockback; }
	Direction getDir() { return currentDirection; }
	sf::Vector2f getPos() { return body.getPosition(); }
	void getKnockbackDirection(sf::Sprite t_sprite);

	//Setters
	void setPos(float x, float y) { body.setPosition(x, y); }

private:

	sf::Vector2f moveBy;
	float speed = 300.f;
	float MAX_SPEED{ 150.f };
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

	//knockback
	sf::Vector2f knockbackDirection;
	sf::Clock knockbackDuration;
	bool knockback{ false };
	float knockbackStrength{ 5 };

	//animation
	void animate();
	Animation anim;

	sf::View view;
	sf::Sprite body;
	sf::Texture tex;
};


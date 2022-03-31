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
	HealthBar healthBar;

	void processEvents(sf::Event& event);
	void update(sf::Time& dt);
	void render();
	void bump();
	void dodge();
	void knockbackEntity();
	bool timer(float t_desiredTime, sf::Clock t_timer);
	void damagePlayer(float t_damage);
	void damageSelf();

	//Getters
	float getDistance(sf::Vector2f other)
	{
		float distance = sqrt(pow(other.x - body.getPosition().x, 2) +
			pow(other.y - body.getPosition().y, 2) * 1.0);
		return distance;
	}
	sf::Sprite getSprite() { return body; }
	sf::RectangleShape getNextMove() { return nextMovement; }
	bool getDodging() { return dodging; }
	bool getKnockedback() { return knockback; }
	bool getAlive() { return alive; }
	Direction getDir() { return currentDirection; }
	sf::Vector2f getPos() { return body.getPosition(); }
	void getKnockbackDirection(sf::Sprite t_sprite);

	//Setters
	void setPos(float x, float y) { body.setPosition(x, y); }

private:

	sf::Time m_dt;

	//Health
	float health{ 200 };
	const float MAX_HEALTH{ 150 };
	static const int ATTACK_SELF_DAMAGE = 5;
	bool alive{ true };
	sf::Clock iFrames;
	sf::Clock highlightTimer;

	//dodging
	bool dodging;
	bool dodgingKnockedback{ false };
	sf::Clock dodgeTimer;
	void animateDodge(sf::Time& dt);
	float alpha = 255;

	//movement
	sf::Vector2f moveBy;
	float speed = 300.f;
	const float MAX_SPEED{ 200.f };
	const float DASH_SPEED{ 700.f };
	Direction currentDirection{ Direction::None };
	sf::RectangleShape nextMovement;
	void setMovement();

	//knockback
	sf::Vector2f knockbackDirection;
	sf::Clock knockbackDuration;
	bool knockback{ false };
	float knockbackStrength{ 5.5 };

	//animation
	void animate();
	Animation anim;

	sf::View view;
	sf::Sprite body;
	sf::Sprite shadow;
	sf::Texture tex;
	sf::Texture shadowTex;
};


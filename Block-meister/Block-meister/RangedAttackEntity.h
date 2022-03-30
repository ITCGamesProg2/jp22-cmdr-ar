#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class RangedAttackEntity
{
public:
	RangedAttackEntity();

	static sf::RenderWindow* window;
	static Player* player;

	void update(sf::Time& dt);
	void render();
	void activateProjectile(sf::Vector2f t_position, sf::Vector2f t_direction);
	void activateProjectile(sf::Vector2f t_position);

	bool getActive() { return active; }
	sf::Sprite getSprite() { return body; }

	void setActive(bool t_active) { active = t_active; }

	static const int MAX_ATTACKS = 20;
	static const int MAX_BEETLE_ATTACKS = 3;

	static const int ATTACK_DAMAGE = 25;

private:
	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);
	void calculateDirection(sf::Vector2f t_mousePos, sf::Vector2f t_start);
	void boundsCollision(sf::Time& dt);

	bool active{ false };

	sf::Vector2f direction{ 0,0 };
	float speed{ 750 };

	static sf::Clock attackTimer;
	float timeBetweenAttacks{ 0.15f };

	sf::Sprite body;
	sf::Texture tex;
};

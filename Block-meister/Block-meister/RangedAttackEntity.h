#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class RangedAttackEntity
{
public:
	RangedAttackEntity();

	static sf::RenderWindow* window;
	static Player* player;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	bool getActive() { return active; }

	void setActive(bool t_active) { active = t_active; }

	static int currentAttack;
	static const int MAX_ATTACKS = 20;

private:
	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);
	void calculateDirection(sf::Vector2f t_mousePos);
	void boundsCollision(sf::Time& dt);

	bool active{ false };

	sf::Vector2f direction{ 0,0 };
	float speed{ 750 };

	static sf::Clock attackTimer;
	float timeBetweenAttacks{ 0.15f };

	sf::Sprite body;
	sf::Texture tex;
};

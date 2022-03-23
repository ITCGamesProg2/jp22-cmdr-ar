#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class AttackEntity
{
public:
	AttackEntity();

	static sf::RenderWindow* window;
	static Player* player;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	bool attacking() { return isAttacking; }

private:
	bool isAttacking = false;
	sf::Clock attackTimer;
	void setAttackPos();
	void animateAttack(sf::Time& dt);
	bool attackDirSet = false;
	bool readyToDraw = false;

	float rotation = 0.f;
	sf::Vector2f offset;

	sf::Vector2f prevDir;
	float prevRotation = 270.f;
	bool firstTime = true;

	sf::Sprite body;
	sf::Texture tex;
};


#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

enum class EnemyType {
	Slime
};

class Enemy
{
public:
	Enemy();
	void SetTexture(const char* path);
	void SetTexture(EnemyType _type);

	void changeType(EnemyType type);

	static sf::RenderWindow* window;
	static Player* player;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();
	bool timer(float t_desiredTime, sf::Clock t_timer);
	void bump();
		
	EnemyType enemyType = EnemyType::Slime;


	//Slime stuff
	void slimeCharge(sf::Time& dt);
	void setCharge(bool t_charging) { charging = t_charging; }
	
	//Getters
	sf::Sprite getSprite() { return body; }
	bool getChargeActive() { return chargeActive; }
	void getBounceDirection(sf::Sprite t_sprite);
	void directionTowardsPlayer();
	sf::RectangleShape getNextMove() { return nextMovement; }

	//Setters
	void setPos(float x, float y) { body.setPosition(x, y); }
	void setPos(sf::Vector2f pos) { body.setPosition(pos); }
	void setScale(float x, float y) { body.setScale(x, y); }
	void setCounter(int t_count) { count = t_count; }
	void setKnockback(bool t_knockback);

private:
	sf::Time m_dt;
	int count;
	float speed{ 500 };
	sf::Vector2f direction{ 0,0 };
	sf::Clock bumpDuration;
	bool knockback{ false };

	//Slime stuff
	bool charging{ false };
	bool chargeActive{ false };
	const float CHARGE_SPEED = 750;
	const float SLIME_SPEED = 500;
	sf::Vector2f playerDirection;
	sf::Clock chargePrep;
	sf::Clock chargeDuration;

	sf::Sprite body;
	sf::RectangleShape nextMovement;
	sf::Texture tex;
};


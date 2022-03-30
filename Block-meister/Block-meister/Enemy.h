#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Vectors.hpp>
#include "Player.h"
#include "HealthBar.h"
#include "BreadthFirstSearch.h"

enum class EnemyType {
	Slime, Beetle
};

enum class EnemyDirection
{
	Up, Down, Left, Right, None
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
	HealthBar healthBar;
	static std::vector<std::shared_ptr<Terrain>>* terrain;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();
	bool timer(float t_desiredTime, sf::Clock t_timer);
	void bump();
	void resetSpeed() { speed = SLIME_SPEED; }
	void damageEnemy(float t_damage);
	void placeHealthBar();
	void setMovement();

	EnemyType enemyType = EnemyType::Slime;
	int count;

	//Directional
	EnemyDirection currentDirection{ EnemyDirection::None };
	float directionRotation{ 0 };

	//Slime stuff
	void slimeCharge(sf::Time& dt);
	void setCharge(bool t_charging) { charging = t_charging; }

	//Beetle stuff
	sf::Vector2f* getTriAim();
	void beetleUpdate();
	
	//Getters
	sf::Sprite& getSprite() { return body; }
	bool getChargeActive() { return chargeActive; }
	bool getParticleReady();
	bool getBeetleAttacking() { return beetleAttacking; }
	void getBounceDirection(sf::Sprite t_sprite);
	void getBounceDirection();
	void directionTowardsPlayer();
	sf::RectangleShape getNextMove() { return nextMovement; }

	//Setters
	void setPos(float x, float y) { body.setPosition(x, y); }
	void setPos(sf::Vector2f pos) { body.setPosition(pos); }
	void setCounter(int t_count) { count = t_count; }
	void setAlive(bool t_alive);
	void setKnockback(bool t_knockback);
	void resetBeetleAttacking() { beetleAttacking = false, beetleReady = false; }

	//pathfinding
	void setupPathing();
private:
	//pathfinding
	BreadthFirstSearch pathing;
	float playerDistance = 1500.f;
	void Pathfind();
	void updatePathing(sf::Time& dt);

	sf::Time m_dt;
	float speed{ 500 };
	sf::Vector2f direction{ 0,0 };
	sf::Vector2f playerDirection;
	sf::Clock bumpDuration;
	bool knockback{ false };

	//Health Related stuff
	float health{ 0 };
	bool alive{ true };
	bool particleReady{ false };
	sf::Clock iFrames;

	//Slime stuff
	const float SLIME_HEALTH{ 50 };
	bool charging{ false };
	bool chargeActive{ false };
	const float CHARGE_SPEED = 750;
	const float SLIME_SPEED = 500;
	sf::Clock chargePrep;
	sf::Clock chargeDuration;
	sf::Clock chargeCooldown;

	//Beetle stuff
	const float BEETLE_HEALTH{ 100 };
	sf::Clock beetleAim;
	bool beetleReady{ false };
	bool beetleAttacking{ false };
	sf::Vector2f triAim[3];

	//Reset Values
	void beetleReset();

	sf::Sprite body;
	sf::RectangleShape nextMovement;
	sf::Texture tex;
};


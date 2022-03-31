#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Vectors.hpp>
#include "Player.h"
#include "HealthBar.h"
#include "BreadthFirstSearch.h"

enum class EnemyType {
	Slime, Beetle, Hive, Spawn
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
	void move(sf::Time& dt);

	EnemyType enemyType = EnemyType::Slime;
	int count;


	//Slime stuff
	void slimeUpdate(sf::Time& dt);
	void setCharge(bool t_charging) { charging = t_charging; }

	//Beetle stuff
	sf::Vector2f* getTriAim();
	void beetleUpdate();
	void resetBeetleAttacking() { beetleAttacking = false, beetleReady = false; }

	//Hive stuff
	void hiveUpdate();

	//Spawn stuff
	void spawnReset(sf::Vector2f pos);

	//Getters
	sf::Sprite& getSprite() { return body; }
	bool getChargeActive() { return chargeActive; }
	bool getParticleReady();
	bool getBeetleAttacking() { return beetleAttacking; }
	void getBounceDirection(sf::Sprite t_sprite);
	void getBounceDirection();
	void directionTowardsPlayer();
	sf::RectangleShape getNextMove() { return nextMovement; }
	bool getAlive() { return alive; }
	bool getSpawnReady() { return spawnReady; }
	bool getHiveHit() { return hiveHit; }
	float getDamage() { return damage; }

	//Setters
	void setPos(float x, float y) { body.setPosition(x, y); }
	void setPos(sf::Vector2f pos) { body.setPosition(pos); }
	void setCounter(int t_count) { count = t_count; }
	void setAlive(bool t_alive);
	void setKnockback(bool t_knockback);
	void setSpawnReady(bool t_ready) { spawnReady = t_ready; }
	void setHiveHit(bool t_hit) { hiveHit = t_hit; }

	//pathfinding
	void setupPathing();
private:

	//pathfinding
	BreadthFirstSearch pathing;
	float playerDistance = 1500.f;
	void Pathfind();
	void updatePathing(sf::Time& dt);

	sf::Time m_dt;
	sf::Clock highlightTimer;

	//damage
	float damage{ 0 };

	//knockback interaction
	sf::Vector2f direction{ 0,0 };
	sf::Vector2f playerDirection;
	sf::Clock bumpDuration;
	bool knockback{ false };

	// Movement
	sf::Vector2f moveBy;
	float speed{ 500 };
	float typeSpeed{ 0 };
	float speedMultiplier{ 3 };

	//Health Related stuff
	float health{ 0 };
	bool alive{ true };
	bool particleReady{ false };
	sf::Clock iFrames;

	//Slime stuff
	const float SLIME_HEALTH{ 75 };
	bool charging{ false };
	bool chargeActive{ false };
	const float CHARGE_SPEED = 650;
	const float SLIME_SPEED = 500;
	const float SLIME_DAMAGE = 25;

	sf::Clock chargePrep;
	sf::Clock chargeDuration;
	sf::Clock chargeCooldown;

	//Beetle stuff
	const float BEETLE_HEALTH{ 100 };
	const float BEETLE_AIM_RANGE{ 350 };
	const float BEETLE_SPEED{ 350 };
	const float BEETLE_DAMAGE = 10;
	sf::Clock beetleAim;
	sf::Clock beetleAttackCooldown;
	sf::Clock runAwayTimer;
	bool beetleReady{ false };
	bool beetleAttacking{ false };
	sf::Vector2f triAim[3];

	//Hive stuff
	const float HIVE_HEALTH{ 300 };
	const float HIVE_SPAWN_RANGE{ 550 };
	sf::Clock spawnTimer;
	bool spawnReady{ false };
	bool hiveHit{ false };
	const float HIVE_DAMAGE = 5;

	//Spawn
	const float SPAWN_HEALTH{ 10 };
	const float SPAWN_SPEED{ 500 };
	const float SPAWN_DAMAGE = 20;

	//Reset Values
	void beetleReset();

	sf::Sprite body;
	sf::RectangleShape nextMovement;
	sf::Texture tex;
};


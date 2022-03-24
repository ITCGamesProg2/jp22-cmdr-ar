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

	EnemyType enemyType = EnemyType::Slime;

	//Getters
	sf::Sprite getSprite() { return body; }

	//Setters
	void setPos(float x, float y) { body.setPosition(x, y); }
	void setPos(sf::Vector2f pos) { body.setPosition(pos); }
	void setScale(float x, float y) { body.setScale(x, y); }
	void setCounter(int t_count) { count = t_count; }

private:
	int count;

	sf::Sprite body;
	sf::Texture tex;
};


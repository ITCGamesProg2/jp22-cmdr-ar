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

	static sf::RenderWindow* window;
	static Player* player;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	EnemyType type = EnemyType::Slime;

	//Getters
	sf::Sprite getSprite() { return body; }

	//Setters
	void setPos(float x, float y) { body.setPosition(x, y); }

private:
	sf::Sprite body;
	sf::Texture tex;
};


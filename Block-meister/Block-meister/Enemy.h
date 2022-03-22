#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy
{
public:
	Enemy();
	void SetTexture(const char* path);

	static sf::RenderWindow* window;
	static Player* player;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	//Getters
	sf::Sprite getSprite() { return body; }

private:
	sf::Sprite body;
	sf::Texture tex;
};


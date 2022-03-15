#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Entity
{
public:
	Entity();
	void SetTexture(const char* path);

	static sf::RenderWindow* window;
	static Player* player;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

private:
	sf::Sprite body;
	sf::Texture tex;
};

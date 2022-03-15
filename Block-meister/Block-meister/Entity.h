#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Entity
{
public:
	Entity();
	void SetTexture(const char* path);

	static sf::RenderWindow* window;
	void SetWindowPtr(sf::RenderWindow& _window) { Entity::window = &_window; }

	static Player* player;
	void SetPlayerPtr(Player& _player) { Entity::player = &_player; }

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

private:
	sf::Sprite body;
	sf::Texture tex;
};

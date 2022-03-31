#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

enum class EntityType {
	Heart
};

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
	void spawn(sf::Vector2f t_pos);
	void heal();

	//Getters
	sf::Sprite getSprite() { return body; }
	bool getActive() { return active; }

	//Setters
	void setType(EntityType t_type);

private:

	EntityType type{ EntityType::Heart };
	bool active{ false };
	const int HEAL_VALUE{ 15 };

	sf::Sprite body;
	sf::Texture tex;
};

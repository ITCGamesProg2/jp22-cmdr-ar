#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

enum class Type
{
	wall, ground
};

class Terrain
{
public:
	Terrain();
	void SetTexture(const char* path);

	static sf::RenderWindow* window;
	static Player* player;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();

	//Getters
	sf::Sprite getSprite() { return body; }
	
	//Setters
	void setType(Type t_type);
	void setPos(sf::Vector2f t_pos) { body.setPosition(t_pos); }

private:

	Type type{ Type::ground };

	sf::Sprite body;
	sf::Texture tex;
};

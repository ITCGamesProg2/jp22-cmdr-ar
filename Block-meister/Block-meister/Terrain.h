#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

enum class Type
{
	wall, ground, stairs
};

class Terrain
{
public:
	Terrain();
	void SetTexture(const char* path);

	static sf::RenderWindow* window;
	static Player* player;
	int terrainCount;

	void processEvents(sf::Event& ev);
	void update(sf::Time& dt);
	void render();
	void changeType(Type type);

	//Getters
	sf::Sprite getSprite() { return body; }
	Type getType() { return type; }
	sf::Vector2f getPos() { return body.getPosition(); }

	//Setters
	void setType(Type t_type);
	void setPos(sf::Vector2f t_pos) { body.setPosition(t_pos); }
	void setCounter(int count) { terrainCount = count; }

private:

	Type type{ Type::ground };

	sf::Sprite body;
	sf::Texture tex;
};

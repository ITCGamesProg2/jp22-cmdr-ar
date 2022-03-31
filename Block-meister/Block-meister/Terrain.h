#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

enum class Type
{
	wall, ground
};

enum class Block
{
	brick, dirt, cobble, stairs
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
	void changeType(Type _type);
	void changeBlock(Block _type);

	//Getters
	sf::Sprite getSprite() { return body; }
	Type getType() { return type; }
	Block getBlock() { return block; }
	sf::Vector2f getPos() { return body.getPosition(); }

	//Setters
	void setPos(sf::Vector2f t_pos) { body.setPosition(t_pos); }
	void setCounter(int count) { terrainCount = count; }

	static bool NextLevelReady;
private:
	void setType(Type t_type);

	Type type{ Type::ground };
	Block block{ Block::dirt };

	sf::Sprite body;
	sf::Texture tex;
};

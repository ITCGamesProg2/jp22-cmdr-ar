#pragma once
#include "Player.h"
#include "Terrain.h"
#include "Enemy.h"
#include "vector"

class Collision
{
public:
	Collision();

	void collisionDetection(std::vector<Terrain>& terrain, std::vector<std::shared_ptr<Enemy>> enemies);
	void collisionDetection(Player& player, std::vector<std::shared_ptr<Enemy>> enemies);
	void collisionDetection(Player& player, std::vector<Terrain>& terrain);
	void collisionDetection(Player& player, sf::RectangleShape& shape, std::vector<Terrain>& terrain);
	int selectTerrain(sf::RectangleShape& shape, std::vector<Terrain>& terrain);

private:
};


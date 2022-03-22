#pragma once
#include "Player.h"
#include "Terrain.h"
#include "vector"

class Collision
{
public:
	Collision();

	void collisionDetection(Player& player, std::vector<Terrain>& terrain);
	void collisionDetection(Player& player, sf::RectangleShape& shape, std::vector<Terrain>& terrain);
	int selectTerrain(sf::RectangleShape& shape, std::vector<Terrain>& terrain);

private:
};


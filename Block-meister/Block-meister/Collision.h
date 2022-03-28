#pragma once
#include "Player.h"
#include "Terrain.h"
#include "vector"

class Collision
{
public:
	Collision();

	void collisionDetection(Player& player, std::vector<std::shared_ptr<Terrain>>& terrain);
	void collisionDetection(Player& player, sf::RectangleShape& shape, std::vector<std::shared_ptr<Terrain>>& terrain);
	int selectTerrain(sf::RectangleShape& shape, std::vector<std::shared_ptr<Terrain>> terrain);

private:
};


#pragma once
#include "Player.h"
#include "Terrain.h"
#include "vector"

class Collision
{
public:
	Collision();

	void collisionDetection(Player& player, std::vector<Terrain>& terrain);
private:
};


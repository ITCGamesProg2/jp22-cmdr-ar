#pragma once
#include "Player.h"
#include "Terrain.h"
#include "Enemy.h"
#include "RangedAttackEntity.h"
#include "AttackEntity.h"
#include "vector"

class Collision
{
public:
	Collision();

	void collisionDetection(RangedAttackEntity(&attack)[20], std::vector<std::shared_ptr<Enemy>>& enemies);
	void collisionDetection(AttackEntity& attack, std::vector<std::shared_ptr<Enemy>>& enemies);
	void collisionDetection(std::vector<std::shared_ptr<Terrain>>& terrain, std::vector<std::shared_ptr<Enemy>> enemies);
	void collisionDetection(Player& player, std::vector<std::shared_ptr<Enemy>>& enemies);
	void collisionDetection(Player& player, std::vector<std::shared_ptr<Terrain>>& terrain);
	void collisionDetection(Player& player, RangedAttackEntity(&attack)[50]);
	void collisionDetection(Player& player, sf::RectangleShape& shape, std::vector<std::shared_ptr<Terrain>>& terrain);
	int selectTerrain(sf::RectangleShape& shape, std::vector<std::shared_ptr<Terrain>>& terrain);
	int selectEnemy(sf::RectangleShape& shape, std::vector<std::shared_ptr<Enemy>>& enemies);

private:
};


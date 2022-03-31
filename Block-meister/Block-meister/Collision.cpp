#include "Collision.h"

Collision::Collision()
{
}

// enemy and ranged attacks
void Collision::collisionDetection(RangedAttackEntity(&attack)[20], std::vector<std::shared_ptr<Enemy>>& enemies)
{
	for (int i = 0; i < 20; i++)
	{
		if (attack[i].getActive())
		{
			for (std::shared_ptr<Enemy> e : enemies)
			{
				if (e->getAlive())
				{
					if (attack[i].getSprite().getGlobalBounds().intersects(e->getSprite().getGlobalBounds()) &&
						attack[i].getFriendly())
					{
						e->setKnockback(true);
						e->getBounceDirection();
						e->resetSpeed();
						attack[i].setActive(false);
						e->damageEnemy(RangedAttackEntity::ATTACK_DAMAGE);
					}
				}
			}
		}
	}
}

void Collision::collisionDetection(RangedAttackEntity(&attack)[20], std::vector<std::shared_ptr<Terrain>>& terrain)
{
	for (int i = 0; i < 20; i++)
	{
		if (attack[i].getActive())
		{
			for (std::shared_ptr<Terrain> t : terrain)
			{
				if (attack[i].getSprite().getGlobalBounds().intersects(t->getSprite().getGlobalBounds()) &&
					t->getType() == Type::wall)
				{
					attack[i].setActive(false);
				}
			}
		}
	}
}

// enemy and melee attacks
void Collision::collisionDetection(AttackEntity& attack, std::vector<std::shared_ptr<Enemy>>& enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
	{
		if (e->getAlive())
		{
			if (attack.getSprite().getGlobalBounds().intersects(e->getSprite().getGlobalBounds()) && attack.attacking())
			{
				e->setKnockback(true);
				e->getBounceDirection();
				e->resetSpeed();
				e->damageEnemy(AttackEntity::ATTACK_DAMAGE);
			}
		}
	}
}

// enemy and terrain collision
void Collision::collisionDetection(std::vector<std::shared_ptr<Terrain>>& terrain, std::vector<std::shared_ptr<Enemy>> enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
	{
		if (e->getAlive())
		{
			for (std::shared_ptr<Terrain>& t : terrain)
			{

				if (e->getNextMove().getGlobalBounds().intersects(t->getSprite().getGlobalBounds()) &&
					t->getType() == Type::wall)
				{
					e->setKnockback(true);
					e->getBounceDirection(t->getSprite());
				}
			}
		}
	}
}

// Player and enemy collision
void Collision::collisionDetection(Player& player, std::vector<std::shared_ptr<Enemy>>& enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
	{
		if (e->getAlive())
		{
			if (player.getNextMove().getGlobalBounds().intersects(e->getNextMove().getGlobalBounds()) &&
				!player.getDodging())
			{
				if (e->getChargeActive() || player.getKnockedback())
				{
					e->setKnockback(true);
					e->getBounceDirection(player.getSprite());
					e->resetSpeed();
				}
				player.getKnockbackDirection(e->getSprite());
			}
		}
	}
}

// Player and terrain collision
void Collision::collisionDetection(Player& player, std::vector<std::shared_ptr<Terrain>>& terrain)
{
	for (std::shared_ptr<Terrain>& e : terrain)
	{
		if (!player.getDodging())
		{
			if (player.getSprite().getGlobalBounds().intersects(e->getSprite().getGlobalBounds()) &&
				e->getType() == Type::wall)
			{
				player.bump();
			}
		}
		else 
		{
			if (player.getNextMove().getGlobalBounds().intersects(e->getSprite().getGlobalBounds()) &&
				e->getType() == Type::wall)
			{
				player.getKnockbackDirection(e->getSprite());
			}
		}
	}
}

void Collision::collisionDetection(Player& player, RangedAttackEntity(&attack)[50])
{
	for (int i = 0; i < 50; i++)
	{
		if (attack[i].getActive() && !player.getDodging())
		{
			if (attack[i].getSprite().getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) &&
				!attack[i].getFriendly())
			{
				player.getKnockbackDirection(attack[i].getSprite());
				attack[i].setActive(false);
			}
		}
	}
}

// Player, Terrain and mouse collision
void Collision::collisionDetection(Player& player, sf::RectangleShape& shape, std::vector<std::shared_ptr<Terrain>>& terrain)
{
	for (std::shared_ptr<Terrain>& e : terrain)
	{
		if (shape.getGlobalBounds().intersects(e->getSprite().getGlobalBounds()))
		{
			shape.setFillColor(sf::Color::Red);
			break;
		}
		else
		{
			shape.setFillColor(sf::Color::Green);
		}
	}
	if (terrain.size() < 1)
	{
		shape.setFillColor(sf::Color::Green);
	}
	if (shape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
	{
		shape.setFillColor(sf::Color::Red);
	}
}

int Collision::selectTerrain(sf::RectangleShape& shape, std::vector<std::shared_ptr<Terrain>>& terrain)
{
	for (std::shared_ptr<Terrain> e : terrain)
	{
		if (shape.getGlobalBounds().intersects(e->getSprite().getGlobalBounds()))
		{
			std::cout << e->terrainCount << std::endl;
			return e->terrainCount;
		}
	}
	return -1;
}

int Collision::selectEnemy(sf::RectangleShape& shape, std::vector<std::shared_ptr<Enemy>>& enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
	{
		if (shape.getGlobalBounds().intersects(e->getSprite().getGlobalBounds()))
		{
			std::cout << e->count << std::endl;
			return e->count;
		}
	}
	return -1;
}

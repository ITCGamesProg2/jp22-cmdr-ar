#include "Collision.h"

Collision::Collision()
{
}

void Collision::collisionDetection(RangedAttackEntity(&attack)[20], std::vector<std::shared_ptr<Enemy>>& enemies)
{
	for (int i = 0; i < 20; i++)
	{
		if (attack[i].getActive())
		{
			for (std::shared_ptr<Enemy> e : enemies)
			{
				if (attack[i].getSprite().getGlobalBounds().intersects(e->getSprite().getGlobalBounds()))
				{
					e->setKnockback(true);
					e->getBounceDirection(attack[i].getSprite());
					e->resetSpeed();
					attack[i].setActive(false);
				}
			}
		}
	}
}

void Collision::collisionDetection(AttackEntity& attack, std::vector<std::shared_ptr<Enemy>>& enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
	{
		if (attack.getSprite().getGlobalBounds().intersects(e->getSprite().getGlobalBounds()) && attack.attacking())
		{
			e->setKnockback(true);
			e->getBounceDirection(attack.getSprite());
			e->resetSpeed();
		}
	}
}

// enemy and terrain collision
void Collision::collisionDetection(std::vector<std::shared_ptr<Terrain>>& terrain, std::vector<std::shared_ptr<Enemy>> enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
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

// Player and enemy collision
void Collision::collisionDetection(Player& player, std::vector<std::shared_ptr<Enemy>>& enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
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

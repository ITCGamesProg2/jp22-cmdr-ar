#include "Collision.h"

Collision::Collision()
{
}

void Collision::collisionDetection(std::vector<Terrain>& terrain, std::vector<std::shared_ptr<Enemy>> enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
	{
		for (Terrain& t : terrain)
		{
			if (e->getSprite().getGlobalBounds().intersects(t.getSprite().getGlobalBounds()) &&
				t.getType() == Type::wall)
			{
				e->setKnockback(true);
			}
		}
	}
}

void Collision::collisionDetection(Player& player, std::vector<std::shared_ptr<Enemy>> enemies)
{
	for (std::shared_ptr<Enemy> e : enemies)
	{
		if (player.getSprite().getGlobalBounds().intersects(e->getSprite().getGlobalBounds()))
		{
	
		}
	}
}

void Collision::collisionDetection(Player& player, std::vector<Terrain>& terrain)
{
	for (Terrain& e : terrain)
	{
		if (player.getSprite().getGlobalBounds().intersects(e.getSprite().getGlobalBounds()) &&
			e.getType() == Type::wall)
		{
			player.bump();
		}
	}
}

void Collision::collisionDetection(Player& player, sf::RectangleShape& shape, std::vector<Terrain>& terrain)
{
	for (Terrain& e : terrain)
	{
		if (shape.getGlobalBounds().intersects(e.getSprite().getGlobalBounds()))
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

int Collision::selectTerrain(sf::RectangleShape& shape, std::vector<Terrain>& terrain)
{
	for (Terrain& e : terrain)
	{
		if (shape.getGlobalBounds().intersects(e.getSprite().getGlobalBounds()))
		{
			std::cout << e.terrainCount << std::endl;
			return e.terrainCount;
		}
	}
	return -1;
}

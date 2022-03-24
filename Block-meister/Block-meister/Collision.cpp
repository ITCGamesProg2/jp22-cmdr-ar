#include "Collision.h"

Collision::Collision()
{
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
			shape.setOutlineColor(sf::Color::Red);
			break;
		}
		else
		{
			shape.setOutlineColor(sf::Color::Green);
		}
	}
	if (terrain.size() < 1)
	{
		shape.setOutlineColor(sf::Color::Green);
	}
	if (shape.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
	{
		shape.setOutlineColor(sf::Color::Red);
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

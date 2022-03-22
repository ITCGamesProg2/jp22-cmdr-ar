#include "Collision.h"

Collision::Collision()
{
}

void Collision::collisionDetection(Player& player, std::vector<Terrain>& terrain)
{
	for (Terrain& e : terrain)
	{
		if (player.getSprite().getGlobalBounds().intersects(e.getSprite().getGlobalBounds()))
		{
			player.bump();
		}
	}
}

void Collision::collisionDetection(sf::RectangleShape& shape, std::vector<Terrain>& terrain)
{
	for (Terrain& e : terrain)
	{
		if (shape.getGlobalBounds().intersects(e.getSprite().getGlobalBounds()))
		{
			shape.setFillColor(sf::Color::Red);
			break;
		}
		else {
			shape.setFillColor(sf::Color::Green);
		}
	}
	if (terrain.size() < 1)
	{
		shape.setFillColor(sf::Color::Green);
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

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

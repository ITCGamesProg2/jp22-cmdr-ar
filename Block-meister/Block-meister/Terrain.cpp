#include "Terrain.h"

sf::RenderWindow* Terrain::window = nullptr;
Player* Terrain::player = nullptr;

Terrain::Terrain()
{
	body.setTextureRect(sf::IntRect{ 0, 0, 50, 50 });
	body.setOrigin(25, 25);
	terrainCount++;
}

void Terrain::SetTexture(const char* path)
{
	tex.loadFromFile(path);
	body.setTexture(tex);
}

void Terrain::changeType(Type type)
{
	switch (type)
	{
	case Type::wall:
		setType(Type::wall);
		SetTexture("./resources/images/game/brick.png");
		break;
	case Type::ground:
		setType(Type::ground);
		SetTexture("./resources/images/game/brick_ground.png");
		break;
	case Type::stairs:
		setType(Type::stairs);
		SetTexture("./resources/images/game/stairs.png");
		break;
	default:
		break;
	}
}

void Terrain::processEvents(sf::Event& ev)
{
}

void Terrain::update(sf::Time& dt)
{
}

void Terrain::render()
{
	window->draw(body);
}

void Terrain::setType(Type t_type)
{
	type = t_type;
}

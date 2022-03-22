#include "Terrain.h"

sf::RenderWindow* Terrain::window = nullptr;
Player* Terrain::player = nullptr;

Terrain::Terrain()
{
	body.setTextureRect(sf::IntRect{ 0, 0, 100, 100 });
	body.setColor(sf::Color::Blue);
	body.setOrigin(50, 50);
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
		body.setColor(sf::Color::Blue);
		SetTexture("./resources/images/game/yoda.png");
		break;
	case Type::ground:
		setType(Type::ground);
		body.setColor(sf::Color::Yellow);
		SetTexture("./resources/images/game/yoda.png");
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

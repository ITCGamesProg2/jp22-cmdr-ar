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

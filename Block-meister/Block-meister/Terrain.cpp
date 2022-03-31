#include "Terrain.h"

sf::RenderWindow* Terrain::window = nullptr;
Player* Terrain::player = nullptr;
bool Terrain::NextLevelReady = false;

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

void Terrain::changeType(Type _type)
{
	switch (_type)
	{
	case Type::wall:
		setType(Type::wall);
		break;
	case Type::ground:
		setType(Type::ground);
		break;
	default:
		break;
	}
}

void Terrain::changeBlock(Block _type)
{
	switch (_type)
	{
	case Block::brick:
		SetTexture("./resources/images/game/brick.png");
		break;
	case Block::dirt:
		SetTexture("./resources/images/game/dirt.png");
		break;
	case Block::cobble:
		SetTexture("./resources/images/game/cobble.png");
		break;
	case Block::stairs:
		SetTexture("./resources/images/game/stairs.png");
		break;
	default:
		break;
	}

	block = _type;
}

void Terrain::processEvents(sf::Event& ev)
{
}

void Terrain::update(sf::Time& dt)
{
	if (getBlock() == Block::stairs)
	{
		if (player->getDistance(body.getPosition()) < 50.f)
		{
			if (!Terrain::NextLevelReady)
				Terrain::NextLevelReady = true;
		}
	}
}

void Terrain::render()
{
	window->draw(body);
}

void Terrain::setType(Type t_type)
{
	type = t_type;
}

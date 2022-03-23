#include "LevelEditor.h"

LevelEditor::LevelEditor()
{

}

void LevelEditor::update(sf::RenderWindow& t_window)
{
	if (levelEditor)
	{
		mousePosition = getMousePosition(t_window);
	}
}

void LevelEditor::processEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		levelEditor = !levelEditor;
	}
	if (levelEditor)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			desiredType = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			desiredType = 2;
		}
	}
}

void LevelEditor::createTerrain(std::vector<Terrain>& terrain)
{
	if (levelEditor)
	{
		Terrain wall;

		switch (desiredType)
		{
		case 1:
			wall.changeType(Type::wall);
			std::cout << "Terrain: Wall" << std::endl;
			break;
		case 2:
			wall.changeType(Type::ground);
			std::cout << "Terrain: Ground" << std::endl;
		}

		wall.setPos(gridPlacement(mousePosition));
		terrain.push_back(wall);

		int count = 0;

		for (Terrain& e : terrain)
		{
			e.setCounter(count);
			count++;
		}
	}
}

void LevelEditor::createTerrain(std::vector<Terrain>& terrain, sf::Vector2f position, Type type)
{
	if (levelEditor)
	{
		Terrain wall;

		switch (type)
		{
		case Type::wall:
			wall.changeType(Type::wall);
			break;
		case Type::ground:
			wall.changeType(Type::ground);
		}

		wall.setPos(position);
		terrain.push_back(wall);

		int count = 0;

		for (Terrain& e : terrain)
		{
			e.setCounter(count);
			count++;
		}
	}
}

void LevelEditor::deleteTerrain(std::vector<Terrain>& terrain, int terrainIndex)
{
	if (levelEditor)
	{
		if (terrainIndex != -1)
		{
			std::vector<Terrain>::const_iterator i = terrain.begin() + terrainIndex;
			terrain.erase(i);
		}
		int count = 0;
		for (Terrain& e : terrain)
		{
			e.setCounter(count);
			count++;
		}
	}
}

sf::Vector2f LevelEditor::getMousePosition(sf::RenderWindow& t_window)
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(t_window).x;
	m_mousePosition.y = (float)sf::Mouse::getPosition(t_window).y;

	return m_mousePosition;
}

sf::Vector2f LevelEditor::gridPlacement(sf::Vector2f mousePosition)
{
	sf::Vector2f mouseGridPlacement;
	mouseGridPlacement.x = (static_cast<int>(mousePosition.x) / 10) * 10;
	mouseGridPlacement.y = (static_cast<int>(mousePosition.y) / 10) * 10;

	return mouseGridPlacement;
}


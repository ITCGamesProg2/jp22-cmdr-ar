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
	if (levelEditor)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			modeIndex++;

			switch (modeIndex)
			{
			case 1:
				currentMode = Mode::terrain;
				std::cout << "Mode: Terrain" << std::endl;
				break;
			case 2:
				currentMode = Mode::enemies;
				std::cout << "Mode: Enemies" << std::endl;
				break;
			}

			if (modeIndex > 2)
			{
				modeIndex = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			desiredType = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			desiredType = 1;
		}
	}
}

void LevelEditor::createTerrain(std::vector<Terrain>& terrain)
{
	createTerrain(terrain, gridPlacement(mousePosition), (Type)desiredType);
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
			break;
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

void LevelEditor::createEnemy(std::vector<std::shared_ptr<Enemy>>& enemies)
{
	if (levelEditor)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		switch (desiredType)
		{
		case 1:
			enemy->changeType(EnemyType::Slime);
			std::cout << "Enemy: Slime" << std::endl;
			break;
		default:
			enemy->changeType(EnemyType::Slime);
			std::cout << "Enemy: Default Slime" << std::endl;
			break;
		}

		enemy->setPos(gridPlacement(mousePosition));
		enemies.push_back(enemy);

		int count = 0;

		for (std::shared_ptr<Enemy> e : enemies)
		{
			e->setCounter(count);
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


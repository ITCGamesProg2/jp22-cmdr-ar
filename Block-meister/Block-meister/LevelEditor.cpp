#include "LevelEditor.h"
std::vector<std::shared_ptr<Terrain>>* LevelEditor::terrain = nullptr;

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

			if (currentMode == Mode::terrain)
			{
				std::cout << "Type: Wall" << std::endl;
			}
			else {
				std::cout << "Type: Slime" << std::endl;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			desiredType = 1;

			if (currentMode == Mode::terrain)
			{
				std::cout << "Type: Ground" << std::endl;
			}
			else {
				std::cout << "Type: Beetle" << std::endl;
			}
		}

		//editor tools
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) // pencil
		{
			toolIndex = 1;
			std::cout << "Tool: Pencil" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // rectangle fill
		{
			toolIndex = 2;
			std::cout << "Tool: Rect Fill" << std::endl;
		}

		//editor tool calls
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && toolIndex == 2)
			{
				rectFill();
			}
		}
	}
}

Terrain LevelEditor::createTerrain()
{
	Terrain t = createTerrain(gridPlacement(mousePosition), (Type)desiredType);
	return t;
}

Terrain LevelEditor::createTerrain(sf::Vector2f position, Type type)
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

		return wall;
	}
}

void LevelEditor::deleteTerrain(std::vector<std::shared_ptr<Terrain>>& terrain, int terrainIndex)
{
	if (levelEditor)
	{
		if (terrainIndex != -1)
		{
			std::vector< std::shared_ptr<Terrain>>::const_iterator i = terrain.begin() + terrainIndex;
			terrain.erase(i);
		}
		int count = 0;
		for (std::shared_ptr<Terrain> t : terrain)
		{
			t->setCounter(count);
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
		case 0:
			enemy->changeType(EnemyType::Slime);
			std::cout << "Enemy: Slime" << std::endl;
			break;
		case 1:
			enemy->changeType(EnemyType::Beetle);
			std::cout << "Enemy: Beetle" << std::endl;
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

Enemy LevelEditor::createEnemy(sf::Vector2f position, EnemyType type)
{
	if (levelEditor)
	{
		Enemy enemy;

		switch (type)
		{
		case EnemyType::Slime:
			enemy.changeType(EnemyType::Slime);
			break;
		case EnemyType::Beetle:
			enemy.changeType(EnemyType::Beetle);
			break;
		}

		enemy.setPos(position);

		return enemy;
	}
}

void LevelEditor::deleteEnemy(std::vector<std::shared_ptr<Enemy>>& enemies, int enemiesIndex)
{
	if (levelEditor)
	{
		if (enemiesIndex != -1)
		{
			std::vector<std::shared_ptr<Enemy>>::const_iterator i = enemies.begin() + enemiesIndex;
			enemies.erase(i);
		}
		int count = 0;
		for (std::shared_ptr<Enemy> t : enemies)
		{
			t->setCounter(count);
			count++;
		}
	}
}

sf::Vector2f LevelEditor::getMousePosition(sf::RenderWindow& t_window)
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(t_window).x + (t_window.getView().getCenter().x - (t_window.getView().getSize().x / 2) + 25);
	m_mousePosition.y = (float)sf::Mouse::getPosition(t_window).y + (t_window.getView().getCenter().y - (t_window.getView().getSize().y / 2) + 25);

	return m_mousePosition;
}

sf::Vector2f LevelEditor::gridPlacement(sf::Vector2f mousePosition)
{
	sf::Vector2f mouseGridPlacement;
	mouseGridPlacement.x = (static_cast<int>(mousePosition.x) / 10) * 10;
	mouseGridPlacement.y = (static_cast<int>(mousePosition.y) / 10) * 10;

	return mouseGridPlacement;
}

void LevelEditor::rectFill()
{

	if (fillPosition[1] == sf::Vector2f(0, 0))
	{
		if (fillPosition[0] == sf::Vector2f(0, 0))
		{
			fillPosition[0] = gridPlacement(mousePosition);
			std::cout << "Rect Fill Top Left: " << fillPosition[0].x << ", "
				<< fillPosition[0].y << std::endl;
		}
		else
		{
			if (gridPlacement(mousePosition) != fillPosition[0])
			{
				fillPosition[1] = gridPlacement(mousePosition);
				std::cout << "Rect Fill Bottom Right: " << fillPosition[1].x << ", "
					<< fillPosition[1].y << std::endl;
			}
		}
	}
	else
	{
		sf::Vector2f cyclePos = fillPosition[0];
		int cycles = 0;
		while (cycles < 10000) // max placement is 10k blocks at once
		{
			std::shared_ptr<Terrain> ter = std::make_shared<Terrain>(createTerrain(cyclePos, (Type)desiredType));
			ter->changeType(ter->getType());
			terrain->push_back(ter);

			int count = 0;

			for (std::shared_ptr<Terrain>& t : *terrain)
			{
				t->setCounter(count);
				count++;
			}

			cyclePos += sf::Vector2f(50, 0);
			if (cyclePos.x > fillPosition[1].x)
			{
				cyclePos = sf::Vector2f(fillPosition[0].x, cyclePos.y);
				cyclePos += sf::Vector2f(0, 50);
				if (cyclePos.y > fillPosition[1].y) // done
				{
					cycles = 10000;
				}
			}

			cycles++;
		}

		//end
		fillPosition[0] = sf::Vector2f(0, 0);
		fillPosition[1] = sf::Vector2f(0, 0);
	}
}

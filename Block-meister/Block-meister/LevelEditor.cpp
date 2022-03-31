#include "LevelEditor.h"
std::vector<std::shared_ptr<Terrain>>* LevelEditor::terrain = nullptr;

LevelEditor::LevelEditor()
{

}

void LevelEditor::update(sf::RenderWindow& t_window)
{
}

void LevelEditor::processEvents(sf::Event& event)
{
	if (levelEditor)
	{
		if (levelEditor)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Tab)
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
				if (event.key.code == sf::Keyboard::Num1)
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
				if (event.key.code == sf::Keyboard::Num2)
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
				if (event.key.code == sf::Keyboard::Num3)
				{
					desiredType = 2;

					if (currentMode == Mode::terrain)
					{
						std::cout << "Type: Nothing" << std::endl;
					}
					else {
						std::cout << "Type: Hive" << std::endl;
					}
				}
				if (event.key.code == sf::Keyboard::Num4)
				{
					desiredType = 3;

					if (currentMode == Mode::terrain)
					{
						std::cout << "Type: Nothing" << std::endl;
					}
					else {
						std::cout << "Type: Spawn" << std::endl;
					}
				}

				//editor tools
				if (event.key.code == sf::Keyboard::P) // pencil
				{
					toolIndex = 1;
					std::cout << "Tool: Pencil" << std::endl;
				}
				if (event.key.code == sf::Keyboard::R) // rectangle fill
				{
					toolIndex = 2;
					std::cout << "Tool: Rect Fill" << std::endl;
				}
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
}

Terrain LevelEditor::createTerrain()
{
	Terrain t = createTerrain(MousePosition::Get(), (Type)desiredType);
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
		int count = 0;
		for (std::shared_ptr<Terrain> t : terrain)
		{
			t->setCounter(count);
			count++;
		}
		if (terrainIndex != -1)
		{
			std::vector< std::shared_ptr<Terrain>>::const_iterator i = terrain.begin() + terrainIndex;
			terrain.erase(i);
		}
		count = 0;
		for (std::shared_ptr<Terrain> t : terrain)
		{
			t->setCounter(count);
			count++;
		}
	}
}

Enemy LevelEditor::createEnemy()
{
	if (levelEditor)
	{
		Enemy enemy;

		switch (desiredType)
		{
		case 0:
			enemy.changeType(EnemyType::Slime);
			break;
		case 1:
			enemy.changeType(EnemyType::Beetle);
			break;
		case 2:
			enemy.changeType(EnemyType::Hive);
			break;
		case 3:
			enemy.changeType(EnemyType::Spawn);
			break;
		default:
			enemy.changeType(EnemyType::Slime);
			break;
		}

		enemy.setPos(MousePosition::Get());

		return enemy;
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
		case EnemyType::Hive:
			enemy.changeType(EnemyType::Hive);
			break;
		case EnemyType::Spawn:
			enemy.changeType(EnemyType::Spawn);
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
		int count = 0;
		for (std::shared_ptr<Enemy> t : enemies)
		{
			t->setCounter(count);
			count++;
		}
		if (enemiesIndex != -1)
		{
			std::vector<std::shared_ptr<Enemy>>::const_iterator i = enemies.begin() + enemiesIndex;
			enemies.erase(i);
		}
		count = 0;
		for (std::shared_ptr<Enemy> t : enemies)
		{
			t->setCounter(count);
			count++;
		}
	}
}

Enemy LevelEditor::createSpawn(sf::Vector2f position)
{
	Enemy enemy;

	enemy.changeType(EnemyType::Spawn);
	enemy.setPos(position);

	return enemy;
}

void LevelEditor::rectFill()
{

	if (fillPosition[1] == sf::Vector2f(0, 0))
	{
		if (fillPosition[0] == sf::Vector2f(0, 0))
		{
			fillPosition[0] = MousePosition::Get();
			std::cout << "Rect Fill Top Left: " << fillPosition[0].x << ", "
				<< fillPosition[0].y << std::endl;
		}
		else
		{
			if (MousePosition::Get() != fillPosition[0])
			{
				fillPosition[1] = MousePosition::Get();
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

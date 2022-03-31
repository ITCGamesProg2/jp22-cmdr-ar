#include "YamlLoader.h"

void operator >> (const YAML::Node& objectNode, Object& o)
{
	o.Type = objectNode["type"].as<float>();
	o.X = objectNode["x"].as<float>();
	o.Y = objectNode["y"].as<float>();
}

void operator >> (const YAML::Node& enemyNode, EnemyObj& e)
{
	e.Type = enemyNode["type"].as<float>();
	e.X = enemyNode["x"].as<float>();
	e.Y = enemyNode["y"].as<float>();
}

void operator >> (const YAML::Node& t_baseNode, LevelData& ldata)
{
	const YAML::Node& ObjectDataNode = t_baseNode["objects"].as<YAML::Node>();
	for (unsigned i = 0; i < ObjectDataNode.size(); ++i)
	{
		Object obj;
		ObjectDataNode[i] >> obj;
		ldata.objects.push_back(obj);
	}

	const YAML::Node& EnemyDataNode = t_baseNode["enemies"].as<YAML::Node>();
	for (unsigned i = 0; i < EnemyDataNode.size(); ++i)
	{
		EnemyObj obj;
		EnemyDataNode[i] >> obj;
		ldata.enemies.push_back(obj);
	}
}

void YamlLoader::load(int level, LevelData& t_data)
{
	try
	{
		std::cout << "Trying to load: " << "resources/levels/level" + std::to_string(level) + ".yaml" << std::endl;
		YAML::Node baseNode = YAML::LoadFile("resources/levels/level" + std::to_string(level) + ".yaml");
		baseNode >> t_data;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void operator >> (const YAML::Node& t_baseNode, PlayerData& pdata)
{
	const YAML::Node& playerDataNode = t_baseNode["player"].as<YAML::Node>();
	pdata.Level = playerDataNode["level"].as<float>();
	pdata.X = playerDataNode["x"].as<float>();
	pdata.Y = playerDataNode["y"].as<float>();
}

void YamlLoader::load(PlayerData& t_data)
{
	try
	{
		YAML::Node baseNode = YAML::LoadFile("resources/levels/player.yaml");
		baseNode >> t_data;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void YamlLoader::emittter(int level, std::vector<std::shared_ptr<Terrain>> ter,
	std::vector<std::shared_ptr<Enemy>> enemy)
{
	YAML::Emitter out;

	// TERRAIN
	out << YAML::BeginMap;
	out << YAML::Key << "objects";
	out << YAML::BeginSeq;

	for (std::shared_ptr<Terrain> t : ter)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "type"; // t type
		out << YAML::Value << (int)t->getBlock();
		out << YAML::Key << "x"; // t x
		out << YAML::Value << t->getPos().x;
		out << YAML::Key << "y"; // t y
		out << YAML::Value << t->getPos().y;
		out << YAML::EndMap;
	}

	out << YAML::EndSeq;

	// ENEMIES
	out << YAML::Key << "enemies";
	out << YAML::BeginSeq;

	for (std::shared_ptr<Enemy> e : enemy)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "type"; // t type
		out << YAML::Value << (int)e->enemyType;
		out << YAML::Key << "x"; // t x
		out << YAML::Value << e->getSprite().getPosition().x;
		out << YAML::Key << "y"; // t y
		out << YAML::Value << e->getSprite().getPosition().y;
		out << YAML::EndMap;
	}

	out << YAML::EndSeq;
	out << YAML::EndMap;
	///////////////////////////// FILE OPS ///////////////////////////////////////////
	std::ofstream file("resources/levels/level" + std::to_string(level) + ".yaml", std::ofstream::out | std::ofstream::trunc);
	file << out.c_str();
	///////////////////////////// END ////////////////////////////////////////////////
	file.close();
	std::cout << "File Saved!\n";
}

void YamlLoader::emittter(int level, sf::Vector2f pos)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "player";
	out << YAML::BeginMap;
	out << YAML::Key << "level"; // t type
	out << YAML::Value << level;
	out << YAML::Key << "x"; // t x
	out << YAML::Value << pos.x;
	out << YAML::Key << "y"; // t y
	out << YAML::Value << pos.y;
	out << YAML::EndMap;
	out << YAML::EndMap;
	///////////////////////////// FILE OPS ///////////////////////////////////////////
	std::ofstream file("resources/levels/player.yaml", std::ofstream::out | std::ofstream::trunc);
	file << out.c_str();
	///////////////////////////// END ////////////////////////////////////////////////
	file.close();
	std::cout << "Game Saved!\n";
}

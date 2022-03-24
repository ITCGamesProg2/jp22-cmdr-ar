#include "YamlLoader.h"

void operator >> (const YAML::Node& objectNode, Object& o)
{
	o.Type = objectNode["type"].as<float>();
	o.X = objectNode["x"].as<float>();
	o.Y = objectNode["y"].as<float>();
}

void operator >> (const YAML::Node& levelDataNode, LevelData& ldata)
{
	for (unsigned i = 0; i < levelDataNode.size(); ++i)
	{
		Object obj;
		levelDataNode[i] >> obj;
		ldata.objects.push_back(obj);
	}
}

void operator >> (const YAML::Node& t_baseNode, Data& t_data)
{
	const YAML::Node& pDataNode = t_baseNode["objects"].as<YAML::Node>();
	LevelData ldata;
	pDataNode >> ldata;
	t_data.levelData = ldata;
}

void YamlLoader::load(int level, Data& t_data)
{
	try
	{
		YAML::Node baseNode = YAML::LoadFile("resources/levels/level" + std::to_string(level) + ".yaml");
		baseNode >> t_data;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void YamlLoader::emittter(int level, std::vector<Terrain> terrain)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "objects";
	out << YAML::BeginSeq;

	for (Terrain t : terrain)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "type"; // t type
		out << YAML::Value << (int)t.getType();
		out << YAML::Key << "x"; // t x
		out << YAML::Value << t.getPos().x;
		out << YAML::Key << "y"; // t y
		out << YAML::Value << t.getPos().y;
		out << YAML::EndMap;
	}
	
	out << YAML::EndSeq;
	out << YAML::EndMap;
	///////////////////////////// FILE OPS ///////////////////////////////////////////
	std::ofstream file("resources/levels/level" + std::to_string(level) + ".yaml", std::ofstream::out | std::ofstream::trunc);
	file << out.c_str();
	///////////////////////////// END ////////////////////////////////////////////////
	file.close();
}

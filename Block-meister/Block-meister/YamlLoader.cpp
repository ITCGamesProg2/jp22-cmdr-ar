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
}

void YamlLoader::load(Data& t_data)
{
	try
	{
		YAML::Node baseNode = YAML::LoadFile("resources/levels/level1.yaml");
		baseNode >> t_data;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

void YamlLoader::emittter()
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "player";
	out << YAML::BeginMap;
	out << YAML::Key << "name"; // name
	out << YAML::Value << "Malia";
	out << YAML::Key << "level"; // level
	out << YAML::Value << "1";
	out << YAML::Key << "floor"; // floor
	out << YAML::Value << "1";
	out << YAML::EndMap;
	out << YAML::EndMap;
	///////////////////////////// FILE OPS ///////////////////////////////////////////
	std::ofstream file("resources/data.yaml", std::ofstream::out | std::ofstream::trunc);
	file << out.c_str();
	///////////////////////////// END ////////////////////////////////////////////////
	file.close();
}

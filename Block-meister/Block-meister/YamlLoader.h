#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp/yaml.h"

#include "Terrain.h"

struct Object
{
	int Type;
	float X;
	float Y;
};

struct LevelData
{
	std::vector<Object> objects;
};

struct Data
{
	LevelData levelData;
};

class YamlLoader
{
public:
	static void load(int level, Data& t_data);
	static void emittter(int level, std::vector<Terrain> ter);
};

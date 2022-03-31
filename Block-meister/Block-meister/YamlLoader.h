#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp/yaml.h"

#include "Terrain.h"
#include "Enemy.h"

struct Object
{
	int Type;
	float X;
	float Y;
};

struct EnemyObj
{
	int Type;
	float X;
	float Y;
};

struct LevelData
{
	std::vector<Object> objects;
	std::vector<EnemyObj> enemies;
};

struct PlayerData
{
	int Level;
	float X;
	float Y;
};

class YamlLoader
{
public:
	static void load(int level, LevelData& t_data);
	static void load(PlayerData& t_data);
	static void emittter(int level, std::vector<std::shared_ptr<Terrain>> ter,
		std::vector<std::shared_ptr<Enemy>> enemy);
	static void emittter(int level, sf::Vector2f pos);
};
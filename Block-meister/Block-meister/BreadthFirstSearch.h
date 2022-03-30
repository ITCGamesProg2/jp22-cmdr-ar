#pragma once
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>
#include "Terrain.h"

struct Cell
{
	int firstIdInRow;
	int lastIdInRow;
	std::vector<int> neighbours;
	sf::Vector2f position;
	bool marked = false;
	bool containsWall = false;
	int father;
};

class BreadthFirstSearch
{
public:
	BreadthFirstSearch(std::vector<std::shared_ptr<Terrain>>* ter);
	void setup(int _width, int _height);

	std::queue<int> q;
	std::queue<int> path;
	void findPath(int start, int end);

	std::vector<Cell> cells;

	void render(sf::RenderWindow& window);

	int width = 0;
	int height = 0;
private:
	std::vector<std::shared_ptr<Terrain>>* terrain;

	std::vector<sf::RectangleShape> pathShape;
};


#include "BreadthFirstSearch.h"
std::vector<std::shared_ptr<Terrain>>* BreadthFirstSearch::t = nullptr;

BreadthFirstSearch::BreadthFirstSearch()
{
}

void BreadthFirstSearch::setup(int _width, int _height)
{
	width = _width;
	height = _height;

	int amountOfCells = width * height;

	int nextRow = width;
	float nextRowY = 50.f;
	float currentColumnX = 25.f;
	int rowIndex = 0;

	for (int i = 0; i <= amountOfCells; i++)
	{
		if (i > nextRow)
		{
			nextRow += width;
			nextRowY += 50.f;
			currentColumnX = 0.f;
			rowIndex++;
		}
		Cell c;
		c.position = sf::Vector2f(currentColumnX, nextRowY);
		c.firstIdInRow = nextRow - width + 1;
		c.lastIdInRow = nextRow;
		
		for (int x = 0; x < t->size(); x++)
		{
			if (t->at(x)->getType() == Type::wall)
			{
				if (t->at(x)->getSprite().getGlobalBounds().contains(c.position))
				{
					c.containsWall = true;
				}
			}
		}
		
		cells.push_back(c);

		currentColumnX += 50.f;
	}

	std::cout << "\nCells Made!";

	for (int i = 1; i < amountOfCells + 1; i++)
	{
		if (i + 1 <= cells.at(i).lastIdInRow)
		{    // Right of the cell
			cells[i].neighbours.push_back(i + 1);
		}
		if (i - 1 >= cells.at(i).firstIdInRow)
		{    // Left of the cell
			cells[i].neighbours.push_back(i - 1);
		}
		if (i - width >= 0)
		{    // Above cell
			cells[i].neighbours.push_back(i - width);
		}
		if (i + width <= amountOfCells)
		{    // Below cell
			cells[i].neighbours.push_back(i + width);
		}
	}
	std::cout << "\nNeighbours Found!";
}

void BreadthFirstSearch::findPath(int start, int end)
{
	pathShape.clear();
	while (!q.empty())
	{
		q.pop();
	}
	sf::Color c = sf::Color(255,0,0);
	while (!path.empty())
	{
		sf::RectangleShape rect;
		rect.setSize({ 50.f,50.f });
		rect.setPosition(cells[path.front()].position - sf::Vector2f(25,25));
		rect.setFillColor(c);
		pathShape.push_back(rect);
		c += sf::Color(0,20,0);

		path.pop();
	}
	q.push(start);
	

	bool foundPath = false;
	int amountOfCells = width * height;

	int cycles = 0;
	while (!foundPath)
	{
		if (!q.empty())
		{
			if (!cells[q.front()].neighbours.empty())
			{
				for (int i : cells[q.front()].neighbours)
				{
					if (!cells[i].marked && !cells[i].containsWall)
					{
						q.push(i);
						cells[i].marked = true;
						cells[i].father = q.front();
						if (i == end) foundPath = true;
					}
				}
			}
		}
		if (!q.empty()) q.pop();
		cycles++;
		if (cycles > 1000) return;
	}
	foundPath = false;
	int currentFather = end;
	if (!q.empty())
	{
		int cycles = 0;
		while (!foundPath)
		{
			if (currentFather == start) foundPath = true;
			path.push(currentFather);
			currentFather = cells[currentFather].father;
			cycles++;
			if (cycles > 1000) return;
		}
	}
}

void BreadthFirstSearch::render(sf::RenderWindow& window)
{
	for (sf::RectangleShape& shape : pathShape)
	{
		window.draw(shape);
	}
}


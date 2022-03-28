#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
public:
	HealthBar(float width, float height, int maxhp);

	void takeDamage(int dmg);

	void setPos(float x, float y);
	void setBarColour(sf::Color c) { bar.setFillColor(c); }

	bool dead = false;

	void render(sf::RenderWindow& window);

private:
	float barXAsPercent;
	const int maxHP;
	const float maxBar;
	int currentHP = 0;
	sf::RectangleShape bg;
	sf::RectangleShape bar;
};


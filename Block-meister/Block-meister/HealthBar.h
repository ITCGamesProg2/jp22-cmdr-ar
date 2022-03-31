#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
public:
	HealthBar(float width, float height, int maxhp);

	void render(sf::RenderWindow& window);
	void takeDamage(int dmg);
	void heal(int t_value);

	void setMaxHealth(float max) { maxHP = max, currentHP = max; }
	void setPos(float x, float y);
	void setBarColour(sf::Color c) { bar.setFillColor(c); }

	bool dead = false;

private:
	float barXAsPercent;
	int maxHP;
	const float maxBar;
	int currentHP = 0;
	sf::RectangleShape bg;
	sf::RectangleShape bar;
};


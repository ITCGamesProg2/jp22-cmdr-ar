#pragma once
#include <SFML/Graphics.hpp>

class MousePosition
{
public:
	static sf::RenderWindow* window;

	static sf::Vector2f Get()
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(*window);

		mouse.x += (window->getView().getCenter().x - (window->getView().getSize().x / 2) + 25);
		mouse.y += (window->getView().getCenter().y - (window->getView().getSize().y / 2) + 25);

		mouse = (mouse / 50) * 50;

		return (sf::Vector2f)mouse;
	}
};

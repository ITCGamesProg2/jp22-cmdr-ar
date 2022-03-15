#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
	mouseBounds.setSize(sf::Vector2f{ 1, 1 });
}

void LevelEditor::update(sf::RenderWindow& t_window)
{
	if (levelEditor)
	{
		mousePosition = getMousePosition(t_window);
		mouseBounds.setPosition(mousePosition);
	}
}

sf::Vector2f LevelEditor::getMousePosition(sf::RenderWindow& t_window)
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(t_window).x;
	m_mousePosition.y = (float)sf::Mouse::getPosition(t_window).y;

	return m_mousePosition;
}

void LevelEditor::selectEntity(Entity t_entity)
{
	if (mouseBounds.getGlobalBounds().intersects(t_entity.getSprite().getGlobalBounds()))
	{
		currentlySelected = &t_entity;
	}
}

void LevelEditor::moveEntity()
{

}

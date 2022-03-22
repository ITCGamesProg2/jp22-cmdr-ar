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

void LevelEditor::processEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		desiredType = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		desiredType = 2;
	}
}

sf::Vector2f LevelEditor::getMousePosition(sf::RenderWindow& t_window)
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(t_window).x;
	m_mousePosition.y = (float)sf::Mouse::getPosition(t_window).y;

	return m_mousePosition;
}

void LevelEditor::selectEntity(Entity& t_entity)
{
	if (mouseBounds.getGlobalBounds().intersects(t_entity.getSprite().getGlobalBounds()))
	{
		currentlySelectedEntity = &t_entity;
	}
}

void LevelEditor::selectTerrain(Terrain& t_terrain)
{
	if (mouseBounds.getGlobalBounds().intersects(t_terrain.getSprite().getGlobalBounds()))
	{
		currentlySelectedTerrain = &t_terrain;
	}
}

void LevelEditor::moveSelected()
{

}

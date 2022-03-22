#include "LevelEditor.h"

LevelEditor::LevelEditor()
{
	
}

void LevelEditor::update(sf::RenderWindow& t_window)
{
	if (levelEditor)
	{
		mousePosition = getMousePosition(t_window);
	}
}

void LevelEditor::processEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		levelEditor = !levelEditor;
	}
	if (levelEditor)
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
}


sf::Vector2f LevelEditor::getMousePosition(sf::RenderWindow& t_window)
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(t_window).x;
	m_mousePosition.y = (float)sf::Mouse::getPosition(t_window).y;

	return m_mousePosition;
}



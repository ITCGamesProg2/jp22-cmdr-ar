#include "DeadMenu.h"
#include <iostream>

DeadMenu::DeadMenu(sf::RenderWindow& t_window)
	: window{ &t_window }, lamp_anim{ lamp[0], lamp[1] }, bg_anim{ bg }
{
	Setup();
}

void DeadMenu::processEvents(sf::Event& ev)
{
}

void DeadMenu::update(sf::Time& dt)
{
	
	if (Restart.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		Restart.setFillColor(sf::Color(255,255,117));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			restartClicked = true;
		}
	}
	else
	{
		Restart.setFillColor(sf::Color::White);
	}
	
	bg_anim.update();
	lamp_anim[0].update();
	lamp_anim[1].update();
}

void DeadMenu::render()
{
	window->clear(sf::Color::Black);

	window->draw(bg);
	window->draw(lamp[0]);
	window->draw(lamp[1]);

	window->draw(Title);
	window->draw(Summary);
	window->draw(Restart);

	window->display();
}

void DeadMenu::Setup()
{
	lamp_anim[0].Setup(45, 45, 4, 1);
	lamp_anim[0].playAnim(0.25f, 0, 4);
	lamp_anim[1].Setup(45, 45, 4, 1);
	lamp_anim[1].playAnim(0.25f, 0, 4);
	lampTex.loadFromFile("resources/images/menu/lamp/lampSheet.png");
	lamp[0].setTexture(lampTex);
	lamp[1].setTexture(lampTex);

	bg_anim.Setup(1024, 576, 7, 1);
	bg_anim.playAnim(0.4f, 0, 7);
	bgTex.loadFromFile("resources/images/menu/bgPixel/spritesheet.png");
	bg.setTexture(bgTex);

	lamp[0].setPosition(Window::WIDTH - 200, 140);
	lamp[0].setScale(4, 4);
	lamp[1].setPosition(50, 140);
	lamp[1].setScale(4, 4);

	alagard.loadFromFile("resources/fonts/alagard.ttf");
	Title.setFont(alagard);
	Summary.setFont(alagard);
	Restart.setFont(alagard);

	Title.setFillColor(sf::Color::White);
	Summary.setFillColor(sf::Color::White);
	Restart.setFillColor(sf::Color::White);

	Title.setString("You have perished...");
	Title.setCharacterSize(48);
	Summary.setString("However, not all hope\nis lost fair warrior.\nYou may try again from\nthe place where all\nbegan...");
	Summary.setCharacterSize(24);
	Restart.setString("restart");
	Restart.setCharacterSize(36);

	Title.setPosition((Window::WIDTH / 2) - (Title.getLocalBounds().width / 2), 100);
	Summary.setPosition((Window::WIDTH / 2) - (Title.getLocalBounds().width / 2), 
		Title.getPosition().y + Title.getLocalBounds().height + 50);
	Restart.setPosition((Window::WIDTH / 2) - (Title.getLocalBounds().width / 2),
		Summary.getPosition().y + Summary.getLocalBounds().height + 50);
}

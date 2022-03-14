#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow& t_window)
	:	window{ &t_window }
{
	titleTex.loadFromFile("resources/images/menu/title.png");
	title.setTexture(titleTex);
	logoTex.loadFromFile("resources/images/menu/logo/blink0.png");
	logo.setTexture(logoTex);
	playTex.loadFromFile("resources/images/menu/play1.png");
	play.setTexture(playTex);
	bgTex.loadFromFile("resources/images/menu/bgPixel/bg6.png");
	bg.setTexture(bgTex);
	lampTex.loadFromFile("resources/images/menu/lamp/lamp0.png");
	lamp.setTexture(lampTex);

	Setup();
}

void Menu::processEvents(sf::Event& ev)
{
}

void Menu::update(sf::Time& dt)
{
	if (play.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
	{
		playTex.loadFromFile("resources/images/menu/play2.png");
	}
	else
	{
		playTex.loadFromFile("resources/images/menu/play1.png");
	}

	if (bgTimer.getElapsedTime().asSeconds() > bgincrement)
	{
		if (bgcurrentFrame > 6) bgcurrentFrame = 0;
		bgTex.loadFromFile("resources/images/menu/bgPixel/bg" + std::to_string(bgcurrentFrame) + ".png");
		bgcurrentFrame++;
		bgTimer.restart();
	}

	if (logoTimer.getElapsedTime().asSeconds() > logoincrement)
	{
		if (logocurrentFrame == 1) logoincrement = 0.1f;
		if (logocurrentFrame > 5)
		{
			logoincrement = 2.5f;
			logocurrentFrame = 0;
		}
		logoTex.loadFromFile("resources/images/menu/logo/blink" + std::to_string(logocurrentFrame) + ".png");
		logocurrentFrame++;

		logoTimer.restart();
	}

	if (lampTimer.getElapsedTime().asSeconds() > lampincrement)
	{
		if (lampcurrentFrame > 3) lampcurrentFrame = 0;
		lampTex.loadFromFile("resources/images/menu/lamp/lamp" + std::to_string(lampcurrentFrame) + ".png");
		lampcurrentFrame++;
		lampTimer.restart();
	}
}

void Menu::render()
{
	window->clear(sf::Color::Black);
	window->draw(bg);
	window->draw(title);
	window->draw(lamp);
	window->draw(logo);
	window->draw(play);
}

void Menu::Setup()
{
	title.setPosition(50,50);
	title.setScale(1.5f,1.5f);
	logo.setScale(4,4);
	logo.setPosition(600,300);
	lamp.setPosition(450, 150);
	lamp.setScale(4, 4);
	play.setPosition(50, 200);
}

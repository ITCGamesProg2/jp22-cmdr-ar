#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow& t_window)
	:	window{ &t_window }, lamp_anim{ lamp }, logo_anim{ logo }
{
	titleTex.loadFromFile("resources/images/menu/title.png");
	title.setTexture(titleTex);
	playTex.loadFromFile("resources/images/menu/play1.png");
	play.setTexture(playTex);
	bgTex.loadFromFile("resources/images/menu/bgPixel/bg6.png");
	bg.setTexture(bgTex);
	// 2.5f
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			playClicked = true;
		}
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

	logo_anim.update();
	lamp_anim.update();
}

void Menu::render()
{
	window->clear(sf::Color::Black);

	window->draw(bg);
	window->draw(title);
	window->draw(lamp);
	window->draw(logo);
	window->draw(play);

	window->display();
}

void Menu::Setup()
{
	lamp_anim.Setup(45,45,4,1);
	lamp_anim.playAnim(0.25f,0,4);
	lampTex.loadFromFile("resources/images/menu/lamp/lampSheet.png");
	lamp.setTexture(lampTex);

	logo_anim.Setup(52, 33, 6, 1);
	logo_anim.playAnim(2.5f, 0, 6);
	logoTex.loadFromFile("resources/images/menu/logo/spritesheet.png");
	logo.setTexture(logoTex);

	title.setPosition(50,50);
	title.setScale(1.5f,1.5f);
	logo.setScale(4,4);
	logo.setPosition(600,250);
	lamp.setPosition(440, 140);
	lamp.setScale(4, 4);
	play.setPosition(50, 200);
}

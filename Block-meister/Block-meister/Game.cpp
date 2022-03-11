#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "MMMMMMMM MONMKLENEKENEEEE" }
{
	state = State::Menu;
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}

		switch (state)
		{
		case State::Menu:
			break;
		case State::Game:
			break;
		}
	}
}

void Game::update(sf::Time dt)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	switch (state)
	{
	case State::Menu:
		break;
	case State::Game:
		break;
	}
}

void Game::render()
{
	m_window.clear(sf::Color::White);

	switch (state)
	{
	case State::Menu:
		break;
	case State::Game:
		break;
	}

	m_window.display();
}

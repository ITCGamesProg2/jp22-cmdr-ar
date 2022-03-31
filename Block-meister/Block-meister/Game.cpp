#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 1024U, 576U, 32U }, "Block-Meister" },
	menu{ m_window }, level{ m_window }, deadMenu{ m_window }
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
			level.saveGame();
		}

		switch (state)
		{
		case State::Menu:
			menu.processEvents(newEvent);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			{
				level.editorOn();
			}
			break;
		case State::Game:
			level.processEvents(newEvent);
			break;
		case State::Dead:
			deadMenu.processEvents(newEvent);
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
		menu.update(dt);
		if (menu.playClicked)
		{
			state = State::Game;
		}
		break;
	case State::Game:
		level.update(dt);
		if (!level.player.getAlive() && deadTimer.getElapsedTime().asSeconds() > 6.f)
		{
			deadTimer.restart();
		}
		else if (!level.player.getAlive() && deadTimer.getElapsedTime().asSeconds() > 5.f)
		{
			state = State::Dead;
			m_window.setView(m_window.getDefaultView());
			level.savedAfterDeath = false;
		}

		break;
	case State::Dead:
		deadMenu.update(dt);
		if (deadMenu.restartClicked)
		{
			deadMenu.restartClicked = false;
			state = State::Game;
			level.clearAllVectors();
			level.loadLevel();
		}
		break;
	}
}

void Game::render()
{
	switch (state)
	{
	case State::Menu:
		menu.render();
		break;
	case State::Game:
		level.render();
		break;
	case State::Dead:
		deadMenu.render();
		break;
	}
}

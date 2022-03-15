#include "Player.h"

Player::Player(sf::RenderWindow& t_window)
	:	window{ &t_window }
{
	tex.loadFromFile("resources/images/game/player/downFrames/down0.png");
	body.setTexture(tex);
	body.setScale(2,2);
	body.setPosition(200, 200);
	body.setOrigin(sf::Vector2f(body.getLocalBounds().width/2, body.getLocalBounds().height / 2));
	view.reset(sf::FloatRect(0, 0, 1024, 576));
}

void Player::processEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::W)
		{
			moveBy.y = -1;
			up = true;
			down = false;
			lastMovedUp = true;
		}
		if (ev.key.code == sf::Keyboard::D)
		{
			moveBy.x = 1;
			otherKey = true;
		}
		if (ev.key.code == sf::Keyboard::S)
		{
			moveBy.y = 1;
			down = true;
			up = false;
			lastMovedUp = false;
		}
		if (ev.key.code == sf::Keyboard::A)
		{
			moveBy.x = -1;
			otherKey = true;
		}
	}
	if (ev.type == sf::Event::KeyReleased)
	{
		if (ev.key.code == sf::Keyboard::W)
		{
			up = false;
			moveBy.y = 0;
		}
		if (ev.key.code == sf::Keyboard::D)
		{
			moveBy.x = 0;
			otherKey = false;
		}
		if (ev.key.code == sf::Keyboard::S)
		{
			down = false;
			moveBy.y = 0;
		}
		if (ev.key.code == sf::Keyboard::A)
		{
			moveBy.x = 0;
			otherKey = false;
		}
	}
}

void Player::update(sf::Time& dt)
{
	animate();
	body.move(moveBy * speed * dt.asSeconds());
	view.setCenter(body.getPosition());
}

void Player::render()
{
	window->setView(view);
	window->draw(body);
}

void Player::animate()
{
	if (Timer.getElapsedTime().asSeconds() > increment)
	{
		if (up || down)
		{
			if (currentFrame > 1) currentFrame = 0;
			if (down) tex.loadFromFile("resources/images/game/player/downFrames/down" + std::to_string(currentFrame) + ".png");
			if (up) tex.loadFromFile("resources/images/game/player/upFrames/up" + std::to_string(currentFrame) + ".png");
			currentFrame++;
			Timer.restart();
		}
		else if (otherKey)
		{
			if (currentFrame > 1) currentFrame = 0;
			if (!lastMovedUp) tex.loadFromFile("resources/images/game/player/downFrames/down" + std::to_string(currentFrame) + ".png");
			if (lastMovedUp) tex.loadFromFile("resources/images/game/player/upFrames/up" + std::to_string(currentFrame) + ".png");
			currentFrame++;
			Timer.restart();
		}
		else
		{
			if (lastMovedUp) tex.loadFromFile("resources/images/game/player/up.png");
			else tex.loadFromFile("resources/images/game/player/down.png");
		}
	}
}

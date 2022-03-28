#include "Player.h"

Player::Player(sf::RenderWindow& t_window)
	: window{ &t_window }, anim{ body }, health{ 300,25,50 }
{
	tex.loadFromFile("resources/images/game/player/downFrames/spritesheet.png");
	//animation setup
	anim.Setup(52, 33, 2, 1);
	anim.playAnim(0.15f, 0, 2);
	anim.pause();

	body.setTexture(tex);
	body.setScale(2, 2);
	body.setPosition(200, 200);
	body.setOrigin(sf::Vector2f(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2));
	view.reset(sf::FloatRect(0, 0, 1024, 576));

	//Next movement bounds
	nextMovement.setSize(sf::Vector2f{ 52 * 2, 33 * 2 });
	nextMovement.setFillColor(sf::Color::Red);
	nextMovement.setOrigin((52 * 2) / 2, (33 * 2) / 2);
	
	//health
	health.setBarColour(sf::Color::Red);
}


void Player::processEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		currentDirection = Direction::UpRight;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentDirection = Direction::UpLeft;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		currentDirection = Direction::DownRight;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentDirection = Direction::DownLeft;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		currentDirection = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentDirection = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		currentDirection = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		currentDirection = Direction::Right;
	}
	else
	{
		currentDirection = Direction::None;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		dodge();
	}
}

void Player::setMovement()
{
	switch (currentDirection)
	{
	case Direction::Up:
		moveBy = { 0,-1 };
		break;
	case Direction::Down:
		moveBy = { 0,1 };
		break;
	case Direction::Left:
		moveBy = { -1,0 };
		break;
	case Direction::Right:
		moveBy = { 1,0 };
		break;
	case Direction::UpRight:
		moveBy = { 0.5, -0.5 };
		break;
	case Direction::UpLeft:
		moveBy = { -0.5, -0.5 };
		break;
	case Direction::DownLeft:
		moveBy = { -0.5, 0.5 };
		break;
	case Direction::DownRight:
		moveBy = { 0.5, 0.5 };
		break;
	case Direction::None:
		moveBy = { 0,0 };
		break;
	}
}

void Player::update(sf::Time& dt)
{
	m_dt = dt;
	if (!dodging)
	{
		animate();
		setMovement();
	}
	if (dodging)
	{
		animateDodge(dt);
		dodge();
	}

	body.move(moveBy * speed * dt.asSeconds());
	nextMovement.setPosition(body.getPosition() + (moveBy * speed * dt.asSeconds()));
	view.setCenter(body.getPosition());
}

void Player::render()
{
	window->setView(view);
	window->draw(nextMovement);
	window->draw(body);
}

void Player::bump()
{
	currentDirection = Direction::None;
	sf::Vector2f x = { -1.0f * moveBy.x, -1.0f * moveBy.y };
	body.move(x * speed * m_dt.asSeconds());
}

void Player::animateDodge(sf::Time& dt)
{
	if (dodgeTimer.getElapsedTime().asSeconds() < 0.1f)
	{
		sf::Vector2f scaleBy{ 0.f, 10 * dt.asSeconds() };
		alpha -= dt.asSeconds() * 3000;
		if (alpha < 0.f) alpha = 0.f;
		body.setScale(body.getScale() + scaleBy);
		body.setColor(sf::Color(255, 255, 255, alpha));
	}
	else if (dodgeTimer.getElapsedTime().asSeconds() > 0.4f)
	{
		sf::Vector2f scaleBy{ 0.f, 10 * dt.asSeconds() };
		alpha += dt.asSeconds() * 3000;
		if (alpha > 255.f) alpha = 255.f;
		body.setScale(body.getScale() - scaleBy);
		body.setColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		body.setColor(sf::Color(255, 255, 255, 0));
	}
}

void Player::dodge()
{
	if (dodgeTimer.getElapsedTime().asSeconds() > 0.5f && !dodging)
	{
		speed *= 5;
		setMovement();
		dodging = true;
		dodgeTimer.restart();
	}
	else if (dodgeTimer.getElapsedTime().asSeconds() > 0.5f && dodging)
	{
		dodging = false;
		dodgeTimer.restart();
		speed /= 5;
		//anim
		body.setScale(2.f, 2.f);
		body.setColor(sf::Color(255, 255, 255, 255));
	}
}

void Player::animate()
{
	anim.update();

	if (currentDirection == Direction::None)
	{
		anim.pause();
	}
	else
	{
		anim.play();
	}
}

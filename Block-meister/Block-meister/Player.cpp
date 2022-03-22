#include "Player.h"

Player::Player(sf::RenderWindow& t_window)
	: window{ &t_window }, anim{ body }
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

void Player::boundsCollision(sf::Time& dt)
{
	//Left Side Bounds
	if (nextMovement.getPosition().x - (nextMovement.getGlobalBounds().width * 0.5) < 0)
	{
		currentDirection = Direction::None;
		body.move(sf::Vector2f{ 1,0 } *speed * dt.asSeconds());
	}
	//Right Side Bounds
	if (nextMovement.getPosition().x + (nextMovement.getGlobalBounds().width * 0.5) > Window::WIDTH)
	{
		currentDirection = Direction::None;
		body.move(sf::Vector2f{ -1,0 } *speed * dt.asSeconds());
	}
	//Top Side Bounds
	if (nextMovement.getPosition().y - (nextMovement.getGlobalBounds().height * 0.5) < 0)
	{
		currentDirection = Direction::None;
		body.move(sf::Vector2f{ 0,1 } *speed * dt.asSeconds());
	}
	//Bottom Side Bounds
	if (nextMovement.getPosition().y + (nextMovement.getGlobalBounds().width * 0.5) > Window::HEIGHT)
	{
		currentDirection = Direction::None;
		body.move(sf::Vector2f{ 0,-1 } *speed * dt.asSeconds());
	}
}

void Player::update(sf::Time& dt)
{
	m_dt = dt;
	animate();
	setMovement();
	boundsCollision(dt);
	body.move(moveBy * speed * dt.asSeconds());
	nextMovement.setPosition(body.getPosition() + (moveBy * speed * dt.asSeconds()));
	//view.setCenter(body.getPosition());
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

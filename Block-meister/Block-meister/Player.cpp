#include "Player.h"

Player::Player(sf::RenderWindow& t_window)
	: window{ &t_window }, anim{ body }, healthBar{ 300,25,50 }
{
	tex.loadFromFile("resources/images/game/player/downFrames/spritesheet.png");
	shadowTex.loadFromFile("resources/images/game/player/downFrames/shadow.png");
	//animation setup
	anim.Setup(52, 33, 2, 1);
	anim.playAnim(0.15f, 0, 2);
	anim.pause();

	body.setTexture(tex);
	body.setScale(2, 2);
	body.setPosition(200, 200);
	body.setOrigin(sf::Vector2f(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2));
	view.reset(sf::FloatRect(0, 0, 1024, 576));

	shadow.setTexture(shadowTex);
	shadow.setScale(2, 2);
	shadow.setPosition(200, 200);
	shadow.setOrigin(sf::Vector2f(shadow.getLocalBounds().width / 2, shadow.getLocalBounds().height / 2));

	//Next movement bounds
	nextMovement.setSize(sf::Vector2f{ 52 * 2, 33 * 2 });
	nextMovement.setFillColor(sf::Color::Red);
	nextMovement.setOrigin((52 * 2) / 2, (33 * 2) / 2);

	//health
	healthBar.setBarColour(sf::Color::Red);
	health = MAX_HEALTH;
	healthBar.setMaxHealth(MAX_HEALTH);

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
	if (alive)
	{
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
		knockbackEntity();
		body.move(moveBy * speed * dt.asSeconds());
		shadow.setPosition(body.getPosition().x, body.getPosition().y + body.getLocalBounds().height);
		nextMovement.setPosition(body.getPosition() + (moveBy * speed * dt.asSeconds()));
	}

	view.setCenter(body.getPosition());

	// Red/White Highlight when damaged
	if (timer(0.1, highlightTimer) && !dodging)
	{
		body.setColor(sf::Color::White);
	}
	if (!alive)
	{
		body.setRotation(-90);
	}
}

void Player::render()
{
	window->setView(view);
	//window->draw(nextMovement);
	window->draw(shadow);
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
		dodging = true;
		speed = DASH_SPEED;
		setMovement();

		dodgeTimer.restart();
	}
	else if (dodgeTimer.getElapsedTime().asSeconds() > 0.5f && dodging)
	{
		dodging = false;
		speed = MAX_SPEED;

		dodgeTimer.restart();

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

void Player::knockbackEntity()
{
	if (!timer(0.3, knockbackDuration) && knockback)
	{
		speed *= 0.90;

		if (dodging)
		{
			dodgingKnockedback = true;
		}

		if (dodgingKnockedback)
		{
			knockbackStrength = 1;
		}
		else {
			knockbackStrength = 5.5;
		}

		moveBy = knockbackDirection * knockbackStrength;
	}
	else if (timer(0.3, knockbackDuration) && knockback)
	{
		knockback = false;
		dodgingKnockedback = false;
		knockbackDuration.restart();
		speed = MAX_SPEED;
	}

	//Fixes bug where player remains slow after bouncing
	if (!knockback && speed < 50)
	{
		speed = MAX_SPEED;
	}
}

bool Player::timer(float t_desiredTime, sf::Clock t_timer)
{
	sf::Time timePasted = t_timer.getElapsedTime();
	float secondsPasted = timePasted.asSeconds();
	float desiredTimer = t_desiredTime;

	if (secondsPasted >= desiredTimer)
	{
		return true;
	}
	return false;
}

void Player::damagePlayer(float t_damage)
{
	if (timer(0.3, iFrames))
	{
		if (health > 0)
		{
			health -= t_damage;
			healthBar.takeDamage(t_damage);
		}
		if (health <= 0)
		{
			health = 0;
			alive = false;
		}
		body.setColor(sf::Color::Red);
		iFrames.restart();
		highlightTimer.restart();
	}
}

void Player::damageSelf()
{
	if (health > 0)
	{
		health -= ATTACK_SELF_DAMAGE;
		healthBar.takeDamage(ATTACK_SELF_DAMAGE);
	}
	if (health <= 0)
	{
		health = 0;
		alive = false;
	}
}

void Player::heal(float t_value)
{
	health += t_value;
	if (health > MAX_HEALTH)
	{
		health = MAX_HEALTH;
	}
	healthBar.heal(t_value);
}


void Player::getKnockbackDirection(sf::Sprite t_sprite)
{
	knockback = true;
	speed = MAX_SPEED;
	knockbackDuration.restart();

	sf::Vector2f t_direction = t_sprite.getPosition() - body.getPosition();
	float vectorLength = sqrt(t_direction.x * t_direction.x + t_direction.y * t_direction.y);
	t_direction = t_direction / vectorLength;

	knockbackDirection = -t_direction;
}

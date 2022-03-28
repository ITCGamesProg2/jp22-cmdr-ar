#include "Enemy.h"
sf::RenderWindow* Enemy::window = nullptr;
Player* Enemy::player = nullptr;

Enemy::Enemy()
{
}

void Enemy::SetTexture(const char* path)
{
	tex.loadFromFile(path);
	body.setTexture(tex);
}

void Enemy::SetTexture(EnemyType _type)
{
	enemyType = _type;
	switch (_type)
	{
	case EnemyType::Slime:
		tex.loadFromFile("resources/images/game/enemies/slime/slime.png");
		break;
	default:
		tex.loadFromFile("resources/images/game/enemies/slime/slime.png");
		break;
	}
	body.setTexture(tex);
	body.setOrigin((body.getGlobalBounds().width * 2) / 2, (body.getGlobalBounds().height * 2) / 2);
	body.setOrigin((body.getLocalBounds().width / 2), (body.getLocalBounds().height / 2));
	//Next movement bounds
	nextMovement.setSize(sf::Vector2f{ body.getGlobalBounds().width * 2, body.getGlobalBounds().height * 2 });
	nextMovement.setFillColor(sf::Color::Red);
	nextMovement.setOrigin((nextMovement.getLocalBounds().width / 2), (nextMovement.getLocalBounds().height / 2));
}

void Enemy::changeType(EnemyType type)
{
	switch (type)
	{
	case EnemyType::Slime:
		//Slime body
		SetTexture(EnemyType::Slime);
		setScale(2.0f, 2.0f);
		body.setOrigin((body.getLocalBounds().width / 2), (body.getLocalBounds().height / 2));
		break;
	}

	enemyType = type;
	SetTexture(type);
}


void Enemy::processEvents(sf::Event& ev)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		charging = true;
		std::cout << "Charge" << std::endl;
	}
}

void Enemy::update(sf::Time& dt)
{
	m_dt = dt;
	nextMovement.setPosition(body.getPosition());
	bump();
	if (enemyType == EnemyType::Slime)
	{
		slimeCharge(dt);
	}
}

void Enemy::render()
{
	window->draw(nextMovement);
	window->draw(body);
}

void Enemy::slimeCharge(sf::Time& dt)
{
	if (charging)
	{
		// Sets charge to true when timer is ready
		if (timer(2, chargePrep) && chargeActive == false)
		{
			chargeActive = true;
			speed = CHARGE_SPEED;
			directionTowardsPlayer();
			direction = playerDirection;
			chargePrep.restart();
		}

		// Starts charging when ready
		if (chargeActive)
		{
			body.move(playerDirection * CHARGE_SPEED * dt.asSeconds());
			nextMovement.setPosition(body.getPosition() + (playerDirection * CHARGE_SPEED * dt.asSeconds()));

			// Resets movement values when charge is over ( 2.0s - 2.5s = 0.5s charge duration)
			if (timer(2.5, chargeDuration))
			{
				chargeActive = false;
				charging = false;
				speed = SLIME_SPEED;
			}
		}
	}
	else
	{
		chargeDuration.restart();
		chargePrep.restart();
	}
}

void Enemy::getBounceDirection(sf::Sprite t_sprite)
{
	float X1 = abs((body.getGlobalBounds().left + body.getGlobalBounds().width) - t_sprite.getGlobalBounds().left);
	float X2 = abs(body.getGlobalBounds().left - (t_sprite.getGlobalBounds().left + t_sprite.getGlobalBounds().width));
	float Y1 = abs(body.getGlobalBounds().top - (t_sprite.getGlobalBounds().top + t_sprite.getGlobalBounds().height));
	float Y2 = abs((body.getGlobalBounds().top + body.getGlobalBounds().height) - t_sprite.getGlobalBounds().top);

	// Bottom side collision
	if (direction.y < 0 && Y1 < Y2 && Y1 < X1 && Y1 < X2)
	{
		direction.y = -1 * direction.y;
	}
	// Top side collision
	if (direction.y > 0 && Y2 < Y1 && Y2 < X1 && Y2 < X2)
	{
		direction.y = -1 * direction.y;
	}
	// Left side collision
	if (direction.x > 0 && X1 < X2 && X1 < Y1 && X1 < Y2)
	{
		direction.x = -1 * direction.x;
	}
	// Right side collision
	if (direction.x < 0 && X2 < X1 && X2 < Y1 && X2 < Y2)
	{
		direction.x = -1 * direction.x;
	}

	if (direction.x == 0 || direction.y == 0)
	{
		directionTowardsPlayer();
		direction = -playerDirection;
	}

	bumpDuration.restart();
	speed = SLIME_SPEED;
}

void Enemy::directionTowardsPlayer()
{
	sf::Vector2f t_direction = player->getPos() - body.getPosition();
	float vectorLength = sqrt(t_direction.x * t_direction.x + t_direction.y * t_direction.y);
	t_direction = t_direction / vectorLength;

	playerDirection = t_direction;
}

void Enemy::setKnockback(bool t_knockback)
{
	knockback = t_knockback;
	bumpDuration.restart();

	//Slime stuff
	charging = false;
}

bool Enemy::timer(float t_desiredTime, sf::Clock t_timer)
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

/// <summary>
/// Work in progress
/// </summary>
void Enemy::bump()
{
	if (!timer(0.5, bumpDuration) && knockback)
	{
		speed *= 0.92;
		body.move(direction * speed * m_dt.asSeconds());
	}
	if (timer(0.5, bumpDuration) && knockback)
	{
		knockback = false;

		//Slime stuff
		speed = SLIME_SPEED;
		chargeActive = false;
		charging = false;
		chargeDuration.restart();
		chargePrep.restart();
	}

}


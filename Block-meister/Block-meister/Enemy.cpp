#include "Enemy.h"
sf::RenderWindow* Enemy::window = nullptr;
Player* Enemy::player = nullptr;

Enemy::Enemy() 
	: healthBar{100, 18, 0}
{
	//health
	healthBar.setBarColour(sf::Color(255,0,0,200));
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
	case EnemyType::Beetle:
		tex.loadFromFile("resources/images/game/enemies/beetle/beetle.png");
		break;
	}

	body.setTexture(tex);
	body.setOrigin((body.getLocalBounds().width / 2), (body.getLocalBounds().height / 2));
	body.setScale(2.0f, 2.0f);

	//Next movement bounds
	nextMovement.setSize(sf::Vector2f{ body.getLocalBounds().width * 2, body.getLocalBounds().height * 2 });
	nextMovement.setFillColor(sf::Color::Red);
	nextMovement.setOrigin((nextMovement.getLocalBounds().width / 2), (nextMovement.getLocalBounds().height / 2));
}

void Enemy::changeType(EnemyType type)
{
	switch (type)
	{
	case EnemyType::Slime:
		SetTexture(EnemyType::Slime);
		//Health
		health = SLIME_HEALTH;
		healthBar.setMaxHealth(SLIME_HEALTH);

		break;
	case EnemyType::Beetle:
		SetTexture(EnemyType::Beetle);
		//Health
		health = BEETLE_HEALTH;
		healthBar.setMaxHealth(BEETLE_HEALTH);

		break;
	}

	enemyType = type;
	SetTexture(type);
}


void Enemy::processEvents(sf::Event& ev)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if (enemyType == EnemyType::Slime)
		{
			charging = true;
		}
	}
}

void Enemy::update(sf::Time& dt)
{
	if (alive)
	{
		m_dt = dt;
		nextMovement.setPosition(body.getPosition());
		placeHealthBar();
		bump();
		if (enemyType == EnemyType::Slime)
		{
			slimeCharge(dt);
		}
		beetleInitiateAim();
	}
}

void Enemy::render()
{
	if (alive)
	{
		window->draw(nextMovement);
		window->draw(body);
		healthBar.render(*window);
	}
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

sf::Vector2f* Enemy::getTriAim()
{
	if (alive)
	{
		float rotation[3] = { thor::polarAngle(playerDirection) - 30, thor::polarAngle(playerDirection) + 30, thor::polarAngle(playerDirection) };

		for (size_t i = 0; i < 3; i++)
		{
			rotation[i] = rotation[i] * 3.1416 / 180;

			triAim[i].x = cos(rotation[i]);
			triAim[i].y = sin(rotation[i]);
		}
		return triAim;
	}
	else {
		return nullptr;
	}
}

void Enemy::beetleInitiateAim()
{
	if (timer(2, beetleAim) && beetleReady && enemyType == EnemyType::Beetle)
	{
		beetleAttacking = true;
		beetleReady = false;
	}
	else if (timer(3, beetleAim) && enemyType == EnemyType::Beetle)
	{
		tex.loadFromFile("resources/images/game/enemies/beetle/beetle.png");
	}
}

void Enemy::beetleReadyup()
{
	if (enemyType == EnemyType::Beetle)
	{
		beetleReady = true;
		directionTowardsPlayer();
		body.setRotation(thor::polarAngle(playerDirection));
		tex.loadFromFile("resources/images/game/enemies/beetle/beetle_attack.png");
		beetleAim.restart();
	}
}

bool Enemy::getParticleReady()
{
	if (!alive && particleReady)
	{
		particleReady = false;
		return true;
	}
	else
	{
		return false;
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

	if (direction.x == 0 && direction.y == 0)
	{
		directionTowardsPlayer();
		direction = -playerDirection;
	}
	bumpDuration.restart();
}

void Enemy::getBounceDirection()
{
	sf::Vector2f t_direction = player->getPos() - body.getPosition();
	float vectorLength = sqrt(t_direction.x * t_direction.x + t_direction.y * t_direction.y);
	t_direction = t_direction / vectorLength;

	direction = -t_direction;
}

void Enemy::directionTowardsPlayer()
{
	sf::Vector2f t_direction = player->getPos() - body.getPosition();
	float vectorLength = sqrt(t_direction.x * t_direction.x + t_direction.y * t_direction.y);
	t_direction = t_direction / vectorLength;

	playerDirection = t_direction;
}

void Enemy::setAlive(bool t_alive)
{
	alive = t_alive;
	if (!alive)
	{
		particleReady = true;
	}
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

void Enemy::damageEnemy(float t_damage)
{
	if (timer(0.1, iFrames))
	{
		if (health > 0)
		{
			health -= t_damage;
			healthBar.takeDamage(t_damage);
		}
		if (health <= 0)
		{
			health = 0;
			setAlive(false);
		}
		iFrames.restart();
	}
}

void Enemy::placeHealthBar()
{
	float x = body.getPosition().x - body.getLocalBounds().width * body.getScale().x + (body.getLocalBounds().width * body.getScale().x * 0.23f);
	float y = body.getPosition().y - body.getLocalBounds().height * body.getScale().y - (body.getLocalBounds().height * body.getScale().x * 0.5f);

	healthBar.setPos(x, y);
}

void Enemy::setMovement()
{
	switch (currentDirection)
	{
	case EnemyDirection::Up:
		directionRotation = 0;
		break;
	case EnemyDirection::Down:
		directionRotation = 0;
		break;
	case EnemyDirection::Left:
		directionRotation = 0;
		break;
	case EnemyDirection::Right:
		directionRotation = 0;
		break;
	case EnemyDirection::None:
		directionRotation = 0;
		break;
	}
}


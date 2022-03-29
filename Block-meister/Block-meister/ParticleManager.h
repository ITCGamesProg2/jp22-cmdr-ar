#pragma once
#include <Thor/Particles.hpp>
#include <SFML/Graphics.hpp>
#include <Thor/Math/Distributions.hpp>
#include <Thor/Animations.hpp>
#include "Enemy.h"

class ParticleManager
{
public:
	ParticleManager();
	static sf::RenderWindow* window;

	void update(sf::Time& dt);
	void render();
	void createParticle(EnemyType type, sf::Vector2f pos);
	bool timer(float t_desiredTime, sf::Clock t_timer);

private:
	sf::Texture tex;
	sf::Vector2f velocity{ 190, 190 };
	sf::Clock particalTimer;
	bool active{ false };

	thor::UniversalEmitter emitter;
	thor::ParticleSystem system;
};


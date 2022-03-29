#include "ParticleManager.h"
sf::RenderWindow* ParticleManager::window = nullptr;

ParticleManager::ParticleManager()
{
	tex.loadFromFile("resources/images/game/particle.png");

	//setting emitter
	emitter.setEmissionRate(100);
	emitter.setParticleLifetime(sf::seconds(0.4f));
	emitter.setParticleRotation(thor::Distributions::uniform(0, 360));

	// Create particle system, add reference to emitter
	system.setTexture(tex);
	system.addEmitter(thor::refEmitter(emitter));

	thor::FadeAnimation fader(0.1f, 0.1f);

	// Affectors
	system.addAffector(thor::TorqueAffector(150.f));
	system.addAffector(thor::AnimationAffector(fader));
}

void ParticleManager::update(sf::Time& dt)
{

	emitter.setParticleVelocity(thor::Distributions::deflect(velocity, 360.f));
	system.update(dt);

	if (!timer(0.2, particalTimer) && active == true)
	{
		emitter.setEmissionRate(100);
	}
	else 
	{
		emitter.setEmissionRate(0);
		active = false;
	}
}

void ParticleManager::render()
{
	window->draw(system);
}

void ParticleManager::createParticle(EnemyType type, sf::Vector2f pos)
{
	if (type == EnemyType::Slime)
	{
		tex.loadFromFile("resources/images/game/particle.png");
	}
	system.setTexture(tex);

	active = true;
	particalTimer.restart();
	emitter.setParticlePosition(pos);
}

bool ParticleManager::timer(float t_desiredTime, sf::Clock t_timer)
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
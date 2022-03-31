#include "HealthBar.h"

HealthBar::HealthBar(float width, float height, int maxhp)
	:	maxHP{ maxhp }, maxBar{ width - 10 }
{
	currentHP = maxHP;
	bg.setSize({ width, height });
	bg.setFillColor(sf::Color(255, 255, 255, 170));
	bar.setSize({ width - 10, height - 10});
	bar.setPosition(5,5);
	barXAsPercent = maxBar / 100.f;
}

void HealthBar::takeDamage(int dmg)
{
	if (!dead)
	{
		currentHP -= dmg;
		if (currentHP <= 0)
		{
			dead = true;
			bar.setSize({ 0, bar.getSize().y });
			return;
		}

		float hpAsPercent = ((float)currentHP / (float)maxHP) * 100.f;
		bar.setSize({ barXAsPercent * hpAsPercent, bar.getSize().y });
	}
}

void HealthBar::heal(int t_value)
{
	currentHP += t_value;
	if (currentHP > maxHP)
	{
		currentHP = maxHP;
	}
	float hpAsPercent = ((float)currentHP / (float)maxHP) * 100.f;
	bar.setSize({ barXAsPercent * hpAsPercent, bar.getSize().y });
}

void HealthBar::setPos(float x, float y)
{
	bg.setPosition(x,y);
	bar.setPosition(x + 5,y + 5);
}

void HealthBar::render(sf::RenderWindow& window)
{
	window.draw(bg);
	window.draw(bar);
}

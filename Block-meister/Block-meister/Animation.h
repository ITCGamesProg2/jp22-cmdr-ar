#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Sprite& _sprite);
	void Setup(int _frameWidth, int _frameHeight, int _noOfFramesHorizontal, int _noOfFramesVertical);

	//operations
	int getCurrentPosX() { return currentPosHorizontal; }
	int getCurrentPosY() { return currentPosVertical; }
	bool isPlaying() { return playing; }
	void play() { playing = true; }
	void pause() { playing = false; }

	void update();
	void playAnim(float _timePerFrame, int posVertical, int amountOfFramesHorizontal);
	void setWaitTime(float time) { waitBetweenAnims = time; }

private:
	sf::Sprite& sprite;
	int frameWidth = 0;
	int frameHeight = 0;
	int noOfFramesHorizontal = 0;
	int noOfFramesVertical = 0;

	int currentPosHorizontal = 0;
	int currentMaxHorizontal = 0;
	int currentPosVertical = 0;

	bool playing = false;
	float timePerFrame = 0.0f;
	sf::Clock animTimer;

	sf::Clock waitTimer;
	float waitBetweenAnims = 0.0f;
	bool waiting = false;
};


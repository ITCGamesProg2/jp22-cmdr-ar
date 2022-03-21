#include "Animation.h"

Animation::Animation(sf::Sprite& _sprite)
	:	sprite{ _sprite }
{
}

void Animation::Setup(int _frameWidth, int _frameHeight, int _noOfFramesHorizontal, int _noOfFramesVertical)
{
	frameWidth = _frameWidth;
	frameHeight = _frameHeight;
	noOfFramesHorizontal = _noOfFramesHorizontal;
	noOfFramesVertical = _noOfFramesVertical;
}

void Animation::update()
{
	if (playing)
	{
		if (waiting)
		{
			if (waitTimer.getElapsedTime().asSeconds() > waitBetweenAnims)
			{
				currentPosHorizontal++;
				waiting = false;
			}
		}
		if (animTimer.getElapsedTime().asSeconds() > timePerFrame && !waiting)
		{
			if (currentPosHorizontal > currentMaxHorizontal - 1) currentPosHorizontal = 0;

			///////////////////////////////////
			
			sprite.setTextureRect(sf::IntRect(currentPosHorizontal * frameWidth, currentPosVertical * frameHeight, 
											frameWidth, frameHeight));

			///////////////////////////////////

			if (currentPosHorizontal != 0 || waitBetweenAnims == 0.0f)
			{
				currentPosHorizontal++;
			}
			else if (waitBetweenAnims != 0.0f)
			{
				waiting = true;
				waitTimer.restart();
			}
			animTimer.restart();
		}
	}
}

void Animation::playAnim(float _timePerFrame, int posVertical, int amountOfFramesHorizontal)
{
	playing = true;
	timePerFrame = _timePerFrame;
	currentPosVertical = posVertical;
	currentMaxHorizontal = amountOfFramesHorizontal;
	animTimer.restart();
	sprite.setTextureRect(sf::IntRect(currentPosHorizontal * frameWidth, currentPosVertical * frameHeight,
		frameWidth, frameHeight));
	waitTimer.restart();
}

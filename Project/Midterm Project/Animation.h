#pragma once

#include "Sprite.h"
#include <Trackable.h>
#include <vector>

class Animation :public Trackable
{
public:

	Animation();
	Animation(std::vector<Sprite> spriteList);
	~Animation();

	void addSprite(Sprite sprite);
	void addSecondSprite(Sprite sprite);
	void update(float dt);
	Sprite* getCurrentSprite();
	void speedUp();
	void slowDown();
	void swapAnimation();

private:
	
	float mTimePerSprite;
	float mTimeRemaining;
	int mCurrentSprite;
	std::vector<Sprite> mSpriteList;
	std::vector<Sprite> mSecondSpriteList;
	bool mShouldLoop;
	bool mSecondAnimation;
};


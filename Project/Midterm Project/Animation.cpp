#include "Animation.h"

Animation::Animation()
{
	mCurrentSprite = 0;
	mTimePerSprite = 1;
	mTimeRemaining = mTimePerSprite;
	mShouldLoop = true;
	mSecondAnimation = false;

}

Animation::Animation(std::vector<Sprite> spriteList) 
{
	mCurrentSprite = 0;
	mTimePerSprite = 1;
	mTimeRemaining = mTimePerSprite;
	
	mSpriteList = spriteList;
	mShouldLoop = true;
	mSecondAnimation = false;
}

Animation::~Animation()
{
	
}

void Animation::addSprite(Sprite sprite)
{
	mSpriteList.push_back(sprite);
}

void Animation::addSecondSprite(Sprite sprite)
{
	mSecondSpriteList.push_back(sprite);
}

void Animation::update(float dt)
{
	mTimeRemaining -= dt;
	if (mTimeRemaining <= 0)
	{
		mCurrentSprite++;
		mTimeRemaining = mTimePerSprite;

		if (mCurrentSprite >= mSpriteList.size() && mShouldLoop) 
		{
			mCurrentSprite = 0;
		}
	}
}

Sprite* Animation::getCurrentSprite() 
{
	if (mSecondAnimation)
	{
		return &mSecondSpriteList[mCurrentSprite];
	}
	else
	{
		return &mSpriteList[mCurrentSprite];
	}
}

void Animation::speedUp() 
{
	mTimePerSprite -= .5; //may have to reverse
	if (mTimePerSprite <= 0)
	{
		mTimePerSprite = .1;
	}
}

void Animation::slowDown() 
{
	mTimePerSprite += .5; //may have to reverse
}

void Animation::swapAnimation()
{
	mSecondAnimation = !mSecondAnimation; //swaps the bool
}

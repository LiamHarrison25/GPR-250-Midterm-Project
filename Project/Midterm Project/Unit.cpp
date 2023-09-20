#include "Unit.h"
#include "Game.h"


Unit::Unit() 
{
	mpAnimation = nullptr;
	mPausedGame = false;
	mIsRed = true;

}

Unit::Unit(Animation* animation, Vector2D location, Vector2D velocity, float accel, float speed)
{
	mpAnimation = animation;
	mPausedGame = false;

	mLocation = location;
	mVelocity = velocity;

	mVelocity.normalize();
	mAccel = mVelocity;
	mAccel *= accel;
	
	mVelocity *= speed;
	mIsRed = true;
}

Unit::~Unit() 
{
	delete mpAnimation;
	mpAnimation = nullptr;

}

void Unit::setLocation(Vector2D newLocation)
{
	mLocation = newLocation;
}

Vector2D Unit::getLocation()
{
	return mLocation;
}

void Unit::update(float dt) 
{
	
	if (!mPausedGame)
	{
		//mVelocity += mAccel * (dt / 1000);
		mLocation += mVelocity * (dt / 1000); //converts to milliseconds 

		//Vector2D newLocation = mLocation;
		mpAnimation->update(dt);
	}
}

void Unit::draw() 
{
	//draw the current sprite in the location of the unit
	Game* game = Game::getInstance();
	game->drawFromGraphicsSystem(mLocation, mpAnimation->getCurrentSprite(), 1.0f); //draws the current sprite of the smurf onto the backbuffer

}

void Unit::setAnimation(GraphicsBuffer *buffer1, GraphicsBuffer *buffer2)
{

	Sprite firstSprite;
	firstSprite.setGraphicsBuffer(buffer1);
	std::vector<Sprite> spriteList;
	int i, j;
	for (i = 0; i <= SPRITE_NUM_COLUMNS; i++) 
	{
		for (j = 0; j <= SPRITE_NUM_ROWS; j++)
		{
			firstSprite.setWidth(SPRITE_WIDTH);
			firstSprite.setHeight(SPRITE_HEIGHT);
			firstSprite.setSourceLoc(Vector2D(SPRITE_WIDTH * i, SPRITE_HEIGHT * j + (SPRITE_NUM_ROWS + 1) * SPRITE_HEIGHT)); //set the location of the first sprite. 
			spriteList.push_back(firstSprite); //load the sprites into the vector //
			mpAnimation->addSprite(firstSprite);
		}

	}

	//create animation to hold the sprites 
	//Animation* spriteAnimation = new Animation(spriteList);

	Sprite secondSprite;
	secondSprite.setGraphicsBuffer(buffer2);
	for (i = 0; i <= SPRITE_NUM_COLUMNS; i++)
	{
		for (j = 0; j <= SPRITE_NUM_ROWS; j++)
		{
			secondSprite.setWidth(SPRITE_WIDTH);
			secondSprite.setHeight(SPRITE_HEIGHT);
			secondSprite.setSourceLoc(Vector2D(SPRITE_WIDTH * i + (SPRITE_NUM_COLUMNS + 1) * SPRITE_WIDTH, SPRITE_HEIGHT * j + (SPRITE_NUM_ROWS + 1) * SPRITE_HEIGHT)); //set the location of the second sprite 
			mpAnimation->addSecondSprite(secondSprite);
		}

	}
	//mpAnimation = spriteAnimation;
}

void Unit::changeAnimation()
{
	//switch to a new animation
	mpAnimation->swapAnimation();
}

void Unit::slowDownAnimation()
{
	mpAnimation->slowDown();
}
void Unit::speedUpAnimation()
{
	mpAnimation->speedUp();
}

void Unit::cleanup()
{
	delete mpAnimation;
}

void Unit::togglePausedGame()
{
	mPausedGame = !mPausedGame;
}


bool Unit::shouldBeDead()
{
	if (!isOnScreen())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Unit::isOnScreen()
{
	if (mLocation.getY() > DISP_HEIGHT || mLocation.getY() < 0)
	{
		return false;
	}
	else if (mLocation.getX() > DISP_WIDTH || mLocation.getX() < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Unit::getIsRed()
{
	return mIsRed;
}

void Unit::setIsRed(bool newBool)
{
	mIsRed = newBool;
}

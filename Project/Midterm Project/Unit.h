#pragma once

#include <PerformanceTracker.h>
#include "Animation.h"
#include "Vector2D.h"

//class Vector2D;
//class Animation;
class GraphicsBuffer;

class Unit :public Trackable
{
public:

	Unit();
	Unit(Animation* animation, Vector2D location, Vector2D velocity, float accel, float speed = 0.0f);
	~Unit();

	void update(float dt);
	void setLocation(Vector2D newLocation);
	Vector2D getLocation();
	void draw();
	void setAnimation(GraphicsBuffer *buffer1, GraphicsBuffer *buffer2);
	void changeAnimation();
	void slowDownAnimation();
	void speedUpAnimation();
	void cleanup();
	void togglePausedGame();
	bool shouldBeDead();
	bool isOnScreen();
	bool getIsRed();
	void setIsRed(bool newBool);

private:

	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const int SPRITE_NUM_COLUMNS = 5; //starts at 0
	const int SPRITE_NUM_ROWS = 3; //starts at 0
	const int SPRITE_WIDTH = 32;
	const int SPRITE_HEIGHT = 32;

	bool mPausedGame;
	Vector2D mLocation;
	Vector2D mVelocity;
	Vector2D mAccel;
	bool mIsRed;
	
	Animation* mpAnimation; 

};


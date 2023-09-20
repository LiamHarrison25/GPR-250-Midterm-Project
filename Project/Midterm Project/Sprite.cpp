#include "Sprite.h"

Sprite::Sprite() 
{
	mSourceLoc = Vector2D(0, 0);
	mHeight = DISP_HEIGHT;
	mWidth = DISP_WIDTH;
	mOwnsBuffer = false;
}

Sprite::Sprite(Vector2D sourceLoc, float height, float width, GraphicsBuffer* graphicsBuffer)
{
	mSourceLoc = sourceLoc;
	mHeight = height;
	mWidth = width;
	mGraphicsBuffer = graphicsBuffer;
	mOwnsBuffer = false;
}

Sprite::~Sprite()
{
	if (mOwnsBuffer)
	{
		delete mGraphicsBuffer;
		mGraphicsBuffer = nullptr;
	}
}


void Sprite::setSourceLoc(Vector2D sourceLoc) 
{
	mSourceLoc = sourceLoc;
}

Vector2D Sprite::getSourceLoc() 
{
	return mSourceLoc;
}

void Sprite::setWidth(float width) 
{
	mWidth = width;
}

float Sprite::getWidth()
{
	return mWidth;
}

void Sprite::setHeight(float height)
{
	mHeight = height;
}

float Sprite::getHeight()
{
	return mHeight;
}

void Sprite::setGraphicsBuffer(GraphicsBuffer* graphicsBuffer)
{
	mGraphicsBuffer = graphicsBuffer;
}

GraphicsBuffer* Sprite::getGraphicsBuffer()
{
	return mGraphicsBuffer;
}

void Sprite::cleanup()
{
	delete mGraphicsBuffer;
	mGraphicsBuffer = nullptr;
}
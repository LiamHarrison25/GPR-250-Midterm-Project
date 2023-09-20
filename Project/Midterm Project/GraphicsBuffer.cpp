#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer(const std::string& filename) //TODO:  
{
	//set mOwnsBitmap to true for this constructor
	mOwnsBitmap = true;

	mpBitmap = al_load_bitmap(filename.c_str());
	mWidth = DISP_WIDTH;
	mHeight = DISP_HEIGHT;

}

GraphicsBuffer::GraphicsBuffer(int width, int height) 
{
	//set mOwnsBitmap to true for this constructor
	mOwnsBitmap = true;
	mWidth = width;
	mHeight = height;
	mpBitmap = al_create_bitmap(mWidth, mHeight);
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_DISPLAY* pDisplay) 
{
	//call alDisplayBackbuffer. set mOwnsBitmap to false for this constructor
	mOwnsBitmap = false;
	mpBitmap = al_get_backbuffer(pDisplay);
	mWidth = DISP_WIDTH;
	mHeight = DISP_HEIGHT;
}

void GraphicsBuffer::setBitmapToColor( const ALLEGRO_COLOR& color)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);

	al_clear_to_color(color);

	al_set_target_bitmap(pOldTarget);
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mOwnsBitmap)
	{
		al_destroy_bitmap(mpBitmap);
	}
};

void GraphicsBuffer::setWidth(float width) 
{
	mWidth = width;
}

float GraphicsBuffer::getWidth() 
{
	return mWidth;
}

void GraphicsBuffer::setHeight(float height) 
{
	mHeight = height;
}

float GraphicsBuffer::getHeight() 
{
	return mHeight;
}

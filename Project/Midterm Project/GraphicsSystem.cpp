#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem() 
{
	mWidth = DISP_WIDTH;
	mHeight = DISP_HEIGHT;
	init();
	
}

GraphicsSystem::~GraphicsSystem() 
{
	cleanup();
}

void GraphicsSystem::setHeight(float height) 
{
	mHeight = height;
}
float GraphicsSystem::getHeight() 
{
	return mHeight;
}

void GraphicsSystem::setWidth(float width) 
{
	mWidth = width;
}

float GraphicsSystem::getWidth() 
{
	return mWidth;
}

void GraphicsSystem::init()  //Initializes the Graphics Buffer 
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);

	bool initSuccess;
	
	bool initSystem al_init();

	if (!al_init_image_addon())
	{
		initSuccess = false;
	}
	
	if (!al_init_primitives_addon())
	{
		initSuccess = false;
	}

	if (!al_init_font_addon())
	{
		initSuccess = false;
	}

	if (!al_init_ttf_addon())
	{
		initSuccess = false;
	}

	if (!al_install_keyboard())
	{
		initSuccess = false;
	}

	if (!al_install_mouse())
	{
		initSuccess = false;
	}

	bool audioInstal = al_install_audio();
	bool init_addon = al_init_acodec_addon();
	bool reserveSamples = al_reserve_samples(1); 

	if (audioInstal && init_addon && reserveSamples);
	else
	{
		initSuccess = false;
	}

	//creates the display
	mpDisplay = al_create_display(mWidth, mHeight); 
	assert(mpDisplay);

	
	//creates the backBuffer
	mpBuffer = new GraphicsBuffer(mpDisplay);
	assert(mpBuffer->mpBitmap);
	
}

void GraphicsSystem::cleanup()  
{
	//cleans up the memory

	delete mpBuffer;
	mpBuffer = nullptr;
	
	al_destroy_display(mpDisplay);
	mpDisplay = nullptr;
}

void GraphicsSystem::flip() //calls the al_flip function to display what is in the back buffer
{
	al_flip_display();
	
}

void GraphicsSystem::draw(Vector2D targetLoc, Sprite* sprite, float scale) //draws to current backbuffer
{

	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();

	al_set_target_bitmap(mpBuffer->mpBitmap);

	Vector2D destSize;
	Vector2D srcSize;
	Vector2D destLoc = targetLoc;
	Vector2D loc = sprite->getSourceLoc();

	srcSize.setX(sprite->mWidth);
	srcSize.setY(sprite->mHeight);

	destSize.setX(srcSize.getX() * scale);
	destSize.setY(srcSize.getY() * scale);

	al_draw_scaled_bitmap(sprite->mGraphicsBuffer->mpBitmap, loc.getX(), loc.getY(), srcSize.getX(), srcSize.getY(), destLoc.getX(), destLoc.getY(), destSize.getX(), destSize.getY(), 0);

	al_set_target_bitmap(pOldTarget);

}

void GraphicsSystem::draw(GraphicsBuffer* buffer, Vector2D loc, Sprite* sprite, float scale) 
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();

	al_set_target_bitmap(buffer->mpBitmap);

	Vector2D destSize;
	Vector2D srcSize;
	Vector2D destLoc = Vector2D(0, 0);

	srcSize.setX(sprite->mWidth);
	srcSize.setY(sprite->mHeight);

	destSize.setX(srcSize.getX() * scale);
	destSize.setY(srcSize.getY() * scale);

	al_draw_scaled_bitmap(sprite->mGraphicsBuffer->mpBitmap, loc.getX(), loc.getY(), srcSize.getX(), srcSize.getY(), destLoc.getX(), destLoc.getY(), destSize.getX(), destSize.getY(), 0);

	al_set_target_bitmap(pOldTarget);

}

void GraphicsSystem::writeText(Vector2D targetLoc, Font font, Color color, std::string text) 
{

	ALLEGRO_COLOR thisColor = al_map_rgba(color.getColor(0), color.getColor(1), color.getColor(2), color.getColor(3));

	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(mpBuffer->mpBitmap);

	al_draw_text(font.getFont(), thisColor, targetLoc.getX(), targetLoc.getY(), 1, text.c_str());

	al_set_target_bitmap(pOldTarget);
}

void GraphicsSystem::writeText(GraphicsBuffer* pDebuffer, Vector2D targetLoc, Font font, Color color, std::string text) 
{

	ALLEGRO_COLOR thisColor = al_map_rgba(color.getColor(0), color.getColor(1), color.getColor(2), color.getColor(3));

	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(pDebuffer->mpBitmap);

	al_draw_text(font.getFont(), thisColor, targetLoc.getX(), targetLoc.getY(), 1, text.c_str());

	al_set_target_bitmap(pOldTarget);
}

void GraphicsSystem::saveBuffer(GraphicsBuffer* buffer , std::string filename) 
{
	//saves the contents of the buffer to a file
	al_save_bitmap(filename.c_str(), buffer->mpBitmap);
}

void GraphicsSystem::saveBuffer(std::string filename)
{
	//saves the contents of the buffer to a file
	al_save_bitmap(filename.c_str(), mpBuffer->mpBitmap);
}

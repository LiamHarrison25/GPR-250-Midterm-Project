#pragma once
#include "GraphicsBuffer.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <Trackable.h>
#include <Vector2D.h>
#include "Sprite.h"
#include "Color.h"
#include <PerformanceTracker.h>
#include "Font.h"

const std::string INIT_TRACKER_NAME = "init";
const std::string DRAW_TRACKER_NAME = "draw";
const std::string WAIT_TRACKER_NAME = "wait";

const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;



class GraphicsBuffer; //forward declaration
class Font;
class Sprite;

//This class can have allegro
//creates and maintains the allegro display
class GraphicsSystem :public Trackable
{
public:

	//---constructors/destructor---
	GraphicsSystem();
	~GraphicsSystem();

	//---getters and setters---

	void setHeight(float height);
	float getHeight();

	void setWidth(float width);
	float getWidth();

	//---Other Functions---
	void init(); //Initializes the Graphics Buffer
	void cleanup(); //cleans up the memory

	void flip(); //calls the al_flip function to display what is in the back buffer

	void draw(Vector2D targetLoc, Sprite* sprite, float scale = 1.0); //draws to current backbuffer
	
	void draw(GraphicsBuffer* buffer, Vector2D loc, Sprite* sprite, float scale = 1.0);

	void writeText(Vector2D targetLoc, Font font, Color color, std::string text);

	void writeText(GraphicsBuffer* pDebuffer, Vector2D targetLoc, Font font, Color color, std::string text);

	void saveBuffer(GraphicsBuffer* buffer, std::string filename);

	void saveBuffer(std::string filename);


private:
		
	//private data
	ALLEGRO_DISPLAY* mpDisplay; 
	GraphicsBuffer* mpBuffer; //back buffer
	float mHeight;
	float mWidth;
	
};

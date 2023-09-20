#pragma once
#include <Trackable.h>
#include "GraphicsSystem.h"
#include <allegro5/allegro.h>
#include <Vector2D.h>

class GraphicsSystem; //forward declaration

//This class can have allegro
class GraphicsBuffer :public Trackable
{
	friend class GraphicsSystem;

public:

	

	//---constructors/destructor---
	GraphicsBuffer(); //default constructor
	GraphicsBuffer(const std::string& filename); //set mOwnsBitmap to true for this constructor 
	GraphicsBuffer(int width, int height); //set mOwnsBitmap to true for this constructor 

	GraphicsBuffer(GraphicsBuffer&) = delete; //copy constructor that prevents passing by value

	~GraphicsBuffer();


	//---getters and setters---

	void setWidth(float width); 
	float getWidth(); 

	void setHeight(float height); 
	float getHeight(); 

	//---other functions---

	void setBitmapToColor( const ALLEGRO_COLOR& color);

private:

	GraphicsBuffer(ALLEGRO_DISPLAY* pDisplay); //call alDisplayBackbuffer. set mOwnsBitmap to false for this constructor 

	//private data
	float mWidth; 
	float mHeight;
	bool mOwnsBitmap;
	ALLEGRO_BITMAP* mpBitmap; //pointer to the bitmap
	
};
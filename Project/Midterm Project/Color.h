#pragma once
#include <Trackable.h>

//create constants for the base colors

class Color :public Trackable
{
public:

	Color();

	Color(int* color);

	int getColor(int i);

	void setColor(int* color);


private:

	int mColor[4];
	 
	//alMapRGBA needs to be called after the display. 
	//call it instead in the write text function
	//don't store any alegro color here.

};
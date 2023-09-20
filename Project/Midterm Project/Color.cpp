#include "Color.h"

Color::Color()
{
	mColor[0] = 255; //r
	mColor[1] = 255; //g
	mColor[2] = 255; //b
	mColor[3] = 255; //a
}

Color::Color(int* color)
{
	mColor[0] = color[0];
	mColor[1] = color[1];
	mColor[2] = color[2];
	mColor[3] = color[3];
}

int Color::getColor(int i)
{
	int color = mColor[i];
	return color;
}

void Color::setColor(int* color)
{
	mColor[0] = color[0];
	mColor[1] = color[1];
	mColor[2] = color[2];
	mColor[3] = color[3];
}

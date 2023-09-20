#pragma once
#include <Trackable.h>
#include "Font.h"


class HUD : public Trackable
{
public:

	HUD();
	~HUD();


	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const int FONT_SIZE = 24;
	const std::string FONT_FILENAME = "cour.ttf";

	void writeText(std::string text, Vector2D location);
	void addFont(Font font);

private:

	Font mFont;

};
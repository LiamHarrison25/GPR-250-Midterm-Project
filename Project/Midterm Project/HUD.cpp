#include "HUD.h"
#include "Game.h"
#include "Color.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//does not need to be a complex system. Make sure to clear out what was there in the previous frame. Make a function to clear the previous frame.
//could also just write the hud to the backbuffer.

HUD::HUD()
{
	
}

HUD::~HUD()
{

}

void HUD::writeText(std::string text, Vector2D location)
{
	Game* game = Game::getInstance();
	GraphicsSystem* graphicsSystem = game->getGraphicsSystem();

	int whiteColor[4] = { 255, 255, 255, 255 };
	Color color(whiteColor);

	graphicsSystem->writeText(location, mFont, color, text);
}

void HUD::addFont(Font font)
{
	mFont = font;
}

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <Trackable.h>
#include "GraphicsSystem.h"

//This class can have allegro
class Font :public Trackable
{
	friend class GraphicsSystem;

public:

	Font();
	Font(ALLEGRO_FONT* font, int fontSize);
	Font(std::string fontName, int fontSize);
	~Font();

	int getFontSize();
	void setFontSize(int fontSize);

	ALLEGRO_FONT* getFont();
	void setFont(ALLEGRO_FONT* font);

private:

	ALLEGRO_FONT* mpFont;
	int mFontSize;
	bool mOwnsFont;
};

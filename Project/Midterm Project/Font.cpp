#include "Font.h"

Font::Font() 
{
	mFontSize = 12;
	mpFont = nullptr;
	mOwnsFont = false;
}

Font::Font(ALLEGRO_FONT* theFont, int fontSize)
{
	mpFont = theFont;
	mFontSize = fontSize;
	mOwnsFont = false;
}

Font::Font(std::string fontName, int fontSize)
{
	mpFont = al_load_font(fontName.c_str(), fontSize, 0);
	mFontSize = fontSize;
	mOwnsFont = true;
}

Font::~Font()
{
	if (mOwnsFont)
	{
		al_destroy_font(mpFont);
	}
	
}

int Font::getFontSize()
{
	return mFontSize;
}

void Font::setFontSize(int fontSize)
{
	mFontSize = fontSize;
}

ALLEGRO_FONT* Font::getFont()
{
	return mpFont;
}
void Font::setFont(ALLEGRO_FONT* font)
{
	mpFont = font;
}

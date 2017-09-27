#ifndef TITLE_H
#define TITLE_H

#include "rectangle.h"

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

struct title
{
	rectangle* rect;
	char* text;
	ALLEGRO_FONT* font;
	ALLEGRO_COLOR text_color;
	
};

typedef struct title title;

title* title_create(rectangle* rect, const char* text, int font_size, ALLEGRO_COLOR text_color);

void title_draw(title* tit);

void title_destroy(title* tit);

void title_update_text(title* tit, const char* text);

#endif
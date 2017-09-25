#include "title.h"

#include <string.h>

title* title_create(rectangle* rect, const char* text, int font_size, ALLEGRO_COLOR text_color)
{
	title* tit = malloc(sizeof(*tit));

	tit->rect = rect;
	tit->text = calloc(strlen(text) + 1, sizeof(*(tit->text)));
	strcpy(tit->text, text);

	tit->font = al_load_ttf_font("res/Doux.ttf", font_size, 0);
	//if (tit->font == NULL) //ERROR

	tit->text_color = text_color;
	return tit;
}

void title_draw(title* tit)
{
	rectangle_draw(tit->rect);	
	float x = tit->rect->x + al_get_bitmap_width(tit->rect->background) / 2;
	float y = tit->rect->y + al_get_bitmap_height(tit->rect->background) / 2;
	al_draw_text(tit->font, tit->text_color, x, y, ALLEGRO_ALIGN_CENTRE, tit->text);
}

void title_destroy(title* tit)
{
	rectangle_destroy(tit->rect);
	al_destroy_font(tit->font);
	free(tit->text);
	free(tit);
}
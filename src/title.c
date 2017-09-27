#include "title.h"

#include <string.h>

#define PARAM_CALC_X 0.5
#define PARAM_CALC_Y 0.25

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
	float x = tit->rect->x + al_get_bitmap_width(tit->rect->border) * PARAM_CALC_X;
	float y = tit->rect->y + al_get_bitmap_height(tit->rect->border) * PARAM_CALC_Y;
	al_draw_text(tit->font, tit->text_color, x, y, ALLEGRO_ALIGN_CENTRE, tit->text);
}

void title_destroy(title* tit)
{
	rectangle_destroy(tit->rect);
	al_destroy_font(tit->font);
	free(tit->text);
	free(tit);
}

void title_update_text(title* tit, const char* text)
{
	if (strcmp(tit->text, text)) {
		if (strlen(tit->text) < strlen(text)) {
			free(tit->text);
			tit->text = calloc(strlen(text) + 1, sizeof(*(tit->text)));
		}
		strcpy(tit->text, text);
	}
}
#include "rectangle.h"

#include <stdio.h>
#include <stdlib.h>

rectangle* rectangle_create(float x, float y, float width, float height, ALLEGRO_COLOR background_color, ALLEGRO_COLOR border_color, float border_size)
{
	rectangle* rect = malloc(sizeof(*rect));
	rect->x = x; 
	rect->y = y;

	rect->background = al_create_bitmap(width, height);
	al_set_target_bitmap(rect->background);
	al_clear_to_color(background_color);
	//if (rect->bitmap_background == NULL) //ERROR;

	rect->border = al_create_bitmap(width - 2 * border_size, height - 2 * border_size);
	al_set_target_bitmap(rect->border);
	al_clear_to_color(border_color);
	//if (rect->bitmap_border == NULL) //ERROR;

	rect->border_size = border_size;
	return rect;
}

void rectangle_draw(rectangle* rect)
{
	al_draw_bitmap(rect->background, rect->x, rect->y, 0);

	float x = rect->x + rect->border_size;
	float y = rect->y + rect->border_size;
	al_draw_bitmap(rect->border, x, y, 0);
}

void rectangle_destroy(rectangle* rect)
{
	al_destroy_bitmap(rect->background);
	al_destroy_bitmap(rect->border);
	free(rect);
}
/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором реализованы тела функций из файла \b "rectangle.h". \endb
 */
#include "rectangle.h"
#include "str.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>

rectangle* rectangle_create(float x, float y, float width, float height, ALLEGRO_COLOR background_color, ALLEGRO_COLOR border_color, float border_size)
{
	rectangle* rect = malloc(sizeof(*rect));
	rect->x = x; 
	rect->y = y;

	float w = width - 2 * border_size;
	float h = height - 2 * border_size;
	if (w <= 0 || h <= 0) {
		error_send(ERR_LARGE_BORDER);
	}

	rect->background = al_create_bitmap(w, h);
	al_set_target_bitmap(rect->background);
	al_clear_to_color(background_color);
	if (rect->background == NULL) {
		error_send(ERR_CREATE_BITMAP);
	}

	rect->border = al_create_bitmap(width, height);
	al_set_target_bitmap(rect->border);
	al_clear_to_color(border_color);
	if (rect->border == NULL) {
		error_send(ERR_CREATE_BITMAP);
	}

	rect->border_size = border_size;
	return rect;
}

void rectangle_draw(rectangle* rect)
{
	al_draw_bitmap(rect->border, rect->x, rect->y, 0);

	float x = rect->x + rect->border_size;
	float y = rect->y + rect->border_size;
	al_draw_bitmap(rect->background, x, y, 0);
}

void rectangle_destroy(rectangle* rect)
{
	al_destroy_bitmap(rect->background);
	al_destroy_bitmap(rect->border);
	free(rect);
}

bool rectangle_inside(rectangle* rect, float x, float y)
{
	float xl = rect->x + rect->border_size;
	float yl = rect->y + rect->border_size;

	float xr = xl + al_get_bitmap_width(rect->background);
	float yr = yl + al_get_bitmap_height(rect->background);

	return (xl <= x && x <= xr && yl <= y && y <= yr);
}
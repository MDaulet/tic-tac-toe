#ifndef RECT_H
#define RECT_H

#include <stdbool.h>
#include <allegro5/allegro.h>

struct rectangle
{
    float x;
    float y;	
    float border_size;
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* border;
};

typedef struct rectangle rectangle;

rectangle* rectangle_create(float x, float y, float width, float height, ALLEGRO_COLOR background_color, ALLEGRO_COLOR border_color, float border_size);

void rectangle_draw(rectangle* rect);

void rectangle_destroy(rectangle* rect);

bool rectangle_inside(rectangle* rect, float x, float y);
#endif

#include "win_menu.h"
#include "rectangle.h"
#include "game.h"
#include "color.h"

#include <stdlib.h>

#define TEXT_MESS "Select side:"
#define TEXT_EXIT "Exit"
#define TEXT_CROSS "X"
#define TEXT_ZERO "0"

#define WIDTH_MESS 180
#define HEIGHT_MESS 50

#define WIDTH_EXIT 150
#define HEIGHT_EXIT 50

#define SIZE_CROSS_ZERO 50

#define PARAM_START_X 0.3
#define PARAM_START_Y 0.25
#define PARAM_BETWEEN 1.5

#define SIZE_BORDER 5
#define FONT_SIZE 26

#define max(a, b) (((a) > (b)) ? (a) : (b))

#define NUM_BUTTON_MOUSE 1

static void draw(win_menu* win_me);

win_menu* win_menu_create(ALLEGRO_DISPLAY* display)
{
	win_menu* win_me = malloc(sizeof(*win_me));

	float x = al_get_display_width(display) * PARAM_START_X;
	float y = al_get_display_height(display) * PARAM_START_Y;

	float width_max = max(max(WIDTH_MESS, WIDTH_EXIT), SIZE_CROSS_ZERO);

	float xt = x + (width_max - WIDTH_MESS) / 2;
	rectangle* rect = rectangle_create(xt, y, WIDTH_MESS, HEIGHT_MESS, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, SIZE_BORDER);
	win_me->mess = title_create(rect, TEXT_MESS, FONT_SIZE, COLOR_LABEL_TEXT);

	y+= HEIGHT_MESS * 1.5;

	xt = x + (width_max / 2 - SIZE_CROSS_ZERO) / 2;
	rect = rectangle_create(xt, y, SIZE_CROSS_ZERO, SIZE_CROSS_ZERO, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, SIZE_BORDER);
	win_me->cross = title_create(rect, TEXT_CROSS, FONT_SIZE, COLOR_CELL_TEXT);

	xt = x + width_max / 2 + (width_max / 2 - SIZE_CROSS_ZERO) / 2;
	rect = rectangle_create(xt, y, SIZE_CROSS_ZERO, SIZE_CROSS_ZERO, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, SIZE_BORDER);
	win_me->zero = title_create(rect, TEXT_ZERO, FONT_SIZE, COLOR_CELL_TEXT);

	y += SIZE_CROSS_ZERO * 1.5;

	xt = x + (width_max - WIDTH_EXIT) / 2 ;
	rect = rectangle_create(xt, y, WIDTH_EXIT, HEIGHT_EXIT, COLOR_BUTTON_BACKGROUND, COLOR_BUTTON_BORDER, SIZE_BORDER);
	win_me->exit = title_create(rect, TEXT_EXIT, FONT_SIZE, COLOR_BUTTON_TEXT);

	win_me->display = display;
	al_set_target_bitmap(al_get_backbuffer(win_me->display));

	return win_me;
}

players win_menu_start(win_menu* win_me)
{
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	//if (event_queue == NULL) //ERROR

	al_register_event_source(event_queue, al_get_display_event_source(win_me->display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	draw(win_me);

	bool must_close = false;
	players player = EMPTY;
	while (!must_close) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			must_close = true;
		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.button == NUM_BUTTON_MOUSE) {
			int x = ev.mouse.x;
			int y = ev.mouse.y;

			if (rectangle_inside(win_me->cross->rect, x, y)) {
				player = CROSS;
				must_close = true;
			} else if (rectangle_inside(win_me->zero->rect, x, y)) {
				player = ZERO;
				must_close = true;
			} else if (rectangle_inside(win_me->exit->rect,	 x, y)) {
				must_close = true;	
			}			
		}
	}

	al_destroy_event_queue(event_queue);
	return player;
}

void win_menu_destroy(win_menu* win_me)
{
	title_destroy(win_me->mess);
	title_destroy(win_me->cross);
	title_destroy(win_me->zero);
	title_destroy(win_me->exit);
	free(win_me);
}

void draw(win_menu* win_me)
{
	al_clear_to_color(COLOR_WINDOW_BACKGROUND);

	title_draw(win_me->mess);
	title_draw(win_me->cross);
	title_draw(win_me->zero);
	title_draw(win_me->exit);

	al_flip_display();
}
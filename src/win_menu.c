/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com*
 * \file
 * \brief Файл, в котором реализованы тела функций из файла \b "win_menu.h". \endb
 */
#include "win_menu.h"
#include "rectangle.h"
#include "game.h"
#include "color.h"
#include "str.h"
#include "constants.h"

#include <stdlib.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * \brief Параметр для выравнивания меню по оси OX.
 */
#define PARAM_START_X 0.3

/**
 * \brief Параметр для выравнивания меню по оси OY.
 */
#define PARAM_START_Y 0.25

/**
 * \brief Параметр для вычисления отступов между элементами меню.
 */
#define PARAM_BETWEEN 1.5

/**
 * \brief Параметр выравнивания.
 */
#define PARAM_HALF 0.5

/**
 * \brief      Поиск максимума.
 *
 * \param      a     Первый элемент.
 * \param      b     Второй элемент.
 *
 * \return     Максимальный из двух элементов.
 */
#define max(a, b) (((a) > (b)) ? (a) : (b))

#endif 

/**
 * \brief      Отрисовка интерфейса главного меню.
 *
 * \param      win_me  Адрес интерфейса главного меню, 
 * который нужно отрисовать.
 */
static void draw(win_menu* win_me);

win_menu* win_menu_create(ALLEGRO_DISPLAY* display)
{
	win_menu* win_me = malloc(sizeof(*win_me));

	float x = al_get_display_width(display) * PARAM_START_X;
	float y = al_get_display_height(display) * PARAM_START_Y;

	float width_max = max(max(LABEL_WIDTH, BUTTON_WIDTH), CELL_WH);

	float xt = x + (width_max - LABEL_WIDTH) * PARAM_HALF;
	rectangle* rect = rectangle_create(xt, y, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
	win_me->mess = title_create(rect, STR_MESS_SELECT, LABEL_FONT_SIZE, COLOR_LABEL_TEXT);

	y+= LABEL_HEIGHT * PARAM_BETWEEN;

	xt = x + (width_max * PARAM_HALF - CELL_WH) * PARAM_HALF;
	rect = rectangle_create(xt, y, CELL_WH, CELL_WH, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, CELL_BORDER_SIZE);
	win_me->cross = title_create(rect, STR_CROSS, CELL_FONT_SIZE, COLOR_CELL_TEXT);

	xt = x + width_max * PARAM_HALF + (width_max * PARAM_HALF - CELL_WH) * PARAM_HALF;
	rect = rectangle_create(xt, y, CELL_WH, CELL_WH, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, CELL_BORDER_SIZE);
	win_me->zero = title_create(rect, STR_ZERO, CELL_FONT_SIZE, COLOR_CELL_TEXT);

	y += CELL_WH * PARAM_BETWEEN;

	xt = x + (width_max - BUTTON_WIDTH) * PARAM_HALF;
	rect = rectangle_create(xt, y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR_BUTTON_BACKGROUND, COLOR_BUTTON_BORDER, BUTTON_BORDER_SIZE);
	win_me->exit = title_create(rect, STR_EXIT, BUTTON_FONT_SIZE, COLOR_BUTTON_TEXT);

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
		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.button == NUM_BUTTON_TARGER) {
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
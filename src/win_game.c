#include "win_game.h"
#include "rectangle.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h> //DEBUG

#define SIZE_CELL 50
#define SIZE_TEXT_IN_CELL 26
#define SIZE_CELL_BORDER 3
#define COLOR_CELL_BACKGROUND al_map_rgb(255, 0, 0)
#define COLOR_CELL_BORDER al_map_rgb(0, 255, 0)
#define COLOR_CELL_TEXT al_map_rgb(0, 0, 255)

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define BUTTON_SIZE_TEXT 26
#define BUTTON_SIZE_BORDER 5
#define BUTTON_COLOR_BACKGROUND al_map_rgb(255, 0, 0)
#define BUTTON_COLOR_BORDER al_map_rgb(0, 255, 0)
#define BUTTON_COLOR_TEXT al_map_rgb(0, 0, 255)
#define BUTTON_TEXT "Back"

#define CROSS_STR "X"
#define ZERO_STR "0"
#define EMPTY_STR ""

#define NUM_BUTTON_MOUSE 1

#define PARAM_FIELD_X 0.5
#define PARAM_FIELD_Y 0.5

#define PARAM_BUTTON_X 0.5
#define PARAM_BUTTON_Y 1.5

#define COLOR_BACKGROUND_WINDOW al_map_rgb(230, 230, 230)

void update_field(win_game* w_gm);

void draw(win_game* w_gm);

win_game* win_game_create(ALLEGRO_DISPLAY* display, players player)
{
	win_game* w_gm = malloc(sizeof(*w_gm));

	float start_x = (al_get_display_width(display) - SIZE_CELL * SIZE_FIELD) * PARAM_FIELD_X;
	float start_y = (al_get_display_height(display) - SIZE_CELL * SIZE_FIELD) * PARAM_FIELD_Y;

	w_gm->gm = game_create(player);

	int i, j;
	for (i = 0; i < SIZE_FIELD; ++i) {
		for (j = 0; j < SIZE_FIELD; ++j) {
			float x = start_x + j * SIZE_CELL;
			float y = start_y + i * SIZE_CELL;

			rectangle* rect = rectangle_create(x, y, SIZE_CELL, SIZE_CELL, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, SIZE_CELL_BORDER);
			w_gm->field[i][j] = title_create(rect, "", SIZE_TEXT_IN_CELL, COLOR_CELL_TEXT);
		}
	} 

	float x = (al_get_display_width(display) - SIZE_CELL * SIZE_FIELD) * PARAM_BUTTON_X;
	float y = al_get_display_height(display) - BUTTON_HEIGHT * PARAM_BUTTON_Y;

	rectangle* rect = rectangle_create(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_COLOR_BACKGROUND, BUTTON_COLOR_BORDER, BUTTON_SIZE_BORDER);
	w_gm->button = title_create(rect, BUTTON_TEXT, BUTTON_SIZE_TEXT, BUTTON_COLOR_TEXT);

	update_field(w_gm);

	w_gm->display = display;
	al_set_target_bitmap(al_get_backbuffer(w_gm->display));

	return w_gm;
}

void win_game_start(win_game* w_gm)
{
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	//if (event_queue == NULL) //ERROR

	al_register_event_source(event_queue, al_get_display_event_source(w_gm->display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	draw(w_gm);

	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit(-1);
		} else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.button == NUM_BUTTON_MOUSE) {
			int x = ev.mouse.x;
			int y = ev.mouse.y;

			if (!game_is_end(w_gm->gm)) {
				int i, j;
				bool flag = true;
				for (i = 0; i < SIZE_FIELD && flag; ++i) {
					for (j = 0; j < SIZE_FIELD && flag; ++j) {
						if (rectangle_inside(w_gm->field[i][j]->rect, x, y)) game_click(w_gm->gm, i, j);
					}
				}

				draw(w_gm);

				if (!game_is_end(w_gm->gm) && w_gm->gm->current_player != w_gm->gm->player) {
					game_run_pc(w_gm->gm);
					draw(w_gm);
				}
			}

			if (rectangle_inside(w_gm->button->rect, x, y)) {
				break;
			}
		}
	}

	al_destroy_event_queue(event_queue);
}

void win_game_destroy(win_game* w_gm)
{
	int i, j;
	for (i = 0; i < SIZE_FIELD; ++i) {
		for (j = 0; j < SIZE_FIELD; ++j) {
			title_destroy(w_gm->field[i][j]);
		}
	}
	title_destroy(w_gm->button);
	game_destroy(w_gm->gm);
}

void update_field(win_game* w_gm)
{
	int i, j;
	for (i = 0; i < SIZE_FIELD; ++i) {
		for (j = 0; j < SIZE_FIELD; ++j) {
			switch(w_gm->gm->field[i][j]) {
				case CROSS:
					title_update_text(w_gm->field[i][j], CROSS_STR);
					break;
				case ZERO:
					title_update_text(w_gm->field[i][j], ZERO_STR);
					break;
				default:
					title_update_text(w_gm->field[i][j], EMPTY_STR);
			}
		}
	}
}

void draw(win_game* w_gm)
{
	al_clear_to_color(COLOR_BACKGROUND_WINDOW);
	
	int i, j;

	update_field(w_gm);

	for (i = 0; i < SIZE_FIELD; ++i) {
		for (j = 0; j < SIZE_FIELD; ++j) {
			title_draw(w_gm->field[i][j]);
		}
	}

	title_draw(w_gm->button);

	al_flip_display();
}
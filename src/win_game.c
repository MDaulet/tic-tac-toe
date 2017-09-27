#include "win_game.h"
#include "rectangle.h"
#include "color.h"
#include "str.h"
#include "constants.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h> //DEBUG

#define NUM_BUTTON_MOUSE 1

#define PARAM_FIELD_X 0.5
#define PARAM_FIELD_Y 0.5

#define PARAM_BUTTON_X 0.5
#define PARAM_BUTTON_Y 1.5

#define PARAM_MESS_Y 1.5

void update_field(win_game* w_gm);

void draw(win_game* w_gm);

win_game* win_game_create(ALLEGRO_DISPLAY* display, players player)
{
	win_game* w_gm = malloc(sizeof(*w_gm));

	float start_x = (al_get_display_width(display) - CELL_WH * FIELD_SIZE) * PARAM_FIELD_X;
	float start_y = (al_get_display_height(display) - CELL_WH * FIELD_SIZE) * PARAM_FIELD_Y;

	w_gm->gm = game_create(player);

	int i, j;
	for (i = 0; i < FIELD_SIZE; ++i) {
		for (j = 0; j < FIELD_SIZE; ++j) {
			float x = start_x + j * CELL_WH;
			float y = start_y + i * CELL_WH;

			rectangle* rect = rectangle_create(x, y, CELL_WH, CELL_WH, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, CELL_BORDER_SIZE);
			w_gm->field[i][j] = title_create(rect, "", CELL_FONT_SIZE, COLOR_CELL_TEXT);
		}
	} 

	float x = (al_get_display_width(display) - CELL_WH * FIELD_SIZE) * PARAM_BUTTON_X;
	float y = al_get_display_height(display) - BUTTON_HEIGHT * PARAM_BUTTON_Y;

	rectangle* rect = rectangle_create(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR_BUTTON_BACKGROUND, COLOR_BUTTON_BORDER, BUTTON_BORDER_SIZE);
	w_gm->button = title_create(rect, STR_BACK, BUTTON_FONT_SIZE, COLOR_BUTTON_TEXT);

	x = (al_get_display_width(display) - LABEL_WIDTH) / 2;
	y = start_y - LABEL_HEIGHT * PARAM_MESS_Y;
	rect = rectangle_create(x, y, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
	w_gm->mess = title_create(rect, "", LABEL_FONT_SIZE, COLOR_LABEL_TEXT);

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
				for (i = 0; i < FIELD_SIZE && flag; ++i) {
					for (j = 0; j < FIELD_SIZE && flag; ++j) {
						if (rectangle_inside(w_gm->field[i][j]->rect, x, y)) game_click(w_gm->gm, i, j);
					}
				}

				draw(w_gm);

				if (!game_is_end(w_gm->gm) && w_gm->gm->current_player != w_gm->gm->player) {
					game_run_pc(w_gm->gm);
					draw(w_gm);
				}

				if (game_is_end(w_gm->gm)) {
					if (game_is_draw(w_gm->gm)) {
						title_update_text(w_gm->mess, STR_MESS_DRAW);
					} else if (game_get_win(w_gm->gm) == w_gm->gm->player) {
						title_update_text(w_gm->mess, STR_MESS_WIN);
					} else {
						title_update_text(w_gm->mess, STR_MESS_LOSE);
					}

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
	for (i = 0; i < FIELD_SIZE; ++i) {
		for (j = 0; j < FIELD_SIZE; ++j) {
			title_destroy(w_gm->field[i][j]);
		}
	}
	title_destroy(w_gm->button);
	title_destroy(w_gm->mess);
	game_destroy(w_gm->gm);
	free(w_gm);
}

void update_field(win_game* w_gm)
{
	int i, j;
	for (i = 0; i < FIELD_SIZE; ++i) {
		for (j = 0; j < FIELD_SIZE; ++j) {
			switch(w_gm->gm->field[i][j]) {
				case CROSS:
					title_update_text(w_gm->field[i][j], STR_CROSS);
					break;
				case ZERO:
					title_update_text(w_gm->field[i][j], STR_ZERO);
					break;
				default:
					title_update_text(w_gm->field[i][j], STR_EMPTY);
			}
		}
	}
}

void draw(win_game* w_gm)
{
	al_clear_to_color(COLOR_WINDOW_BACKGROUND);

	int i, j;

	update_field(w_gm);

	for (i = 0; i < FIELD_SIZE; ++i) {
		for (j = 0; j < FIELD_SIZE; ++j) {
			title_draw(w_gm->field[i][j]);
		}
	}

	title_draw(w_gm->button);
	title_draw(w_gm->mess);

	al_flip_display();
}
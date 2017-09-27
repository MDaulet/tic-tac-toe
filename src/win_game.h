#ifndef WIN_GAME_H
#define WIN_GAME_H

#include "title.h"
#include "game.h"

#include <allegro5/allegro.h>

typedef enum result_game result_game;

struct win_game
{
	title* field[SIZE_FIELD][SIZE_FIELD];
	game* gm;
	title* button;
	ALLEGRO_DISPLAY* display;
};

typedef struct win_game win_game;

win_game* win_game_create(ALLEGRO_DISPLAY* display, players player);

void win_game_start(win_game* w_gm);

void win_game_destroy(win_game* w_gm);

#endif
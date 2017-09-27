#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define FIELD_SIZE 3

enum players
{
	CROSS,
	ZERO,
	EMPTY
};

typedef enum players players;

struct game 
{	
	players** field;
	players current_player; 
	players player;
};

typedef struct game game;

game* game_create(players player);

void game_click(game* gm, int row, int col);

bool game_is_end(game* gm);

players game_get_win(game* gm);

bool game_is_draw(game* gm);

void game_destroy(game* gm);

void game_run_pc(game* gm);

#endif
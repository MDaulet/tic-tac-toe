#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define SIZE_FIELD 3

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

bool is_end(game* gm);

players get_win(game* gm);

bool is_draw(game* gm);

void game_destroy(game* gm);

#endif
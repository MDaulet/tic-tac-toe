#include "game.h"

#include <stdlib.h>

void run_pc(game* gm);

players back_player(players player);

void change_current_player(game* gm);

bool check_win(players** field, players p);

bool check_draw(players** field);

bool check_end(players** field);

players search_win(players** field, players p);

game* game_create(players player)
{
	game* gm = malloc(sizeof(*gm));
	gm->field = calloc(SIZE_FIELD, sizeof(*(gm->field)));

	int i, j;
	for (i = 0; i < SIZE_FIELD; ++i) {
		gm->field[i] = calloc(SIZE_FIELD, sizeof(*(gm->field[i])));
		for (j = 0; j < SIZE_FIELD; ++j) {
			gm->field[i][j] = EMPTY;
		}
	}

	gm->current_player = CROSS;
	gm->player = player;

	if (gm->player == ZERO) {
		run_pc(gm);
	}

	return gm;
}

void game_click(game* gm, int row, int col)
{
	//ERROR
	if (gm->current_player == gm->player && gm->field[row][col] == EMPTY) {
		gm->field[row][col] = gm->current_player;
		change_current_player(gm);

		if (!game_is_end(gm)) run_pc(gm);
	}
}

bool game_is_end(game* gm)
{
	return check_end(gm->field);
}

players game_get_win(game* gm)
{
	if (check_win(gm->field, CROSS)) return CROSS;
	else if (check_win(gm->field, ZERO)) return ZERO;
	else return EMPTY;
}

bool game_is_draw(game* gm)
{
	return check_draw(gm->field);
}

void game_destroy(game* gm)
{
	int i;
	for (i = 0; i < SIZE_FIELD; ++i) {
		free(gm->field[i]);
	}
	free(gm->field);
	free(gm);
}

void run_pc(game* gm)
{
	players** copy_field = calloc(SIZE_FIELD, sizeof(*copy_field));
	int i, j;
	for (i = 0; i < SIZE_FIELD; ++i) {
		copy_field[i] = calloc(SIZE_FIELD, sizeof(*(copy_field[i])));
		for (int j = 0; j < SIZE_FIELD; ++j) {
			copy_field[i][j] = gm->field[i][j];
		}
	}

	players win = gm->player;
	players pc = gm->current_player;

	int move_row = -1;
	int move_col = -1;
	for (i = 0; i < SIZE_FIELD; ++i) {
		for (j = 0; j < SIZE_FIELD; ++j) {
			if (copy_field[i][j] != EMPTY) continue;

			copy_field[i][j] = pc;
			players current_win = search_win(copy_field, gm->player);

			if (current_win == pc || (win != pc && current_win == EMPTY) || (win == gm->player)) {
				win = current_win;
				move_row = i;
				move_col = j;
			} 
		} 
	}

	for (i = 0; i < SIZE_FIELD; ++i) {
		free(copy_field[i]);
	}
	free(copy_field);

	gm->field[move_row][move_col] = pc;
	change_current_player(gm);
}


players back_player(players player)
{
	switch(player) {
		case CROSS: return ZERO;
		case ZERO: return CROSS;
		default:
			return EMPTY;
			//ERROR
	}
}

void change_current_player(game* gm)
{
	gm->current_player = back_player(gm->current_player);
}

bool check_win(players** field, players p)
{
	int i, j, count;
	for (i = 0; i < SIZE_FIELD; ++i) {
		count = 0;
		for (j = 0; j < SIZE_FIELD; ++j) {
			if (field[i][j] == p) ++count;
		}
		if (count == SIZE_FIELD) return true;
	}

	for (int j = 0; j < SIZE_FIELD; ++j) {
		count = 0;
		for (i = 0; i < SIZE_FIELD; ++i) {
			if (field[i][j] == p) ++count;
		}
		if (count == SIZE_FIELD) return true;
	}

	count = 0;
	for (i = 0; i < SIZE_FIELD; ++i) {
		if (field[i][i] == p) ++count;
	}
	if (count == SIZE_FIELD) return true;

	count = 0;
	for (i = 0; i < SIZE_FIELD; ++i) {
		if (field[i][SIZE_FIELD - i - 1] == p) ++count;
	}
	if (count == SIZE_FIELD) return true;

	return false;
}

bool check_draw(players** field)
{
	int i, j;
	for (i = 0; i < SIZE_FIELD; ++i) {
		for (j = 0; j < SIZE_FIELD; ++j) {
			if (field[i][j] == EMPTY) return false;
		}
	}
	return true;
}

bool check_end(players** field)
{
	return (check_draw(field) || check_win(field, CROSS) || check_win(field, ZERO));
}

players search_win(players** field, players player)
{
	if (check_end(field)) {
		if (check_win(field, CROSS)) return CROSS;
		else if (check_win(field, ZERO)) return ZERO;
		else return EMPTY; 
	}

	players win = back_player(player);
	int i, j;
	for (i = 0; i < SIZE_FIELD; ++i) {
		for (j = 0; j < SIZE_FIELD; ++j) {
			if (field[i][j] != EMPTY) continue;

			field[i][j] = player;
			players current_win = search_win(field, back_player(player));
			field[i][j] = EMPTY;

			if (current_win == player) return player;
			else if (current_win == EMPTY) win = EMPTY;
		}
	}

	return win;
}
/**
 * \author Mахамбетали Даулет - 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором реализованы тела функций из файла \b "game.h". \endb
 */
#include "game.h"
#include "constants.h"
#include "str.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * \brief      Получение противника игра.
 *
 * \param[in]  player  Игрок, для которого необходимо найти противника.
 *
 * \return     Противник.
 */
static players back_player(players player);

/**
 * \brief      Передача хода следующему игроку.
 *
 * \param      gm    Адрес модели игры, в которой нужно передать ход.
 */
static void change_current_player(game* gm);

/**
 * \brief      Проверка: победил ли заданный игрок?
 *
 * \param      field  Адрес поля игры.
 * \param[in]  p      Игрок.
 *
 * \return     
 * 			- \b true, \endb если игрок победил.
 * 			- \b false, \endb в противном случае.
 */
static bool check_win(players** field, players p);

/**
 * \brief      Проверка: закончилась ли игра в ничью?
 *
 * \param      field  Адрес поля игры.
 *
 * \return     
 * 			- \b true, \endb если игра закончилась в ничью.
 * 			- \b false, \endb в противном случае.
 */
static bool check_draw(players** field);

/**
 * \brief      Проверка: закончилась ли игра?
 *
 * \param      field  Адрес поля игры.
 *
 * \return     
 * 			- \b true, \endb если игра закончилась.
 * 			- \b false, \endb в противном случае.
 */
static bool check_end(players** field);

/**
 * \brief      Поиск победителя при лучшей стратегии обеих игроков.
 *
 * \param      field  Адрес поля.
 * \param[in]  p      Игрок, который должен ходить.
 *
 * \return     
 * 			- \b #CROSS, \endb если победили крестики.
 * 			- \b #ZERO, \endb если победили нолики.
 * 			- \b #EMPTY, \endb в остальных случаях.
 */
static players search_win(players** field, players p);

game* game_create(players player)
{
	if (player == EMPTY) {
		error_send(ERR_PLAY_EMPTY);
	}

	game* gm = malloc(sizeof(*gm));
	gm->field = calloc(FIELD_SIZE, sizeof(*(gm->field)));

	int i, j;
	for (i = 0; i < FIELD_SIZE; ++i) {
		gm->field[i] = calloc(FIELD_SIZE, sizeof(*(gm->field[i])));
		for (j = 0; j < FIELD_SIZE; ++j) {
			gm->field[i][j] = EMPTY;
		}
	}

	gm->current_player = CROSS;
	gm->player = player;

	if (gm->player == ZERO) {
		game_run_pc(gm);
	}

	return gm;
}

void game_click(game* gm, int row, int col)
{
	if (row < 0 || row >= FIELD_SIZE || col < 0 || col >= FIELD_SIZE) {
		error_send(ERR_OUTSIDE_FIELD);
	}

	if (gm->current_player == gm->player && gm->field[row][col] == EMPTY) {
		gm->field[row][col] = gm->current_player;
		change_current_player(gm);
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
	for (i = 0; i < FIELD_SIZE; ++i) {
		free(gm->field[i]);
	}
	free(gm->field);
	free(gm);
}

void game_run_pc(game* gm)
{
	players** copy_field = calloc(FIELD_SIZE, sizeof(*copy_field));
	int i, j;
	for (i = 0; i < FIELD_SIZE; ++i) {
		copy_field[i] = calloc(FIELD_SIZE, sizeof(*(copy_field[i])));
		for (int j = 0; j < FIELD_SIZE; ++j) {
			copy_field[i][j] = gm->field[i][j];
		}
	}

	players win = gm->player;
	players pc = gm->current_player;

	int move_row = -1;
	int move_col = -1;
	for (i = 0; i < FIELD_SIZE; ++i) {
		for (j = 0; j < FIELD_SIZE; ++j) {
			if (copy_field[i][j] != EMPTY) continue;

			copy_field[i][j] = pc;
			players current_win = search_win(copy_field, gm->player);
			copy_field[i][j] = EMPTY;

			if (current_win == pc || (win != pc && current_win == EMPTY) || (win == gm->player)) {
				win = current_win;
				move_row = i;
				move_col = j;
			} 
		} 
	}

	for (i = 0; i < FIELD_SIZE; ++i) {
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
			error_send(ERR_BACK_EMPTY);
			return EMPTY;
	}
}

void change_current_player(game* gm)
{
	gm->current_player = back_player(gm->current_player);
}

bool check_win(players** field, players p)
{
	if (p == EMPTY) {
		error_send(ERR_WIN_EMPTY);
	}

	int i, j, count;
	for (i = 0; i < FIELD_SIZE; ++i) {
		count = 0;
		for (j = 0; j < FIELD_SIZE; ++j) {
			if (field[i][j] == p) ++count;
		}
		if (count == FIELD_SIZE) return true;
	}

	for (int j = 0; j < FIELD_SIZE; ++j) {
		count = 0;
		for (i = 0; i < FIELD_SIZE; ++i) {
			if (field[i][j] == p) ++count;
		}
		if (count == FIELD_SIZE) return true;
	}

	count = 0;
	for (i = 0; i < FIELD_SIZE; ++i) {
		if (field[i][i] == p) ++count;
	}
	if (count == FIELD_SIZE) return true;

	count = 0;
	for (i = 0; i < FIELD_SIZE; ++i) {
		if (field[i][FIELD_SIZE - i - 1] == p) ++count;
	}
	if (count == FIELD_SIZE) return true;

	return false;
}

bool check_draw(players** field)
{
	int i, j;
	for (i = 0; i < FIELD_SIZE; ++i) {
		for (j = 0; j < FIELD_SIZE; ++j) {
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
	if (player == EMPTY) {
		error_send(ERR_MOVE_EMPTY);
	}
	
	if (check_end(field)) {
		if (check_win(field, CROSS)) return CROSS;
		else if (check_win(field, ZERO)) return ZERO;
		else return EMPTY; 
	}

	players win = back_player(player);
	int i, j;
	for (i = 0; i < FIELD_SIZE; ++i) {
		for (j = 0; j < FIELD_SIZE; ++j) {
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
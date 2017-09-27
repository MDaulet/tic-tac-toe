/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com*
 * \file
 * \brief Файл, в котором определяется структура 
 * \b #game \endb - модель игры крестики-нолики.
 */
#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

/**
 * \brief      Перечисления для обозначения игрока/клетки.
 */
enum players
{
	CROSS, ///< Крестик.
	ZERO,  ///< Нолик.
	EMPTY  ///< Ни крестик, ни нолик. 
};

typedef enum players players;

/**
 * \brief      Структура, которая описывает модель игры.
 */
struct game 
{	
	/**
	 * \brief Игровое поле.
	 */
	players** field;

	/**
	 * \brief Игрок, который сейчас ходит.
	 */
	players current_player; 

	/**
	 * \brief Игрок, за которого играет человек.
	 */
	players player;
};

typedef struct game game;

/**
 * \brief      Создание модели игры.
 *
 * \param[in]  player  Игрок, за которого играет человек.
 *
 * \return     Адрес созданной модели игры.
 */
game* game_create(players player);

/**
 * \brief      Обработка события: клик по полю.
 *
 * \param      gm    Адрес модели игры, для которой обрабатывается событие.
 * \param[in]  row   Номер строки, по которой кликнули.
 * \param[in]  col   Номер столбца, по которому кликнули.
 */
void game_click(game* gm, int row, int col);

/**
 * \brief      Проверка: закончилась ли игра?
 *
 * \param      gm    Адрес модели игры, для которой нужно осуществить проверку.
 *
 * \return     
 * 			- \b true, \endb если игра закончилась.
 * 			- \b false, \endb в противном случае.
 */
bool game_is_end(game* gm);

/**
 * \brief      Определение победителя.
 *
 * \param      gm    Адрес модели игры, для которой нужно найти победителя.
 *
 * \return     
 * 			- \b #CROSS, \endb если победили крестики.
 * 			- \b #ZERO, \endb если победили нолики.
 * 			- \b #EMPTY, \endb в остальных случаях.
 */
players game_get_win(game* gm);


/**
 * \brief      Проверка: закончилась ли игра в ничью?
 *
 * \param      gm    Адрес модели игры, для которой нужно осуществить проверку.
 *
 * \return     
 * 			- \b true, \endb если игра закончилась в ничью.
 * 			- \b false, \endb в противном случае.
 */
bool game_is_draw(game* gm);

/**
 * \brief      Уничтожение модели игры.
 *
 * \param      gm    Адрес модели игры, которую нужно уничтожить.
 */
void game_destroy(game* gm);

/**
 * \brief      Передача хода компьютеру.
 *
 * \param      gm    Адрес модели игры, в которой должен ходить компьютер.
 */
void game_run_pc(game* gm);

#endif
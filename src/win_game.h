/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file 
 * \brief Файл, в котором определяется структура 
 * \b #win_game \endb - интерфейс игры.
 */
#ifndef WIN_GAME_H
#define WIN_GAME_H

#include "title.h"
#include "game.h"
#include "constants.h"

#include <allegro5/allegro.h>

/**
 * \brief Структура, которая описывает интерфейс игры.
 */
struct win_game
{
	/**
	 * \brief Поле.
	 */
	title* field[FIELD_SIZE][FIELD_SIZE];

	/**
	 * \brief Модель игры.
	 */
	game* gm;

	/**
	 * \brief Кнопка "Назад".
	 */
	title* button;

	/**
	 * \brief Надпись для вывода сообщения.
	 */
	title* mess;

	/**
	 * \brief Дисплей, на котором происходит рисование.
	 */
	ALLEGRO_DISPLAY* display;
};

typedef struct win_game win_game;

/**
 * \brief      Создание интерфейса игры.
 *
 * \param      display  Адрес дисплея, на котором происходит рисование.
 * \param[in]  player   Игрок, за которого играет человек.
 *
 * \return     Адрес созданного интерфейса игры.
 */
win_game* win_game_create(ALLEGRO_DISPLAY* display, players player);

/**
 * \brief      Запуск цикла рисования и обработки событий.
 *
 * \param      win_gm  Адрес интерфейса игры, для которого запускается цикл.
 */
void win_game_start(win_game* win_gm);

/**
 * \brief      Уничтожение интерфейса игры.
 *
 * \param      win_gm  Адрес интерфейса игры, который уничтожается.
 */
void win_game_destroy(win_game* win_gm);

#endif
/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file 
 * \brief Файл, в котором определяется структура 
 * \b #win_menu \endb - интерфейс главного меню.
 */
#ifndef WIN_MENU_H
#define WIN_MENU_H

#include "title.h"
#include "game.h"

#include <allegro5/allegro.h>

/**
 * \brief Структура, которая описывает интерфейс главного меню.
 */
struct win_menu
{
	/**
	 * \brief Надпись (заголовок).
	 */
	title* mess;

	/**
	 * \brief Кнопка "За крестики".
	 */
	title* cross;

	/**
	 * \brief Кнопка "За нолики".
	 */
	title* zero;

	/**
	 * \brief Кнопка "Выход".
	 */
	title* exit;

	/**
	 * \brief Дисплей, на котором происходит рисование.
	 */
	ALLEGRO_DISPLAY* display;
};	

typedef struct win_menu win_menu;

/**
 * \brief      Создание интерфейса главного меню.
 *
 * \param      display  Адрес дисплея, на котором происходит рисование.
 *
 * \return     Адрес созданного интерфейса главного меню.
 */
win_menu* win_menu_create(ALLEGRO_DISPLAY* display);

/**
 * \brief      Запуск цикла рисования и обработки событий.
 *
 * \param      win_me  Адрес интерфейса главного меню, 
 * для которого запускается цикл.
 *
 * \return     
 * 			- \b #CROSS , \endb если игрок выбрал игру за крестики.
 * 			- \b #ZERO, \endb если игрок выбрал игру за нолики.
 * 			- \b #EMPTY, \endb если игрок решил выйти.
 */
players win_menu_start(win_menu* win_me);

/**
 * \brief      Уничтожение интерфейса главного меню.
 *
 * \param      win_me  Адрес интерфейса главного меню, который нужно уничтожить.
 */
void win_menu_destroy(win_menu* win_me);

#endif

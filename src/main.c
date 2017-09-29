/**
 * \author Mахамбетали Даулет - 77003820792d@gmail.com
 * \file 
 * \brief Файл, в котором реализована функция #main - точка входа в приложение.
 */
#include "game.h"
#include "win_game.h"
#include "win_menu.h"
#include "str.h"
#include "constants.h"

#include <stdio.h>
#include <allegro5/allegro.h>

/**
 * \brief      Точка входа приложения.
 *
 * \return     
 * 			- \b 0, \endb если программа корректно завершила свою работу.
 * 			- Отличное от нуля число, если в ходе выполнения 
 * 			программы возникла ошибка.
 */
int main() {
	if (!al_init()) {
		perror(ERR_INIT_ALLEGRO);
		return -1;
	}

	if (!al_install_mouse()) {
		perror(ERR_INSTALL_MOUSE);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (display == NULL) {
		perror(ERR_CREATE_DISPLAY);
		return -1;
	}

	while (true) {
		win_menu* win_me = win_menu_create(display);
		players player = win_menu_start(win_me);
		win_menu_destroy(win_me);

		if (player == EMPTY) {
			break;
		}

		win_game* win_gm = win_game_create(display, player);
		win_game_start(win_gm);
		win_game_destroy(win_gm);
	}

	al_destroy_display(display);
	return 0;
}
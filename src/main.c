/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * 	
 * \file 
 * \brief Файл, в котором реализована функция #main - точка входа в приложение.
 */
#include "game.h"
#include "win_game.h"
#include "win_menu.h"

#include <allegro5/allegro.h>

/**
 * \brief Ширина окна приложение.
 */
#define SCREEN_WIDTH 640

/**
 * \brief Высота окна приложения.
 */
#define SCREEN_HEIGHT 480

/**
 * @brief      Точка входа приложения.
 *
 * @return     
 * 			- \b 0, \endb если программа корректно завершила свою работу.
 * 			- Отличное от нуля число, если в ходе выполнения 
 * 			программы возникла ошибка.
 */
int main() {
	if (!al_init()) {
		//ERROR
		return -1;
	}

	if (!al_install_mouse()) {
		//ERROR
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (display == NULL) {
		//ERROR
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
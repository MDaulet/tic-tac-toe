/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором определены тесты 
 * для тестирования структуры #win_menu.
 */
#include "unity.h"
#include "unity_fixture.h"
#include "game.h"
#include "constants.h"
#include "color.h"
#include "win_menu.h"

#include <stdio.h>
#include <allegro5/allegro.h>

/**
 * \brief      Имя тестовой группы.
 *
 * \param[in]  <unnamed>  имя.
 */
TEST_GROUP(test_win_menu);

/**
 * \brief      Функция, которая запускает тесты.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_GROUP_RUNNER(test_win_menu)
{
	RUN_TEST_CASE(test_win_menu, fun_create);
	RUN_TEST_CASE(test_win_menu, fun_destroy);
}

/**
 * \brief      Функция, которая вызывается перед каждым тестом.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_SETUP(test_win_menu) {}

/**
 * \brief      Функция, которая вызывается после каждого теста.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_TEAR_DOWN(test_win_menu) {}

/**
 * \brief      Функция, в которой тестируется функция #win_menu_create.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_win_menu, fun_create)
{
	al_init();

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (TEST_PROTECT()) {
		win_menu* win_me = win_game_create(display);
		win_menu_destroy(win_me);
	} else {
		TEST_FAIL();
	}

	al_destroy_display(display);
}

/**
 * \brief      Функция, в которой тестируется функция #win_menu_destroy.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_win_menu, fun_destroy)
{
	al_init();

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (TEST_PROTECT()) {
		win_menu* win_me = win_game_create(display);
		win_menu_destroy(win_me);
	} else {
		TEST_FAIL();
	}

	al_destroy_display(display);
}
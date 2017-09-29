/**
 * \author Mахамбетали Даулет - 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором определены тесты 
 * для тестирования структуры #win_game.
 */
#include "unity.h"
#include "unity_fixture.h"
#include "game.h"
#include "constants.h"
#include "color.h"
#include "win_game.h"

#include <stdio.h>
#include <allegro5/allegro.h>

/**
 * \brief      Имя тестовой группы.
 *
 * \param[in]  <unnamed>  имя.
 */
TEST_GROUP(test_win_game);

/**
 * \brief      Функция, которая запускает тесты.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_GROUP_RUNNER(test_win_game)
{
	RUN_TEST_CASE(test_win_game, fun_create);
	RUN_TEST_CASE(test_win_game, fun_destroy);
}

/**
 * \brief      Функция, которая вызывается перед каждым тестом.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_SETUP(test_win_game) {}

/**
 * \brief      Функция, которая вызывается после каждого теста.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_TEAR_DOWN(test_win_game) {}

/**
 * \brief      Функция, в которой тестируется функция #win_game_create.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_win_game, fun_create)
{
	al_init();

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (TEST_PROTECT()) {
		win_game* win_gm = win_game_create(display, CROSS);
		win_game_destroy(win_gm);
	} else {
		TEST_FAIL();
	}

	if (TEST_PROTECT()) {
		win_game* win_gm = win_game_create(display, ZERO);
		win_game_destroy(win_gm);
	} else {
		TEST_FAIL();
	}

	if (TEST_PROTECT()) {
		win_game_create(display, EMPTY);
		TEST_FAIL();
	} 

	al_destroy_display(display);
}

/**
 * \brief      Функция, в которой тестируется функция #win_game_destroy.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_win_game, fun_destroy)
{
	al_init();

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (TEST_PROTECT()) {
		win_game* win_gm = win_game_create(display, CROSS);
		win_game_destroy(win_gm);
	} else {
		TEST_FAIL();
	}

	al_destroy_display(display);
}
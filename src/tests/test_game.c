/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором определены тесты 
 * для тестирования структуры #game.
 */
#include "unity.h"
#include "unity_fixture.h"
#include "game.h"
#include "constants.h"

#include <stdio.h>

/**
 * \brief Модель игры, которая пересоздается перед каждым тестом.
 */
static game* gm;

/**
 * \brief      Имя тестовой группы.
 *
 * \param[in]  <unnamed>  имя.
 */
TEST_GROUP(test_game);

/**
 * \brief      Функция, которая запускает тесты.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_GROUP_RUNNER(test_game)
{
	RUN_TEST_CASE(test_game, fun_create);
	RUN_TEST_CASE(test_game, fun_click);
	RUN_TEST_CASE(test_game, fun_destroy);
}

/**
 * \brief      Функция, которая вызывается перед каждым тестом.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_SETUP(test_game)
{
	gm = game_create(CROSS);
}

/**
 * \brief      Функция, которая вызывается после каждого теста.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_TEAR_DOWN(test_game)
{
	game_destroy(gm);
}

/**
 * \brief      Функция, в которой тестируется функция #game_create.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_game, fun_create)
{
	if (TEST_PROTECT()) {
		game* gm = game_create(CROSS);
		TEST_ASSERT_NOT_NULL(gm);
		game_destroy(gm);
	} else {
		TEST_FAIL();
	}

	if (TEST_PROTECT()) {
		game* gm = game_create(ZERO);
		TEST_ASSERT_NOT_NULL(gm);
		game_destroy(gm);
	} else {
		TEST_FAIL();
	}

	if (TEST_PROTECT()) {	
		gm = game_create(EMPTY);
		TEST_FAIL();
	} 
}

/**
 * \brief      Функция, в которой тестируется функция #game_click.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_game, fun_click)
{
	if (TEST_PROTECT()) {
		int i, j;
		for (i = 0; i < FIELD_SIZE; ++i) {
			for (j = 0; j < FIELD_SIZE; ++j) {
				game* gm = game_create(CROSS);
				if (TEST_PROTECT()) {
					game_click(gm, i, j);
				} else {
					TEST_FAIL();
				}

				if (TEST_PROTECT()) {
					game_click(gm, i, -1);
					TEST_FAIL();
				} else if (TEST_PROTECT()) {
					game_click(gm, i, FIELD_SIZE);
					TEST_FAIL();
				} else if (TEST_PROTECT()) {
					game_click(gm, -1, j);
					TEST_FAIL();
				} else if (TEST_PROTECT()) {
					game_click(gm, FIELD_SIZE, j);
					TEST_FAIL();
				}
			}
		}
	} else {
		TEST_FAIL();
	}
}

/**
 * \brief      Функция, в которой тестируется функция #game_destroy.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_game, fun_destroy)
{
	if (TEST_PROTECT()) {
		game* gm = game_create(CROSS);
		game_destroy(gm);
	} else {
		TEST_FAIL();
	}
}


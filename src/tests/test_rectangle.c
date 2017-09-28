/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором определены тесты 
 * для тестирования структуры #rectangle.
 */
#include "unity.h"
#include "unity_fixture.h"
#include "constants.h"
#include "color.h"
#include "rectangle.h"

#include <stdio.h>
#include <allegro5/allegro.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * \brief Параметр округления вещественных чисел.
 */
#define PARAM_ROUND 0.5

#endif 

/**
 * \brief      Имя тестовой группы.
 *
 * \param[in]  <unnamed>  имя.
 */
TEST_GROUP(test_rectangle);

/**
 * \brief      Функция, которая запускает тесты.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_GROUP_RUNNER(test_rectangle)
{
	RUN_TEST_CASE(test_rectangle, fun_create);
	RUN_TEST_CASE(test_rectangle, fun_inside);
	RUN_TEST_CASE(test_rectangle, fun_destroy);
	RUN_TEST_CASE(test_rectangle, fun_draw);
}

/**
 * \brief      Функция, которая вызывается перед каждым тестом.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_SETUP(test_rectangle) {}

/**
 * \brief      Функция, которая вызывается после каждого теста.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_TEAR_DOWN(test_rectangle) {}

/**
 * \brief      Функция, в которой тестируется функция #rectangle_create.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_rectangle, fun_create)
{
	al_init();
	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
		rectangle_destroy(rect);
	} else {
		TEST_FAIL();
	}

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, CELL_WH, CELL_WH, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, CELL_BORDER_SIZE);
		rectangle_destroy(rect);
	} else {
		TEST_FAIL();
	}

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR_BUTTON_BACKGROUND, COLOR_BUTTON_BORDER, BUTTON_BORDER_SIZE);
		rectangle_destroy(rect);
	} else {
		TEST_FAIL();
	}
	
	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, CELL_WH, CELL_WH, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, CELL_WH);
		TEST_FAIL();
	} 
}

/**
 * \brief      Функция, в которой тестируется функция #rectangle_inside.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_rectangle, fun_inside)
{
	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);

		int xl = rect->x + rect->border_size + PARAM_ROUND;
		int yl = rect->y + rect->border_size + PARAM_ROUND;
		int xr = xl + al_get_bitmap_width(rect->background);
		int yr = yl + al_get_bitmap_height(rect->background); 

		int x, y;
		for (x = xl; x <= xr; ++x) {
			for (y = yl; y <= yr; ++y) {
				TEST_ASSERT_TRUE(rectangle_inside(rect, x, y));
			}
		}

		for (x = 0; x < xl; ++x) {
			for (y = 0; y < SCREEN_HEIGHT; ++y) {
				TEST_ASSERT_FALSE(rectangle_inside(rect, x, y));
			}
		}

		for (x = xr + 1; x <= SCREEN_WIDTH; ++x) {
			for (y = 0; y < SCREEN_HEIGHT; ++y) {
				TEST_ASSERT_FALSE(rectangle_inside(rect, x, y));
			}
		}

		for (y = 0; y < yl; ++y) {
			for (x = 0; x < SCREEN_WIDTH; ++x) {
				TEST_ASSERT_FALSE(rectangle_inside(rect, x, y));	
			}
		}

		for (y = yr + 1; y < SCREEN_HEIGHT; ++y) {
			for (x = 0; x < SCREEN_WIDTH; ++x) {
				TEST_ASSERT_FALSE(rectangle_inside(rect, x, y));	
			}
		}

		rectangle_destroy(rect);
	} else {
		TEST_FAIL();
	}
}

/**
 * \brief      Функция, в которой тестируется функция #rectangle_destroy.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_rectangle, fun_destroy)
{
	al_init();
	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
		rectangle_destroy(rect);
	} else {
		TEST_FAIL();
	}
}

/**
 * \brief      Функция, в которой тестируется функция #rectangle_draw.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_rectangle, fun_draw)
{
	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
		al_set_target_bitmap(al_get_backbuffer(display));
		rectangle_draw(rect);
		rectangle_destroy(rect);
		al_destroy_display(display);
	} else {
		TEST_FAIL();
	}
}
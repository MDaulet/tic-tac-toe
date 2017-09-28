/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором определены тесты 
 * для тестирования структуры #title.
 */
#include "unity.h"
#include "unity_fixture.h"
#include "game.h"
#include "constants.h"
#include "color.h"
#include "rectangle.h"
#include "title.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro.h>

/**
 * \brief Максимальная длина надписи.
 */
#define MAX_LEN_TITLE 100

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * \brief Модуль, по которому берется случайный код символа.
 */
#define MOD 126

#endif 

/**
 * \brief      Генерация случайного символа из отрезке [1, 127].
 *
 * \return     случайны символ.
 */
static char rnd_char();

/**
 * \brief      Генерация случайной строки.
 *
 * \param[out] str   Адрес, по которому нужно записать случайную строку.
 * \param[in]  len   Требуемая длина.
 */
static void rnd_string(char* str, int len);

/**
 * \brief      Имя тестовой группы.
 *
 * \param[in]  <unnamed>  имя.
 */
TEST_GROUP(test_title);

/**
 * \brief      Функция, которая запускает тесты.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_GROUP_RUNNER(test_title)
{
	RUN_TEST_CASE(test_title, fun_create);
	RUN_TEST_CASE(test_title, fun_update_text);
	RUN_TEST_CASE(test_title, fun_destroy);
	RUN_TEST_CASE(test_title, fun_draw);
}

/**
 * \brief      Функция, которая вызывается перед каждым тестом.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_SETUP(test_title) 
{
	srand(time(NULL));
}

/**
 * \brief      Функция, которая вызывается после каждого теста.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_TEAR_DOWN(test_title) {}

/**
 * \brief      Функция, в которой тестируется функция #title_create.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_title, fun_create)
{
	al_init();
	
	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
		title_create(rect, STR_MESS_SELECT, LABEL_FONT_SIZE, COLOR_LABEL_TEXT);
		TEST_FAIL();
	}

	al_init_font_addon();
	al_init_ttf_addon();

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
		title* tit = title_create(rect, STR_MESS_SELECT, LABEL_FONT_SIZE, COLOR_LABEL_TEXT);
		title_destroy(tit);
	} else {
		TEST_FAIL();
	}

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, CELL_WH, CELL_WH, COLOR_CELL_BACKGROUND, COLOR_CELL_BORDER, CELL_BORDER_SIZE);
		title* tit = title_create(rect, STR_CROSS, CELL_FONT_SIZE, COLOR_CELL_TEXT);
		title_destroy(tit);
	} else {
		TEST_FAIL();
	}

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT, COLOR_BUTTON_BACKGROUND, COLOR_BUTTON_BORDER, BUTTON_BORDER_SIZE);
		title* tit = title_create(rect, STR_EXIT, BUTTON_FONT_SIZE, COLOR_BUTTON_TEXT);
		title_destroy(tit);
	} else {
		TEST_FAIL();
	}
}

/**
 * \brief      Функция, в которой тестируется функция #title_update_text.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_title, fun_update_text)
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
		title* tit = title_create(rect, STR_MESS_SELECT, LABEL_FONT_SIZE, COLOR_LABEL_TEXT);

		char str[MAX_LEN_TITLE + 1];
		int i;
		for (i = 1; i <= MAX_LEN_TITLE; ++i) {
			rnd_string(str, i);
			title_update_text(tit, str);
			if (strcmp(tit->text, str)) {
				TEST_FAIL();
			}
		}

		for (i = MAX_LEN_TITLE; i >= 1; --i) {
			rnd_string(str, i);
			title_update_text(tit, str);
			if (strcmp(tit->text, str)) {
				TEST_FAIL();
			}
		}
	} else {
		TEST_FAIL();
	}
}

/**
 * \brief      Функция, в которой тестируется функция #title_destroy.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_title, fun_destroy)
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
		title* tit = title_create(rect, STR_MESS_SELECT, LABEL_FONT_SIZE, COLOR_LABEL_TEXT);
		title_destroy(tit);
	} else {
		TEST_FAIL();
	}
}

/**
 * \brief      Функция, в которой тестируется функция #title_draw.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_title, fun_draw)
{
	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (TEST_PROTECT()) {
		rectangle* rect = rectangle_create(0, 0, LABEL_WIDTH, LABEL_HEIGHT, COLOR_LABEL_BACKGROUND, COLOR_LABEL_BORDER, LABEL_BORDER_SIZE);
		title* tit = title_create(rect, STR_MESS_SELECT, LABEL_FONT_SIZE, COLOR_LABEL_TEXT);
		al_set_target_bitmap(al_get_backbuffer(display));
		title_draw(tit);
		title_destroy(tit);
		al_destroy_display(display);
	} else {
		TEST_FAIL();
	}
}

static char rnd_char()
{
	return rand() % MOD + 1;
}

static void rnd_string(char* str, int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		str[i] = rnd_char();
	}
	str[len] = 0;
}
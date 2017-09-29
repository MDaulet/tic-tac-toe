/**
 * \author Mахамбетали Даулет - 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором определены тесты 
 * для тестирования корректности работы библиотеки <a href="http://liballeg.org/">Allegro</a>. 
 */
#include "unity.h"
#include "unity_fixture.h"
#include "constants.h"

#include <stdio.h>
#include <allegro5/allegro.h>

/**
 * \brief      Имя тестовой группы.
 *
 * \param[in]  <unnamed>  имя.
 */
TEST_GROUP(test_allegro);

/**
 * \brief      Функция, которая запускает тесты.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_GROUP_RUNNER(test_allegro)
{
	RUN_TEST_CASE(test_allegro, fun_init);
	RUN_TEST_CASE(test_allegro, fun_install_mouse);
	RUN_TEST_CASE(test_allegro, fun_create_display);
	RUN_TEST_CASE(test_allegro, fun_create_event_queue);
}

/**
 * \brief      Функция, которая вызывается перед каждым тестом.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_SETUP(test_allegro) {}

/**
 * \brief      Функция, которая вызывается после каждого теста.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 */
TEST_TEAR_DOWN(test_allegro) {}

/**
 * \brief      Функция, в которой тестируется функция  <a href="https://www.allegro.cc/manual/5/al_init">al_init</a>.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_allegro, fun_init)
{
	if(!al_init()) {
		TEST_FAIL();
	}
}

/**
 * \brief      Функция, в которой тестируется функция <a href="https://www.allegro.cc/manual/5/al_install_mouse">al_install_mouse</a>.
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_allegro, fun_install_mouse)
{
	al_init();

	if (!al_install_mouse()) {
		TEST_FAIL();
	}
}

/**
 * \brief      Функция, в которой тестируется функция <a href="https://www.allegro.cc/manual/5/al_create_display">al_create_display</a>. 
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_allegro, fun_create_display)
{
	al_init();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (display == NULL) {
		TEST_FAIL();
	} else {
		al_destroy_display(display);
	}
}

/**
 * \brief      Функция, в которой тестируется функция <a href="https://www.allegro.cc/manual/5/al_create_event_queue">al_create_event_queue</a>. 
 *
 * \param[in]  <unnamed>  имя тестовой группы.
 * \param[in]  <unnamed>  имя теста.
 */
TEST(test_allegro, fun_create_event_queue)
{
	al_init();

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	if (event_queue == NULL) {
		TEST_FAIL();
	} else {
		al_destroy_event_queue(event_queue);
	}
}


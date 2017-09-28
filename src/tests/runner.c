
/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором реализована функция #main - точка входа в программу тестирования.
 */
#include "unity.h"
#include "unity_fixture.h"

/**
 * \brief      Функция, которая запускает группы тестов.
 */
static void run_tests()
{
	RUN_TEST_GROUP(test_allegro);
	RUN_TEST_GROUP(test_game);
	RUN_TEST_GROUP(test_rectangle);
	RUN_TEST_GROUP(test_title);
	RUN_TEST_GROUP(test_win_game);
	RUN_TEST_GROUP(test_win_menu);
}

/**
 * \brief      Точка входа тестирующей программы.
 *
 * \param[in]  argc  Количество аргументов запуска.
 * \param      argv  Аргументы запуска.
 *
 * \return     
 * 			- \b 0, \endb если программа корректно завершила свою работу.
 * 			- Отличное от нуля число, если в ходе выполнения 
 * 			программы возникла ошибка.
 */
int main(int argc, const char* argv[]) 
{
	return UnityMain(argc, argv, run_tests);
}
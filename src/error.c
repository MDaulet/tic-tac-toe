/**
 * \author Mахамбетали Даулет - 77003820792d@gmail.com
 * \file
 * \brief Файл, в котором реализованы тела функций из файла \b "error.h". \endb
 */
#include "error.h"

#ifdef TESTING
	#include "unity.h"
	#include "unity_fixture.h"
#else 
	#include <stdlib.h>
#endif

#include <stdio.h>

void error_send(const char* mess)
{
	#ifdef TESTING
		TEST_ABORT();
	#else
		fprintf(stderr, "%s", mess);
		exit(-1);
	#endif
}
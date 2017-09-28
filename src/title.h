/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file 
 * \brief Файл, в котором определяется структура 
 * \b #title \endb - надпись в закрашенном прямоугольнике с рамкой.
 */
#ifndef TITLE_H
#define TITLE_H

#include "rectangle.h"

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/**
 * \brief Структура, которая описывает надпись 
 * в закрашенном прямоугольнике с рамкой.
 */
struct title
{
	/**
	 * \brief Прямоугольник, в котором находится надпись.
	 */
	rectangle* rect;

	/**
	 * \brief Текст надписи.
	 */
	char* text;

	/**
	 * \brief Шрифт.
	 */
	ALLEGRO_FONT* font;

	/**
	 * \brief Цвет шрифта.
	 */
	ALLEGRO_COLOR text_color;
	
};

typedef struct title title;

/**
 * \brief      Создание надписи.
 *
 * \param      rect        Адрес прямоугольника, в котором должна находится надпись.
 * \param[in]  text        Текст надписи.
 * \param[in]  font_size   Размер шрифта.
 * \param[in]  text_color  Цвет шрифта.
 *
 * \return     Адрес созданной надписи.
 */
title* title_create(rectangle* rect, const char* text, int font_size, ALLEGRO_COLOR text_color);

/**
 * \brief      Отрисовка надписи.
 *
 * \param      tit   Адрес надписи, которую необходимо нарисовать.
 */
void title_draw(title* tit);

/**
 * \brief      Уничтожение надписи.
 *
 * \param      tit   Адрес надписи, которую необходимо уничтожить.
 */
void title_destroy(title* tit);

/**
 * \brief      Изменение текста надписи.
 *
 * \param      tit   Адрес надписи, текст которой надо изменить.
 * \param[in]  text  Новый текст надписи.
 */
void title_update_text(title* tit, const char* text);

#endif
/**
 * \author Mахамбетали Дуалет, 77003820792d@gmail.com
 * \file 
 * \brief Файл, в котором определяется структура 
 * \b #rectangle \endb - закрашенный прямоугольник с рамкой.
 */
#ifndef RECT_H
#define RECT_H

#include <stdbool.h>
#include <allegro5/allegro.h>

/**
 * \brief Структура, которая описывает закрашенный прямоугольник с рамкой.
 */
struct rectangle
{
	/**
	 * \brief Координата верхнего левого угла по оси OX.
	 */
    float x;

    /**
     * \brief Координата верхнего левого угла по оси OY.
     */
    float y;	

    /**
     * \brief Толщина рамки.
     */
    float border_size;

    /**
     * \b BITMAP \endb для отрисовки внутренней части.
     */
    ALLEGRO_BITMAP* background;

    /**
     * \b BITMAP \endb для отрисовки границы.
     */
    ALLEGRO_BITMAP* border;
};

typedef struct rectangle rectangle; 

/**
 * \brief      Создание прямоугольника.
 *
 * \param[in]  x                 Координата верхнего левого угла по оси OX.
 * \param[in]  y                 Координата верхнего левого угла по оси OY.
 * \param[in]  width             Ширина.
 * \param[in]  height            Высота.
 * \param[in]  background_color  Цвет заливки.
 * \param[in]  border_color      Цвет рамки.
 * \param[in]  border_size       Толщина рамки.
 *
 * \return     Адрес созданного прямоугольника.
 */
rectangle* rectangle_create(float x, float y, float width, float height, ALLEGRO_COLOR background_color, ALLEGRO_COLOR border_color, float border_size);

/**
 * \brief      Отрисовка прямоугольника.
 *
 * \param      rect  Адрес прямоугольника, который необходимо нарисовать.
 */
void rectangle_draw(rectangle* rect);

/**
 * \brief      Уничтожение прямоугольника.
 *
 * \param      rect  Адрес прямоугольника, который нужно уничтожить.
 */
void rectangle_destroy(rectangle* rect);

/**
 * \brief      Проверка точки на принадлежность прямоугольника.
 *
 * \param      rect  Прямоугольник.
 * \param[in]  x     Координата точки по оси OX.
 * \param[in]  y     Координата точки по оси OY. 
 *
 * \return     
 * 			- \b true, \endb если точка лежит в прямоугольнике.
 * 			- \b false, \endb в противном случае.
 */
bool rectangle_inside(rectangle* rect, float x, float y);
#endif

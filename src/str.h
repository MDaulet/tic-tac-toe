/**
 * \author Mахамбетали Даулет - 77003820792d@gmail.com
 * \file 
 * \brief Файл, в котором определены строковые 
 * константы, которые исполюзуются в приложении.
 */
#ifndef STR_H
#define STR_H

/**
 * \brief Строка, представляющая крестик.
 */
#define STR_CROSS 	"X"

/**
 * \brief Строка, представляющая нолик.
 */
#define STR_ZERO 	"O"

/**
 * \brief Строка, представляющая пустую клетку.
 */
#define STR_EMPTY 	""

/**
 * \brief Надпись: "Назад".
 */
#define STR_BACK "Back"

/**
 * \brief Надпись: "Выход".
 */
#define STR_EXIT "Exit"

/**
 * \brief Сообщение: "Выберите сторону".
 */
#define STR_MESS_SELECT "Select side"

/**
 * \brief Сообщение: "Вы победели".
 */
#define STR_MESS_WIN 	"You are win"

/**
 * \brief Сообщение: "Вы проиграли".
 */
#define STR_MESS_LOSE	"You are lose"

/**
 * \brief Сообщение: "Ничья".
 */
#define STR_MESS_DRAW	"Draw"

/**
 * \brief Путь к файлу со шрифтом.
 */
#define PATH_FONT "res/Doux.ttf"

/**
 * \brief Сообщение об ошибке: "Не удалось создать BITMAP.".
 */
#define ERR_CREATE_BITMAP "Error. Could not create bitmap.\n"

/**
 * \brief Сообщение об ошибке: "Размер рамки слишком большой.".
 */
#define ERR_LARGE_BORDER "Error. The border size is too large.\n"

/**
 * \brief Сообщение об ошибке: "Не удалось загурзить шрифт.".
 */
#define ERR_LOAD_FONT "Error. Failed to load font.\n"

/**
 * \brief Сообщение об ошибке: "Выход за границы поля.".
 */
#define ERR_OUTSIDE_FIELD "Error. Outside the field.\n"

/**
 * \brief Сообщение об ошибке: "Невозможно найти противника для EMPTY игрока.".
 */
#define ERR_BACK_EMPTY "Error. It is impossible to find an opponent for an EMPTY player.\n"

/**
 * \brief Сообщение об ошибке: "Человек не может играть за EMPTY.".
 */
#define ERR_PLAY_EMPTY "Error. A person can not play for EMPTY.\n"

/**
 * \brief Сообщение об ошибке: "EMPTY не может быть победителем.".
 */
#define ERR_WIN_EMPTY "Error. EMPTY can not be the winner..\n"

/**
 * \brief Сообщение об ошибке: "EMPTY не может ходить.".
 */
#define ERR_MOVE_EMPTY "Error. EMPTY can not move.\n"

/**
 * \brief Сообщение об ошибке: "Не удалось создать EVENT_QUEUE.".
 */
#define ERR_EVENT_QUEUE "Error. Could not create EVENT_QUEUE.\n"

/**
 * \brief Сообщение об ошибке: "Не удалось инициализировать Allegro.".
 */
#define ERR_INIT_ALLEGRO "Error. Failed to initialize Allegro.\n"

/**
 * \brief Сообщение об ошибке: "Не удалось установить подсистему для работы с мышью.".
 */
#define ERR_INSTALL_MOUSE "Error. Failed to install subsystem to work with mouse.\n"

/**
 * \brief Сообщение об ошибке: "Не удалось создать Dislpay.".
 */
#define ERR_CREATE_DISPLAY "Error. Could not create Display.\n"

#endif
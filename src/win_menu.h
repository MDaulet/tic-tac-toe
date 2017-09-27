#ifndef WIN_MENU_H
#define WIN_MENU_H

#include "title.h"
#include "game.h"

#include <allegro5/allegro.h>

struct win_menu
{
	title* mess;
	title* cross;
	title* zero;
	title* exit;
	ALLEGRO_DISPLAY* display;
};	

typedef struct win_menu win_menu;

win_menu* win_menu_create(ALLEGRO_DISPLAY* display);

players win_menu_start(win_menu* win_me);

void win_menu_destroy(win_menu* win_me);

#endif

#ifndef TUI_SELECT_H
#define TUI_SELECT_H

#include "draw.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    WINDOW* window;
    char* title;
    char** items;
    size_t length;
    size_t current;
} select_state_t;


int update_select(select_state_t* select_state);
void draw_select(int y, int x, int width, select_state_t* select_state);
int chui_select(WINDOW* window,
                int y, int x,
                char* title,
                char** items, size_t length);


#endif

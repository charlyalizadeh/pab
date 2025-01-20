#ifndef TUI_DRAW_H
#define TUI_DRAW_H

#include <ncurses.h>
#include <string.h>
#include "../utils/base_convertion.h"


extern char* TUI_SLINES[9];
extern char* TUI_BLINES[9];
extern char* TUI_DLINES[9];
extern char* TUI_RLINES[9];

enum TUILineIndex {
    HORIZONTAL,
    VERTICAL,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    CROSS,
    CROSS_LEFT,
    CROSS_RIGHT
};

enum InputMode {
    BINARY,
    HEXADECIMAL,
    DECIMAL,
    ALL
};

void draw_rect(WINDOW* window,
               int y, int x, int height, int width,
               char** lines);
void draw_rect_sline(WINDOW* window,
                     int y, int x, int height, int width); 
void draw_rect_bline(WINDOW* window,
                     int y, int x, int height, int width); 
void draw_rect_dline(WINDOW* window,
                     int y, int x, int height, int width); 
void draw_rect_rline(WINDOW* window,
                     int y, int x, int height, int width); 

void mvwprintw_split(WINDOW* window, int y, int x, char *str, int size, int split);
void mvwprintw_bin(WINDOW* window, int y, int x, unsigned long long value, int size, int split);
void mvwprintw_hex(WINDOW* window, int y, int x, unsigned long long value, int size, int split);


#endif

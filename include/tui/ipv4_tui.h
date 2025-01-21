#ifndef TUI_IPV4_H
#define TUI_IPV4_H

#include <stdint.h>
#include <ncurses.h>
#include "biteditor.h"
#include "../ipv4/ipv4.h"


typedef struct {
    WINDOW* window;
    unsigned long long values[12];
    char** labels;
    int* bitlen;
    size_t row, col;
    enum InputMode mode;
    int split;
    size_t current;
} ipv4tui_state_t;

void ipv4_tui(WINDOW *window, uint8_t *bytes);


#endif

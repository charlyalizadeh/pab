#ifndef TUI_IPV4_H
#define TUI_IPV4_H

#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>
#include "draw.h"
#include "../ipv4/ipv4.h"
#include "input.h"


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

void ipv4_tui_input_value(ipv4tui_state_t* state);
void ipv4_tui_draw_mode(ipv4tui_state_t* state);
int ipv4_tui_update(ipv4tui_state_t* state);
void ipv4_tui_draw(ipv4tui_state_t* state);
void ipv4_tui(WINDOW *window, uint8_t *bytes);


#endif

#ifndef BITEDITOR_H
#define BITEDITOR_H

#include <ncurses.h>
#include "draw.h"
#include "input.h"
#include "../utils/str.h"
#include "../utils/minmax.h"


typedef struct {
    WINDOW* window;
    int y;
    int x;
    int width;
    unsigned long long* values;
    int length;
    char** labels;
    int labels_lenmax;
    int* bitlen;
    int bitlen_max;
    enum InputMode mode;
    int split;
    size_t current;
} biteditor_state_t;

void biteditor_input_value(biteditor_state_t* state);
void biteditor_draw_mode(biteditor_state_t* state);
int biteditor_update(biteditor_state_t* state);
void biteditor_draw(biteditor_state_t* state);
void biteditor_init(biteditor_state_t* state, WINDOW* window, int y, int x, int length, char** labels, int* bitlen, unsigned long long* values);
void biteditor(WINDOW* window, int y, int x, int length, char** labels, int* bitlen, unsigned long long* values);
void biteditor_centered(WINDOW* window, int length, char** labels, int* bitlen, unsigned long long* values);


#endif

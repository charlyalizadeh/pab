#ifndef TUI_INPUT_H
#define TUI_INPUT_H

#include <ncurses.h>
#include <string.h>
#include "../utils/check_str.h"
#include "../utils/base_convertion.h"
#include "draw.h"


typedef struct {
    WINDOW* window;
    char* title;
    char* input;
    char* original_input;
    size_t title_length;
    size_t length;
    size_t cursor_pos;
    unsigned int length_limit;
    unsigned long long max;
    enum InputMode mode;
} input_state_t;

/* Utils */
unsigned long long get_input_value(char* str, size_t len, enum InputMode mode);
void clean_input(input_state_t* input_state);
char* copy_input(input_state_t* input_state);

/* Update helpers */
int set_input(input_state_t* input_state, char* new_input);
void insert_char(input_state_t* input_state, char c);
void del_char_before(input_state_t* input_state);
void del_char_after(input_state_t* input_state);
void switch_mode_down(input_state_t* input_state);

/* Draw helpers */
void draw_mode(int y, int x, input_state_t* input_state);
void draw_base_convertion(int y, int x, input_state_t* input_state);

int chui_input_update(input_state_t* input_state);
void chui_input_draw(int y, int x, int width, input_state_t* input_state);
void chui_input_free(input_state_t* input_state);
int chui_input_init(input_state_t* input_state,
                    WINDOW* window,
                    char* title, char* input,
                    unsigned int length_limit,
                    unsigned long long max,
                    enum InputMode mode);

void chui_input(WINDOW* window,
                int y, int x, int width,
                char* title, char* init,
                unsigned int length_limit,
                unsigned long long max,
                enum InputMode mode,
                input_state_t* input_state);
char* chui_input_str(WINDOW* window,
                     int y, int x, int width,
                     char* title, char* init,
                     unsigned int length_limit,
                     unsigned long long max,
                     enum InputMode mode);
uint64_t chui_input_int(WINDOW* window,
                        int y, int x, int width,
                        char* title, char* init,
                        unsigned long long max,
                        enum InputMode mode);


#endif

#include "../../include/tui/biteditor.h"


void biteditor_draw_mode(biteditor_state_t* state) {
    WINDOW* w;

    w = state->window;
    switch(state->mode) {
        case BINARY:
            mvwprintw(w, state->y + state->length + 2, state->x, "Mode: BINARY (press M to switch)");
            break;
        case HEXADECIMAL:
            mvwprintw(w, state->y + state->length + 2, state->x, "Mode: HEXADECIMAL (press M to switch)");
            break;
        case DECIMAL:
            mvwprintw(w, state->y + state->length + 2, state->x, "Mode: DECIMAL (press M to switch)");
            break;
        default:
            break;
    }
}
void biteditor_input_value(biteditor_state_t* state) {
    char* init;
    size_t size;
    size_t row, col;

    getmaxyx(state->window, row, col);
    switch(state->mode) {
        case BINARY:
            init = dec2bin(state->values[state->current], state->bitlen[state->current]);
            break;
        case HEXADECIMAL:
            size = state->bitlen[state->current] / 4;
            size += (size % 2) * (state->bitlen[state->current] % 4);
            init = dec2hex(state->values[state->current], size);
            break;
        case DECIMAL:
            init = malloc(state->bitlen_max * sizeof(char));
            init = dec2dec(state->values[state->current], -1);
            break;
        default:
            break;
    }
    state->values[state->current] = chui_input_int(state->window,
                                                   row / 2,
                                                   col / 2 - state->bitlen_max / 2,
                                                   state->bitlen_max,
                                                   state->labels[state->current],
                                                   init,
                                                   get_max_base(2, state->bitlen[state->current]),
                                                   state->mode);
    free(init);
}
int biteditor_update(biteditor_state_t* state) {
    int key;

    key = getch();
    if(key == KEY_EXIT || key == 27)
        return 0;
    else if(key == 'm') {
        switch(state->mode) {
            case BINARY:
                state->mode = HEXADECIMAL;
                state->split = 2;
                break;
            case HEXADECIMAL:
                state->mode = DECIMAL;
                state->split = 3;
                break;
            case DECIMAL:
                state->mode = BINARY;
                state->split = 4;
                break;
            default:
                break;
        }
    }
    else if(key == KEY_DOWN) {
        if(state->current == 11)
            state->current = 0;
        else
            state->current++;
    }
    else if(key == KEY_UP) {
        if(state->current == 0)
            state->current = 11;
        else
            state->current--;
    }
    else if(key == KEY_ENTER || key == KEY_IL || key == 13 || key == 10) {
        wclear(state->window);
        biteditor_input_value(state);
    }
    return 1;
}
void biteditor_draw(biteditor_state_t* state) {
    WINDOW* w;
    int size;

    w = state->window;
    for(int i = 0; i < 12; i++) {
        if(i == (int)state->current) {
            wattron(w, A_BOLD);
            wattron(w, A_REVERSE);
        }
        mvwprintw(w, state->y + 1 + i, state->x + 1, "%s", state->labels[i]);
        mvwprintw(w, state->y + 1 + i, state->x + 1 + state->labels_lenmax, ":");
        switch(state->mode) {
            case BINARY:
                mvwprintw_bin(w, state->y + 1 + i, state->x + 1 + state->labels_lenmax + 3, state->values[i], state->bitlen[i], state->split);
                break;
            case HEXADECIMAL:
                size = state->bitlen[i] / 4;
                size += (size % 2) * (state->bitlen[i] % 4);
                mvwprintw_hex(w, state->y + 1 + i, state->x + 1 + state->labels_lenmax + 3, state->values[i], size, state->split);
                break;
            case DECIMAL:
                mvwprintw(w, state->y + 1 + i, state->x + 1 + state->labels_lenmax + 3, "%lld", state->values[i]);
                break;
            default:
                break;
        }
        if(i == (int)state->current) {
            wattroff(w, A_BOLD);
            wattroff(w, A_REVERSE);
        }
    }
    biteditor_draw_mode(state);
    draw_rect_rline(w, state->y, state->x, state->length + 2, state->width + 2);
}
void biteditor_init(biteditor_state_t* state, WINDOW* window, int y, int x, int length, char** labels, int* bitlen, unsigned long long* values) {
    state->window = window;
    state->length = length;
    state->y = y;
    state->x = x;
    state->values = values;
    state->labels = labels;
    state->bitlen = bitlen;

    state->mode = BINARY;
    state->split = 4;
    state->current = 0;

    state->bitlen_max = max_d(bitlen, length);
    state->labels_lenmax = strslenmax(labels, length);
    state->width = state->bitlen_max + state->bitlen_max / 4 - 1 + state->labels_lenmax + 3;
}
void biteditor(WINDOW* window, int y, int x, int length, char** labels, int* bitlen, unsigned long long* values) {
    int stop;
    biteditor_state_t state;

    biteditor_init(&state, window, y, x, length, labels, bitlen, values);

    stop = 1;
    while(stop) {
        wclear(window);
        biteditor_draw(&state);
        stop = biteditor_update(&state);
    }
}

void biteditor_centered(WINDOW* window, int length, char** labels, int* bitlen, unsigned long long* values) {
    int stop;
    size_t row, col;
    biteditor_state_t state;

    getmaxyx(window, row, col);
    biteditor_init(&state, window, 0, 0, length, labels, bitlen, values);
    state.y = row / 2 - length / 2 - 1;
    state.x = col / 2 - state.width / 2 - 1;

    stop = 1;
    while(stop) {
        wclear(window);
        biteditor_draw(&state);
        stop = biteditor_update(&state);
    }
}

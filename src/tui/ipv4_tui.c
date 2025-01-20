#include "../../include/tui/ipv4_tui.h"


static void init_values(ipv4header_t* ipv4header, unsigned long long values[12]) {
    values[0] = ipv4header->version;
    values[1] = ipv4header->length;
    values[2] = ipv4header->type_of_service;
    values[3] = ipv4header->total_length;
    values[4] = ipv4header->identification;
    values[5] = ipv4header->flags;
    values[6] = ipv4header->fragment_offset;
    values[7] = ipv4header->time_to_live;
    values[8] = ipv4header->protocol;
    values[9] = ipv4header->checksum;
    values[10] = ipv4header->source;
    values[11] = ipv4header->destination;
}
void ipv4_tui_input_value(ipv4tui_state_t* state) {
    uint64_t new_value;
    size_t width;
    char* init;
    size_t size;

    width = 32;
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
            init = malloc(width * sizeof(char));
            snprintf(init, width, "%lld", state->values[state->current]);
            break;
        default:
            break;
    }
    state->values[state->current] = chui_input_int(state->window,
                                                   state->row / 2,
                                                   state->col / 2 - width / 2,
                                                   width,
                                                   state->labels[state->current],
                                                   init,
                                                   get_max_base(2, state->bitlen[state->current]),
                                                   state->mode);
    free(init);
}
int ipv4_tui_update(ipv4tui_state_t* state) {
    int key;

    getmaxyx(state->window, state->row, state->col);
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
        ipv4_tui_input_value(state);
    }
    return 1;
}
void ipv4_tui_draw_mode(ipv4tui_state_t* state) {
    WINDOW* w;
    size_t mid_row, mid_col;

    w = state->window;
    mid_row = state->row / 2;
    mid_col = state->col / 2;
    switch(state->mode) {
        case BINARY:
            mvwprintw(w, mid_row + 8, mid_col - 21, "Mode: BINARY (press M to switch)");
            break;
        case HEXADECIMAL:
            mvwprintw(w, mid_row + 8, mid_col - 21, "Mode: HEXADECIMAL (press M to switch)");
            break;
        case DECIMAL:
            mvwprintw(w, mid_row + 8, mid_col - 21, "Mode: DECIMAL (press M to switch)");
            break;
        default:
            break;
    }
}
void ipv4_tui_draw(ipv4tui_state_t* state) {
    WINDOW* w;
    size_t mid_row, mid_col;
    int size;
    char format[21];

    w = state->window;
    mid_row = state->row / 2;
    mid_col = state->col / 2;
    wclear(w);
    draw_rect_rline(w, mid_row - 7, mid_col - 28, 14, 62);
    for(int i = 0; i < 12; i++) {
        if(i == state->current) {
            wattron(w, A_BOLD);
            wattron(w, A_REVERSE);
        }
        snprintf(format, 21, "%s%%%lds", state->labels[i], 20 - strlen(state->labels[i]));
        mvwprintw(w, mid_row - 6 + i, mid_col - 27, format, ":");
        switch(state->mode) {
            case BINARY:
                mvwprintw_bin(w, mid_row - 6 + i, mid_col, state->values[i], state->bitlen[i], state->split);
                break;
            case HEXADECIMAL:
                size = state->bitlen[i] / 4;
                size += (size % 2) * (state->bitlen[i] % 4);
                mvwprintw_hex(w, mid_row - 6 + i, mid_col, state->values[i], size, state->split);
                break;
            case DECIMAL:
                mvwprintw(w, mid_row - 6 + i, mid_col, "%lld", state->values[i]);
                break;
            default:
                break;
        }
        if(i == state->current) {
            wattroff(w, A_BOLD);
            wattroff(w, A_REVERSE);
        }
    }
    ipv4_tui_draw_mode(state);
}
void ipv4_tui(WINDOW* window, uint8_t* bytes) {
    ipv4_t ipv4;
    ipv4tui_state_t state;
    int stop;
    int key;

    state.window = window;
    ipv4_from_bytes(bytes, &ipv4);
    init_values(&ipv4.header, state.values);
    state.labels = (char*[12]){
        "Version",
        "IHL",
        "Type of Service",
        "Total Length",
        "Identification",
        "Flags",
        "Fragment Offset",
        "Time to Live",
        "Protocol",
        "Header Checksum",
        "Source Address",
        "Destination Address"
    };
    state.bitlen = (int[12]){
        4, 4, 8, 16,
        16, 3, 13,
        8, 8, 16,
        32, 32
    };
    getmaxyx(window, state.row, state.col);
    state.mode = HEXADECIMAL;
    state.split = 2;
    state.current = 0;
    stop = 1;
    while(stop) {
        ipv4_tui_draw(&state);
        stop = ipv4_tui_update(&state);
    }
}

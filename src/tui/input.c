#include "../../include/tui/input.h"


unsigned long long get_input_value(char* str, size_t len, enum InputMode mode) {
    unsigned long long value;

    value = 0;
    switch(mode) {
        case BINARY:
            value = bin2dec(str, len);
            break;
        case HEXADECIMAL:
            value = hex2dec(str, len);
            break;
        case DECIMAL:
            value = atoi(str);
            break;
        default:
            break;
    }
    return value;
}
void clean_input(input_state_t* input_state) {
    if((input_state->mode == DECIMAL && !check_hex_str(input_state->input, input_state->length)) ||
       (input_state->mode == HEXADECIMAL && !check_hex_str(input_state->input, input_state->length)) ||
       (input_state->mode == BINARY && !check_decimal_str(input_state->input, input_state->length))) {
        memset(input_state->input, 0, input_state->length);
        input_state->length = 0;
        input_state->cursor_pos = 0;
    }
}
char* copy_input(input_state_t* input_state) {
    char* copy;

    copy = malloc((input_state->length_limit + 1) * sizeof(char));
    memcpy(copy, input_state->input, input_state->length_limit + 1);
    return copy;
}

int set_input(input_state_t* input_state, char* new_input) {
    size_t length;

    length = strlen(new_input);
    if(input_state->mode != ALL && input_state->max != 0 && get_input_value(new_input, length, input_state->mode) > input_state->max)
        return 0;
    memcpy(input_state->input, new_input, length + 1);
    memset(input_state->input + length + 1, 0, input_state->length_limit - length);
    input_state->length = length;
    return 1;
}
void insert_char(input_state_t* input_state, char c) {
    char* new_input;

    new_input = copy_input(input_state);
    if(input_state->cursor_pos < input_state->length) {
        for(size_t i = input_state->length; i > input_state->cursor_pos; i--)
            new_input[i] = input_state->input[i - 1];
    }
    new_input[input_state->cursor_pos] = c;
    new_input[input_state->length + 1] = '\0';
    if(set_input(input_state, new_input))
        input_state->cursor_pos++;
    free(new_input);
}
void del_char_before(input_state_t* input_state) {
    char* new_input;

    new_input = copy_input(input_state);
    if(input_state->cursor_pos < input_state->length) {
        for(size_t i = input_state->cursor_pos - 1; i < input_state->length; i++)
            new_input[i] = input_state->input[i + 1];
    }
    new_input[input_state->length - 1] = '\0';
    if(set_input(input_state, new_input) && input_state->cursor_pos > 0)
        input_state->cursor_pos--;
    free(new_input);
}
void del_char_after(input_state_t* input_state) {
    char* new_input;

    new_input = copy_input(input_state);
    for(size_t i = input_state->cursor_pos + 1; i < input_state->length; i++)
        new_input[i] = input_state->input[i + 1];
    new_input[input_state->length - 1] = '\0';
    set_input(input_state, new_input);
    free(new_input);
}
void switch_mode_down(input_state_t* input_state) {
    unsigned long long value;
    char* temp;

    switch(input_state->mode) {
        case BINARY:
            input_state->mode = HEXADECIMAL;
            if(input_state->length == 0)
                break;
            value = bin2dec(input_state->input, input_state->length);
            temp = dec2hex(value, -1);
            set_input(input_state, temp);
            free(temp);
            break;
        case HEXADECIMAL:
            input_state->mode = DECIMAL;
            if(input_state->length == 0)
                break;
            value = hex2dec(input_state->input, input_state->length);
            temp = malloc((input_state->length_limit + 1) * sizeof(char));
            snprintf(temp, input_state->length_limit + 1, "%lld", value);
            set_input(input_state, temp);
            break;
        case DECIMAL:
            input_state->mode = BINARY;
            if(input_state->length == 0)
                break;
            value = atoi(input_state->input);
            temp = dec2bin(value, -1);
            set_input(input_state, temp);
            free(temp);
            break;
        default:
            break;
    }
    if(input_state->cursor_pos > input_state->length)
        input_state->cursor_pos = input_state->length;
}
void draw_mode(int y, int x, input_state_t* input_state) {
    WINDOW *w;

    w = input_state->window;
    switch(input_state->mode) {
        case BINARY:
            mvwprintw(w, y + 3, x, "Mode: BINARY (Press↓ to switch)");
            break;
        case HEXADECIMAL:
            mvwprintw(w, y + 3, x, "Mode: HEXADECIMAL (Press↓ to switch)");
            break;
        case DECIMAL:
            mvwprintw(w, y + 3, x, "Mode: DECIMAL (Press↓ to switch)");
            break;
        case ALL:
            mvwprintw(w, y + 3, x, "Mode: ALL");
            break;
    }
}
void draw_base_convertion(int y, int x, input_state_t* input_state) {
    WINDOW* w;
    unsigned long long value;
    char* bin;
    char* hex;

    w = input_state->window;
    draw_mode(y, x, input_state);
    if(input_state->mode != ALL && input_state->length == 0) {
        mvwprintw(w, y + 4, x, "Dec:");
        mvwprintw(w, y + 5, x, "Hex:");
        mvwprintw(w, y + 6, x, "Bin:");
        return;
    }
    switch(input_state->mode) {
        case BINARY:
            value = bin2dec(input_state->input, input_state->length);
            hex = dec2hex(value, -1);
            mvwprintw(w, y + 4, x, "Dec: %lld", value);
            if(!hex)
                mvwprintw(w, y + 5, x, "Hex: ERROR");
            else
                mvwprintw(w, y + 5, x, "Hex: 0x%s", hex);
            mvwprintw(w, y + 6, x, "Bin: %s", input_state->input);
            free(hex);
            break;
        case HEXADECIMAL:
            value = hex2dec(input_state->input, input_state->length);
            bin = dec2bin(value, -1);
            mvwprintw(w, y + 4, x, "Dec: %lld", value);
            mvwprintw(w, y + 5, x, "Hex: 0x%s", input_state->input);
            if(!bin)
                mvwprintw(w, y + 6, x, "Bin: ERROR");
            else
                mvwprintw(w, y + 6, x, "Bin: %s", bin);
            free(bin);
            break;
        case DECIMAL:
            value = atoi(input_state->input);
            bin = dec2bin(value, -1);
            hex = dec2hex(value, -1);
            mvwprintw(w, y + 4, x, "Dec: %lld", value);
            if(!hex)
                mvwprintw(w, y + 5, x, "Hex: ERROR");
            else
                mvwprintw(w, y + 5, x, "Hex: 0x%s", hex);
            if(!bin)
                mvwprintw(w, y + 6, x, "Bin: ERROR");
            else
                mvwprintw(w, y + 6, x, "Bin: %s", bin);
            free(bin);
            free(hex);
            break;
        case ALL:
            mvwprintw(w, y + 3, x, "Mode: ALL");
            break;
    }
}

int chui_input_init(input_state_t* input_state,
                    WINDOW* window,
                    char* title, char* input,
                    unsigned int length_limit,
                    unsigned long long max,
                    enum InputMode mode) {
    size_t length;

    length = strlen(input);
    if(length > length_limit)
        return 0;
    input_state->window = window;
    input_state->mode = mode;
    input_state->length = length;
    input_state->length_limit = length_limit;
    input_state->max = max;
    input_state->original_input = malloc((length_limit + 1) * sizeof(char));
    if(!input_state->original_input)
        return 0;
    input_state->input = malloc((length_limit + 1) * sizeof(char));
    if(!input_state->input)
        return 0;
    if(length != 0) {
        memcpy(input_state->original_input, input, length);
        memcpy(input_state->input, input, length);
        memset(input_state->original_input + length, 0, length_limit - length);
        memset(input_state->input + length, 0, length_limit - length);
        input_state->cursor_pos = input_state->length;
        clean_input(input_state);
    }
    else
        input_state->cursor_pos = 0;
    input_state->title = title;
    input_state->title_length = strlen(title);
    return 1;
}
int chui_input_update(input_state_t* input_state) {
    int key;

    key = getch();
    if(key == KEY_BACKSPACE && input_state->cursor_pos > 0)
        del_char_before(input_state);
    if(key == KEY_DC && input_state->cursor_pos < input_state->length - 1)
        del_char_after(input_state);
    else if(key == KEY_LEFT && input_state->cursor_pos > 0)
        input_state->cursor_pos--;
    else if(key == KEY_RIGHT && input_state->cursor_pos < input_state->length)
        input_state->cursor_pos++;
    else if(key == KEY_DOWN)
        switch_mode_down(input_state);
    else if(key == KEY_ENTER || key == KEY_IL || key == 13 || key == 10)
        return 0;
    else if(key == KEY_EXIT || key == 27) {
        memcpy(input_state->input, input_state->original_input, input_state->length);
        return 0;
    }
    else if(key >= 32 && key <= 126 && input_state->length < 99) {
        if((input_state->mode == DECIMAL && !check_decimal_char(key)) ||
           (input_state->mode == HEXADECIMAL && !check_hex_char(key)) ||
           (input_state->mode == BINARY && !check_binary_char(key))) {
            return 1;
        }
        insert_char(input_state, key);
    }
    return 1;
}
void chui_input_draw(int y, int x, int width, input_state_t* input_state) {
    WINDOW* w;
    char format[6];

    w = input_state->window;
    sprintf(format, "%%.%zis", input_state->title_length);
    mvwprintw(w,
              y - 2,
              x + width / 2 - input_state->title_length / 2,
              format, input_state->title);

    draw_rect_rline(w, y - 1, x - 1, 3, width + 2);
    sprintf(format, "%%.%zis", input_state->length);
    mvwprintw(w, y, x, format, input_state->input);
    wattron(w, A_REVERSE);
    wattron(w, A_BOLD);
    if(input_state->cursor_pos < input_state->length)
        mvwaddch(w, y, x + input_state->cursor_pos, input_state->input[input_state->cursor_pos]);
    else
        mvwaddch(w, y, x + input_state->cursor_pos, ' ');
    wattroff(w, A_REVERSE);
    wattroff(w, A_BOLD);

    mvwprintw(w, y + 2, x, "Length: %zi", input_state->length);
    draw_base_convertion(y, x, input_state);
    if(input_state->mode != ALL)
        mvwprintw(w, y + 7, x, "Max value: %lld", input_state->max);
}
void chui_input_free(input_state_t* input_state) {
    free(input_state->original_input);
    free(input_state->input);
}
void chui_input(WINDOW* window,
                int y, int x, int width,
                char* title, char* init,
                unsigned int length_limit,
                unsigned long long max,
                enum InputMode mode,
                input_state_t* input_state) {
    int stop;

    if(!chui_input_init(input_state,  window, title, init, length_limit, max, mode))
        return;
    stop = 1;
    while(stop) {
        chui_input_draw(y, x, width, input_state);
        stop = chui_input_update(input_state);
        wclear(window);
    }
}
char* chui_input_str(WINDOW* window,
                     int y, int x, int width,
                     char* title, char* init,
                     unsigned int length_limit,
                     unsigned long long max,
                     enum InputMode mode) {
    input_state_t input_state;
    char* out;

    chui_input(window, y, x, width, title, init, length_limit, max, mode, &input_state);
    out = malloc(input_state.length * sizeof(char));
    if(!out)
        return NULL;
    memcpy(out, input_state.input, input_state.length);
    out[input_state.length] = '\0';
    chui_input_free(&input_state);
    return out;
}
uint64_t chui_input_int(WINDOW* window,
                        int y, int x, int width,
                        char* title, char* init,
                        unsigned long long max,
                        enum InputMode mode) {
    input_state_t input_state;
    uint64_t out;

    if(mode == ALL)
        return 0;
    chui_input(window, y, x, width, title, init, width, max, mode, &input_state);
    switch(input_state.mode) {
        case BINARY:
            out = bin2dec(input_state.input, input_state.length);
            break;
        case HEXADECIMAL:
            out = hex2dec(input_state.input, input_state.length);
            break;
        case DECIMAL:
            out = atoi(input_state.input);
            break;
        default:
            break;
    }
    chui_input_free(&input_state);
    return out;
}

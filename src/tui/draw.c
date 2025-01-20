#include "../../include/tui/draw.h"


char* TUI_SLINES[9] = {"─", "│", "┌", "┐", "└", "┘", "┼", "├", "┤"};
char* TUI_BLINES[9] = {"━", "┃", "┏", "┓", "┗", "┛", "╋", "┣", "┫"};
char* TUI_DLINES[9] = {"═", "║", "╔", "╗", "╚", "╝", "╬", "╠", "╣"};
char* TUI_RLINES[9] = {"─", "│", "╭", "╮", "╰", "╯", "┼", "├", "┤"};

void draw_rect(WINDOW* window,
               int y, int x, int height, int width,
               char** lines) {
    for(int i = 0; i < width; i++) {
        if(i == 0) {
            mvwprintw(window, y, x + i, "%s", lines[UP_LEFT]);
            mvwprintw(window, y + height - 1, x + i, "%s", lines[DOWN_LEFT]);
        }
        else if(i == width - 1) {
            mvwprintw(window, y, x + i, "%s", lines[UP_RIGHT]);
            mvwprintw(window, y + height - 1, x + i, "%s", lines[DOWN_RIGHT]);
        }
        else {
            mvwprintw(window, y, x + i, "%s", lines[HORIZONTAL]);
            mvwprintw(window, y + height - 1, x + i, "%s", lines[HORIZONTAL]);
        }
    }
    for(int i = 1; i < height - 1; i++) {
        mvwprintw(window, y + i, x, "%s", lines[VERTICAL]);
        mvwprintw(window, y + i, x + width - 1, "%s", lines[VERTICAL]);
    }
}
void draw_rect_sline(WINDOW* window, int y, int x, int height, int width) {
    draw_rect(window, y, x, height, width, TUI_SLINES);
}
void draw_rect_bline(WINDOW* window, int y, int x, int height, int width) {
    draw_rect(window, y, x, height, width, TUI_BLINES);
}
void draw_rect_dline(WINDOW* window, int y, int x, int height, int width) {
    draw_rect(window, y, x, height, width, TUI_DLINES);
}
void draw_rect_rline(WINDOW* window, int y, int x, int height, int width) {
    draw_rect(window, y, x, height, width, TUI_RLINES);
}

void mvwprintw_split(WINDOW* window, int y, int x, char *str, int size, int split) {
    char format[16];
    size_t nsplit;
    int mod;

    if(split <= 0) {
        mvwprintw(window, y, x, "%s", str);
        return;
    }
    mod = size % split;
    size += mod;
    nsplit = size / split;
    sprintf(format, "%%.%ds", split);
    for(size_t i = 0; i < nsplit; i++) {
        mvwprintw(window, y, x + i * (split + 1), format, str + i * split);
        if(i < nsplit - 1)
            mvwaddch(window, y, x + (i + 1) * (split + 1) + 1, ' ');
    }
}
void mvwprintw_bin(WINDOW* window, int y, int x, unsigned long long value, int size, int split) {
    char* bin;

    bin = dec2bin(value, size); 
    if(!bin)
        return;
    if(size <= 0)
        size = strlen(bin);
    mvwprintw_split(window, y, x, bin, size, split);
    free(bin);
}
void mvwprintw_hex(WINDOW* window, int y, int x, unsigned long long value, int size, int split) {
    char* hex;

    hex = dec2hex(value, size); 
    if(!hex)
        return;
    if(size <= 0)
        size = strlen(hex);
    mvwprintw_split(window, y, x, hex, size, split);
    free(hex);
}

#include "../../include/tui/select.h"


int update_select(select_state_t* select_state) {
    int key;

    key = getch();
    if(key == KEY_DOWN) {
        if(select_state->current < select_state->length - 1)
            select_state->current++;
        else
            select_state->current = 0;
    }
    else if(key == KEY_UP) {
        if(select_state->current > 0)
            select_state->current--;
        else
            select_state->current = select_state->length - 1;
    }
    else if(key == KEY_ENTER || key == KEY_IL || key == 13 || key == 10)
        return 0;
    return 1;
}
void draw_select(int y, int x, int width, select_state_t* select_state) {
    WINDOW* w;

    w = select_state->window;
    mvwprintw(w,
              y,
              x - 2 - strlen(select_state->title),
              "%s",
              select_state->title);
    draw_rect_rline(w, y - 1, x - 1, 3, width + 2);
    for(size_t i = 0; i < select_state->length; i++) {
        if(i == select_state->current)
            wattron(w, A_BOLD);
        mvwprintw(w,
                  y - 2 * (select_state->current - i),
                  x + width / 2 - strlen(select_state->items[i]) / 2,
                  "%s",
                  select_state->items[i]);
        if(i == select_state->current)
            wattroff(w, A_BOLD);
    }
    mvwprintw(w, y, x + width + 2, "(Press↓ or↑ to switch)");
}
int chui_select(WINDOW* window,
                int y, int x,
                char* title,
                char** items, size_t length) {
    select_state_t select_state;
    size_t width;
    int stop;

    select_state.window = window;
    select_state.title = title;
    select_state.items = items;
    select_state.length = length;
    select_state.current = length / 2;
    width = strslenmax(items, length);
    stop = 1;
    while(stop) {
        draw_select(y, x, width, &select_state);
        stop = update_select(&select_state);
        wclear(window);
    }
    return select_state.current;
}

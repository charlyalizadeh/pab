#include "../../include/tui/tui.h"


void start_pab(void) {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    ESCDELAY = 10;
}
void end_pab(void) {
    endwin();
}
void start_packet(uint8_t* buffer, enum CHUIProtocol protocol) {
    switch(protocol) {
        case IPv4:
            ipv4_tui(stdscr, buffer);
            break;
        default:
            mvwprintw(stdscr, 0, 0, "NOT IMPLEMENTED (Press a key to exit)");
            getch();
            break;
    }
}
void main_menu(void) {
    int row, col;
    char* title;
    char* packet_path;
    enum CHUIProtocol protocol;
    size_t width;
    uint8_t* buffer;

    getmaxyx(stdscr, row, col);
    width = 50 > col ? col - 2 : 50;

    /* Packet path */
    title = "Path to packet";
    while(1) {
        packet_path = chui_input_str(stdscr, row / 2, col / 2 - width / 2, width, title, "", width, 0, ALL);
        if(!packet_path)
            return;
        if(access(packet_path, F_OK) != 0) {
            clear();
            mvprintw(row / 2, col / 2 - 46 / 2, "File not found. Please enter a valid file path.");
            mvprintw(row / 2 + 1, col / 2 - 25 / 2, "(Press a key to continue)");
            free(packet_path);
            getch();
            clear();
            continue;
        }
        buffer = read_bytes(packet_path);
        if(!buffer)
            return;
    }
    /* Protocol */
    protocol = chui_select(stdscr, row / 2, col / 2 - 4, "Select protocol", (char*[3]){"IPv4", "TCP", "UDP"}, 3);
    start_packet(buffer, protocol);
    free(packet_path);
}

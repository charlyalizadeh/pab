#ifndef TUI_H
#define TUI_H

#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include "input.h"
#include "select.h"
#include "../ipv4/ipv4.h"
#include "../utils/file.h"
#include "ipv4_tui.h"


enum CHUIProtocol {
    IPv4,
};


void start_pab(void);
void end_pab(void);
void start_packet(uint8_t* buffer, enum CHUIProtocol protocol);
void main_menu(void);


#endif

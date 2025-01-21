#ifndef TUI_IPV4_H
#define TUI_IPV4_H

#include <stdint.h>
#include <ncurses.h>
#include "biteditor.h"
#include "../ipv4/ipv4.h"


void ipv4_tui(WINDOW *window, uint8_t *bytes);


#endif

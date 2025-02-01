#ifndef IPV4_H
#define IPV4_H

#include <stdio.h>
#include "ipv4_header.h"
#include "ipv4_option.h"
#include "../utils/base_convertion.h"


typedef struct {
    ipv4header_t header;
    ipv4option_t option;
    uint8_t* data;
    size_t data_length;
} ipv4_t;

void ipv4_init(ipv4_t* ipv4);
void ipv4_build_bytes(ipv4_t* ipv4, uint8_t* buffer);
void ipv4_from_bytes(uint8_t* buffer, ipv4_t* ipv4);
void ipv4_print_dec(ipv4_t* ipv4);
void ipv4_print_hex(ipv4_t* ipv4);
void ipv4_print_bin(ipv4_t* ipv4);


#endif

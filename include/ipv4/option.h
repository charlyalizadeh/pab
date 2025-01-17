#ifndef OPTION_H
#define OPTION_H

#include <stddef.h>
#include <stdio.h>
#include "security.h"
#include "source_route.h"


typedef struct {
    unsigned int nb;
    uint8_t option_lengths[40];
    size_t length;
    uint8_t buffer[40];
} ipv4option_t;

void ipv4option_init(ipv4option_t* option);
uint8_t ipv4option_push_no_option(ipv4option_t* option);
uint8_t ipv4option_push_end_option(ipv4option_t* option);
uint8_t ipv4option_push_security(ipv4option_t* option, ipv4option_security_t* security);
uint8_t ipv4option_push_sr(ipv4option_t* option, ipv4option_sr_t* sr);
uint8_t ipv4option_push_stream_id(ipv4option_t* option, uint16_t stream_id);
uint8_t ipv4option_push_internet_timestamp(ipv4option_t* option, uint8_t length, uint8_t flag);
uint8_t ipv4option_pop_option(ipv4option_t* option);


#endif

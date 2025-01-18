#ifndef IPV4_H
#define IPV4_H

#include "ipv4_header.h"
#include "ipv4_option.h"


/* Building the buffer */
void ipv4_build_bytes(ipv4header_t* header,
                      ipv4option_t* option,
                      uint8_t* data,
                      uint64_t data_length,
                      uint8_t* buffer);
void ipv4_from_bytes(uint8_t* buffer,
                     ipv4header_t* header,
                     ipv4option_t* option);


#endif

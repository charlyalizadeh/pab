#include "../../include/ipv4/ipv4.h"



void ipv4_init(ipv4_t* ipv4) {
    ipv4->data_length = 0;
    ipv4header_init(&ipv4->header);
    ipv4option_init(&ipv4->option);
}
/* Building the buffer */
void ipv4_build_bytes(ipv4_t* ipv4, uint8_t* buffer) {
    ipv4header_t* header;
    ipv4option_t* option;

    header = &ipv4->header;
    option = &ipv4->option;
    header->length = 20 + option->length;
    header->checksum = ipv4header_compute_header_checksum(header);
    ipv4header_to_bytes(header, buffer);
    ipv4option_to_bytes(option, buffer + 20);
    memcpy(buffer + header->length, ipv4->data, ipv4->data_length);
}
void ipv4_from_bytes(uint8_t* buffer, ipv4_t* ipv4) {
    ipv4header_from_bytes(buffer, &ipv4->header);
    //if(ipv4->header.length <= 20)
    //    ipv4option_init(&ipv4->option);
    //else
    //    ipv4option_from_bytes(buffer, &ipv4->option);
}

#include "../../include/ipv4/ipv4.h"



/* Building the buffer */
void ipv4_to_bytes(ipv4header_t* header,
                   ipv4option_t* option,
                   uint8_t* data,
                   uint64_t data_length,
                   uint8_t* buffer) {
    size_t bi;

    header->length = 20 + option->length;
    header->checksum = ipv4header_compute_header_checksum(header);
    bi = 0;
    buffer[bi++] = header->version | (header->length << 4);
    buffer[bi++] = header->type_of_service;
    buffer[bi++] = header->total_length;
    buffer[bi++] = header->total_length >> 8;
    buffer[bi++] = header->identification;
    buffer[bi++] = header->identification >> 8;
    buffer[bi++] = header->flags | (header->fragment_offset << 3);
    buffer[bi++] = header->fragment_offset >> 5;
    buffer[bi++] = header->time_to_live;
    buffer[bi++] = header->protocol;
    buffer[bi++] = header->checksum;
    buffer[bi++] = header->checksum >> 8;
    buffer[bi++] = header->source;
    buffer[bi++] = header->source >> 8;
    buffer[bi++] = header->source >> 16;
    buffer[bi++] = header->source >> 24;
    buffer[bi++] = header->destination;
    buffer[bi++] = header->destination >> 8;
    buffer[bi++] = header->destination >> 16;
    buffer[bi++] = header->destination >> 24;
    memcpy(buffer + bi, option->buffer, option->length);
    bi += option->length;
    memcpy(buffer + bi, data, data_length);
}
void ipv4_from_bytes(uint8_t* buffer, ipv4header_t* header, ipv4option_t* option) {
    ipv4header_from_bytes(buffer, header);
    ipv4option_from_bytes(buffer, option);
}

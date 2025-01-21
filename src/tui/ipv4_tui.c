#include "../../include/tui/ipv4_tui.h"


static void init_values(ipv4header_t* ipv4header, unsigned long long values[12]) {
    values[0] = ipv4header->version;
    values[1] = ipv4header->length;
    values[2] = ipv4header->type_of_service;
    values[3] = ipv4header->total_length;
    values[4] = ipv4header->identification;
    values[5] = ipv4header->flags;
    values[6] = ipv4header->fragment_offset;
    values[7] = ipv4header->time_to_live;
    values[8] = ipv4header->protocol;
    values[9] = ipv4header->checksum;
    values[10] = ipv4header->source;
    values[11] = ipv4header->destination;
}
void ipv4_tui(WINDOW* window, uint8_t* bytes) {
    ipv4_t ipv4;
    char** labels;
    int* bitlen;
    unsigned long long values[12];

    ipv4_from_bytes(bytes, &ipv4);
    init_values(&ipv4.header, values);
    labels = (char*[12]){
        "Version",
        "IHL",
        "Type of Service",
        "Total Length",
        "Identification",
        "Flags",
        "Fragment Offset",
        "Time to Live",
        "Protocol",
        "Header Checksum",
        "Source Address",
        "Destination Address"
    };
    bitlen = (int[12]){
        4, 4, 8, 16,
        16, 3, 13,
        8, 8, 16,
        32, 32
    };
    biteditor_centered(window, 12, labels, bitlen, values);
}

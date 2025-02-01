#include "../../include/ipv4/ipv4.h"



void ipv4_init(ipv4_t* ipv4) {
    ipv4->data_length = 0;
    ipv4header_init(&ipv4->header);
    ipv4option_init(&ipv4->option);
}
void ipv4_build_bytes(ipv4_t* ipv4, uint8_t* buffer) {
    ipv4header_t* header;
    ipv4option_t* option;

    header = &ipv4->header;
    option = &ipv4->option;
    header->length = 20 + option->length;
    ipv4header_to_bytes(header, buffer);
    ipv4option_to_bytes(option, buffer + 20);
    memcpy(buffer + header->length, ipv4->data, ipv4->data_length);
}
void ipv4_from_bytes(uint8_t* buffer, ipv4_t* ipv4) {
    ipv4header_from_bytes(buffer, &ipv4->header);
    if(ipv4->header.length <= 20)
        ipv4option_init(&ipv4->option);
    else
        ipv4option_from_bytes(buffer, &ipv4->option);
}
void ipv4_print_dec(ipv4_t* ipv4) {
    printf("Version: %u\n", ipv4->header.version);
    printf("IHL: %u\n", ipv4->header.length);
    printf("Type of Service: %u\n", ipv4->header.type_of_service);
    printf("Total Length: %u\n", ipv4->header.total_length);
    printf("Identification: %u\n", ipv4->header.identification);
    printf("Flags: %u\n", ipv4->header.flags);
    printf("Fragment Offset: %u\n", ipv4->header.fragment_offset);
    printf("Time to Live: %u\n", ipv4->header.time_to_live);
    printf("Porotocol: %u\n", ipv4->header.protocol);
    printf("Header Checksum: %u\n", ipv4->header.checksum);
    printf("Source Address: %u\n", ipv4->header.source);
    printf("Destination Address: %u\n", ipv4->header.destination);
}
void ipv4_print_hex(ipv4_t* ipv4) {
    printf("Version: %1X\n", ipv4->header.version);
    printf("IHL: %1X\n", ipv4->header.length);
    printf("Type of Service: %1X\n", ipv4->header.type_of_service);
    printf("Total Length: %2X\n", ipv4->header.total_length);
    printf("Identification: %2X\n", ipv4->header.identification);
    printf("Flags: %1X\n", ipv4->header.flags);
    printf("Fragment Offset: %2X\n", ipv4->header.fragment_offset);
    printf("Time to Live: %1X\n", ipv4->header.time_to_live);
    printf("Porotocol: %1X\n", ipv4->header.protocol);
    printf("Header Checksum: %2X\n", ipv4->header.checksum);
    printf("Source Address: %4X\n", ipv4->header.source);
    printf("Destination Address: %4X\n", ipv4->header.destination);
}
void ipv4_print_bin(ipv4_t* ipv4) {
    printf("Version: "); dec2bin_print(ipv4->header.version, 4); printf("\n");
    printf("IHL: "); dec2bin_print(ipv4->header.length, 4); printf("\n");
    printf("Type of Service: "); dec2bin_print(ipv4->header.type_of_service, 8); printf("\n");
    printf("Total Length: "); dec2bin_print(ipv4->header.total_length, 16); printf("\n");
    printf("Identification: "); dec2bin_print(ipv4->header.identification, 16); printf("\n");
    printf("Flags: "); dec2bin_print(ipv4->header.flags, 3); printf("\n");
    printf("Fragment Offset: "); dec2bin_print(ipv4->header.fragment_offset, 13); printf("\n");
    printf("Time to Live: "); dec2bin_print(ipv4->header.time_to_live, 8); printf("\n");
    printf("Porotocol: "); dec2bin_print(ipv4->header.protocol, 8); printf("\n");
    printf("Header Checksum: "); dec2bin_print(ipv4->header.checksum, 16); printf("\n");
    printf("Source Address: "); dec2bin_print(ipv4->header.source, 32); printf("\n");
    printf("Destination Address: "); dec2bin_print(ipv4->header.destination, 32); printf("\n");
}

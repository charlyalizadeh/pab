#include "../include/utils/file.h"
#include "../include/ipv4/ipv4.h"

int main(void) {
    uint8_t* bytes = read_bytes("dump.bin");
    ipv4_t ipv4;
    ipv4_from_bytes(bytes, &ipv4);
    ipv4_print_dec(&ipv4);
    ipv4_print_hex(&ipv4);
    ipv4_print_bin(&ipv4);
    return 0;
}
